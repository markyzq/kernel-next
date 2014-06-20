/*
 * Copyright (c) 2013 MundoReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/delay.h>
#include <linux/init.h>
#include <linux/smp.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
//#include <linux/cpu.h>

#include <asm/cacheflush.h>
#include <asm/smp_scu.h>
#include <asm/smp_plat.h>
#include <asm/mach/map.h>

#include "core.h"

static void __iomem *scu_base_addr;
static void __iomem *sram_base_addr;
static int ncores;

#define PMU_PWRDN_CON		0x08
#define PMU_PWRDN_ST		0x0c

#define PMU_PWRDN_SCU		4

static void __iomem *pmu_base_addr;

static inline bool pmu_power_domain_is_on(int pd)
{
	return !(readl_relaxed(pmu_base_addr + PMU_PWRDN_ST) & BIT(pd));
}

static void pmu_set_power_domain(int pd, bool on)
{
	u32 val = readl_relaxed(pmu_base_addr + PMU_PWRDN_CON);
	if (on)
		val &= ~BIT(pd);
	else
		val |=  BIT(pd);
	writel(val, pmu_base_addr + PMU_PWRDN_CON);

	while (pmu_power_domain_is_on(pd) != on) { }
}

/*
 * Handling of CPU cores
 */

static int __cpuinit rockchip_boot_secondary(unsigned int cpu,
					     struct task_struct *idle)
{
	if (!sram_base_addr || !pmu_base_addr) {
		pr_err("%s: sram or pmu missing for cpu boot\n", __func__);
		return -ENXIO;
	}

	if (ncores > 0 && cpu >= ncores) {
		pr_err("%s: cpu %d outside maximum number of cpus %d\n",
							__func__, cpu, ncores);
		return -ENXIO;
	}

	/* start the core */
	pmu_set_power_domain(0 + cpu, true);

	return 0;
}

/**
 * rockchip_smp_prepare_sram - populate necessary sram block
 * Starting cores execute the code residing at the start of the on-chip sram
 * after power-on. Therefore make sure, this sram region is reserved and
 * big enough. After this check, copy the trampoline code that directs the
 * core to the real startup code in ram into the sram-region.
 * @node: mmio-sram device node
 */
static int __init rockchip_smp_prepare_sram(struct device_node *node,
					    unsigned long boot_fn)
{
	unsigned int trampoline_sz = &rockchip_secondary_trampoline_end -
					    &rockchip_secondary_trampoline;
	struct resource res;
	unsigned int rsize;
	int ret;

	ret = of_address_to_resource(node, 0, &res);
	if (ret < 0) {
		pr_err("%s: could not get address for node %s\n",
		       __func__, node->full_name);
		return ret;
	}

	rsize = resource_size(&res);
	if (rsize < trampoline_sz) {
		pr_err("%s: reserved block with size 0x%x is to small for trampoline size 0x%x\n",
		       __func__, rsize, trampoline_sz);
		return -EINVAL;
	}

	sram_base_addr = of_iomap(node, 0);

	/* set the boot function for the sram code */
	rockchip_boot_fn = boot_fn;

	/* copy the trampoline to sram, that runs during startup of the core */
	memcpy(sram_base_addr, &rockchip_secondary_trampoline, trampoline_sz);
	flush_cache_all();
	outer_clean_range(0, trampoline_sz);

	dsb_sev();

	return 0;
}

static void __init rk3066_smp_prepare_cpus(unsigned int max_cpus)
{
	struct device_node *node;
	unsigned int i;

	node = of_find_compatible_node(NULL, NULL, "arm,cortex-a9-scu");
	if (!node) {
		pr_err("%s: missing scu\n", __func__);
		return;
	}

	scu_base_addr = of_iomap(node, 0);
	if (!scu_base_addr) {
		pr_err("%s: could not map scu registers\n", __func__);
		return;
	}

	node = of_find_compatible_node(NULL, NULL, "rockchip,rk3066-smp-sram");
	if (!node) {
		pr_err("%s: could not find sram dt node\n", __func__);
		return;
	}

	if (rockchip_smp_prepare_sram(node,
				virt_to_phys(rockchip_secondary_startup)))
		return;

	node = of_find_compatible_node(NULL, NULL, "rockchip,rk3066-pmu");
	if (!node) {
		pr_err("%s: could not find pmu dt node\n", __func__);
		return;
	}

	pmu_base_addr = of_iomap(node, 0);
	if (!pmu_base_addr) {
		pr_err("%s: could not map pmu registers\n", __func__);
		return;
	}

	/* enable the SCU power domain */
	pmu_set_power_domain(PMU_PWRDN_SCU, true);

	/*
	 * While the number of cpus is gathered from dt, also get the number
	 * of cores from the scu to verify this value when booting the cores.
	 */
	ncores = scu_get_core_count(scu_base_addr);

	scu_enable(scu_base_addr);

	/* Make sure that all cores except the first are really off */
	for (i = 1; i < ncores; i++)
		pmu_set_power_domain(0 + i, false);
}

static void __init rk3288_smp_prepare_cpus(unsigned int max_cpus)
{
	struct device_node *node;
	unsigned int i;

	/* Enable remap, so the cores boot from sram.
	 * FIXME: this should use the early_syscon to use regmap.
	 */
	void __iomem *tmp = ioremap(0xff740000, 0x1000);
	writel((1 << 11) | (1 << (11+16)), tmp);

//	node = of_get_cpu_node(0, NULL);

	node = of_find_compatible_node(NULL, NULL, "rockchip,rk3066-smp-sram");
	if (!node) {
		pr_err("%s: could not find sram dt node\n", __func__);
		return;
	}

	if (rockchip_smp_prepare_sram(node,
				virt_to_phys(secondary_startup)))
		return;

	node = of_find_compatible_node(NULL, NULL, "rockchip,rk3066-pmu");
	if (!node) {
		pr_err("%s: could not find pmu dt node\n", __func__);
		return;
	}

	pmu_base_addr = of_iomap(node, 0);
	if (!pmu_base_addr) {
		pr_err("%s: could not map pmu registers\n", __func__);
		return;
	}

	ncores = 4;

	/* Make sure that all cores except the first are really off */
	for (i = 1; i < ncores; i++)
		pmu_set_power_domain(0 + i, false);
}

static struct smp_operations rockchip3066_smp_ops __initdata = {
	.smp_prepare_cpus	= rk3066_smp_prepare_cpus,
	.smp_boot_secondary	= rockchip_boot_secondary,
};
CPU_METHOD_OF_DECLARE(rk3066_smp, "rockchip,rk3066-smp", &rockchip3066_smp_ops);

static struct smp_operations rockchip3288_smp_ops __initdata = {
	.smp_prepare_cpus	= rk3288_smp_prepare_cpus,
	.smp_boot_secondary	= rockchip_boot_secondary,
};
CPU_METHOD_OF_DECLARE(rk3288_smp, "rockchip,rk3288-smp", &rockchip3288_smp_ops);

