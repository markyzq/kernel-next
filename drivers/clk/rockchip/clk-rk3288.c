/*
 * Copyright (c) 2014 MundoReader S.L.
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

#include <linux/clk-provider.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <dt-bindings/clock/rk3188-cru.h>

#include "clk.h"

#define RK3288_PLL_CON(x)		RK2928_PLL_CON(x)
#define RK3288_MODE_CON			0x50
#define RK3288_CLKSEL_CON(x)		(x * 0x4 + 0x60)
#define RK3288_CLKGATE_CON(x)		(x * 0x4 + 0x160)
#define RK3288_GLB_SRST_FST		0x1b0
#define RK3288_GLB_SRST_SND		0x1b4
#define RK3288_SOFTRST_CON(x)		(x * 0x4 + 0x1b8)


/* list of PLLs to be registered */
enum rk3288_plls {
	apll, dpll, cpll, gpll, npll,
};

struct rockchip_pll_rate_table rk3288_apll_rates[] = {
	RK3066_PLL_RATE(2208000000, 1, 92, 1),
	RK3066_PLL_RATE(2184000000, 1, 91, 1),
	RK3066_PLL_RATE(2160000000, 1, 90, 1),
	RK3066_PLL_RATE(2136000000, 1, 89, 1),
	RK3066_PLL_RATE(2112000000, 1, 88, 1),
	RK3066_PLL_RATE(2088000000, 1, 87, 1),
	RK3066_PLL_RATE(2064000000, 1, 86, 1),
	RK3066_PLL_RATE(2040000000, 1, 85, 1),
	RK3066_PLL_RATE(2016000000, 1, 84, 1),
	RK3066_PLL_RATE(1992000000, 1, 83, 1),
	RK3066_PLL_RATE(1968000000, 1, 82, 1),
	RK3066_PLL_RATE(1944000000, 1, 81, 1),
	RK3066_PLL_RATE(1920000000, 1, 80, 1),
	RK3066_PLL_RATE(1896000000, 1, 79, 1),
	RK3066_PLL_RATE(1872000000, 1, 78, 1),
	RK3066_PLL_RATE(1848000000, 1, 77, 1),
	RK3066_PLL_RATE(1824000000, 1, 76, 1),
	RK3066_PLL_RATE(1800000000, 1, 75, 1),
	RK3066_PLL_RATE(1776000000, 1, 74, 1),
	RK3066_PLL_RATE(1752000000, 1, 73, 1),
	RK3066_PLL_RATE(1728000000, 1, 72, 1),
	RK3066_PLL_RATE(1704000000, 1, 71, 1),
	RK3066_PLL_RATE(1680000000, 1, 70, 1),
	RK3066_PLL_RATE(1656000000, 1, 69, 1),
	RK3066_PLL_RATE(1632000000, 1, 68, 1),
	RK3066_PLL_RATE(1608000000, 1, 67, 1),
	RK3066_PLL_RATE(1560000000, 1, 65, 1),
	RK3066_PLL_RATE(1512000000, 1, 63, 1),
	RK3066_PLL_RATE(1488000000, 1, 62, 1),
	RK3066_PLL_RATE(1464000000, 1, 61, 1),
	RK3066_PLL_RATE(1440000000, 1, 60, 1),
	RK3066_PLL_RATE(1416000000, 1, 59, 1),
	RK3066_PLL_RATE(1392000000, 1, 58, 1),
	RK3066_PLL_RATE(1368000000, 1, 57, 1),
	RK3066_PLL_RATE(1344000000, 1, 56, 1),
	RK3066_PLL_RATE(1320000000, 1, 55, 1),
	RK3066_PLL_RATE(1296000000, 1, 54, 1),
	RK3066_PLL_RATE(1272000000, 1, 53, 1),
	RK3066_PLL_RATE(1248000000, 1, 52, 1),
	RK3066_PLL_RATE(1224000000, 1, 51, 1),
	RK3066_PLL_RATE(1200000000, 1, 50, 1),
	RK3066_PLL_RATE(1176000000, 1, 49, 1),
	RK3066_PLL_RATE(1128000000, 1, 47, 1),
	RK3066_PLL_RATE(1104000000, 1, 46, 1),
	RK3066_PLL_RATE(1008000000, 1, 84, 2),
	RK3066_PLL_RATE( 912000000, 1, 76, 2),
	RK3066_PLL_RATE( 888000000, 1, 74, 2),
	RK3066_PLL_RATE( 816000000, 1, 68, 2),
	RK3066_PLL_RATE( 792000000, 1, 66, 2),
	RK3066_PLL_RATE( 696000000, 1, 58, 2),
	RK3066_PLL_RATE( 600000000, 1, 50, 2),
	RK3066_PLL_RATE( 504000000, 1, 84, 4),
	RK3066_PLL_RATE( 408000000, 1, 68, 4),
	RK3066_PLL_RATE( 312000000, 1, 52, 4),
	RK3066_PLL_RATE( 252000000, 1, 84, 8),
	RK3066_PLL_RATE( 216000000, 1, 72, 8),
	RK3066_PLL_RATE( 126000000, 1, 84, 16),
	RK3066_PLL_RATE(  48000000, 1, 64, 32),
	{ /* sentinel */ },
};

struct rockchip_pll_rate_table rk3288_cpll_rates[] = {
	RK3066_PLL_RATE(1188000000, 2,  99, 1),
	RK3066_PLL_RATE( 798000000, 2, 133, 2),
	RK3066_PLL_RATE( 768000000, 1,  64, 2),
	RK3066_PLL_RATE( 742500000, 8, 495, 2),
	RK3066_PLL_RATE( 600000000, 1,  50, 2),
	RK3066_PLL_RATE( 594000000, 2, 198, 4),
	RK3066_PLL_RATE( 552000000, 1,  46, 2),
	RK3066_PLL_RATE( 504000000, 1,  84, 4),
	RK3066_PLL_RATE( 456000000, 1,  76, 4),
	RK3066_PLL_RATE( 408000000, 1,  68, 4),
	RK3066_PLL_RATE( 360000000, 1,  60, 4),
	{ /* sentinel */ },
};

struct rockchip_pll_rate_table rk3288_gpll_rates[] = {
	RK3066_PLL_RATE(1200000000, 1,  50, 1),
	RK3066_PLL_RATE(1188000000, 2,  99, 1),
	RK3066_PLL_RATE( 891000000, 8, 594, 2),
	RK3066_PLL_RATE( 768000000, 1,  64, 2),
	RK3066_PLL_RATE( 594000000, 2, 198, 4),
	RK3066_PLL_RATE( 384000000, 2, 128, 4),
	RK3066_PLL_RATE( 300000000, 1,  50, 4),
	RK3066_PLL_RATE( 297000000, 2, 198, 8),
	RK3066_PLL_RATE( 148500000, 2,  99, 8),
	{ /* sentinel */ },
};

static struct rockchip_pll_clock rk3288_pll_clks[] __initdata = {
	[apll] = PLL(pll_rk3066, 0, "apll", "xin24m", 0, RK3288_PLL_CON(0),
		     RK3288_MODE_CON, 0, 6, rk3288_apll_rates),
	[dpll] = PLL(pll_rk3066, 0, "dpll", "xin24m", 0, RK3288_PLL_CON(4),
		     RK3288_MODE_CON, 4, 5, NULL),
	[cpll] = PLL(pll_rk3066, 0, "cpll", "xin24m", 0, RK3288_PLL_CON(8),
		     RK3288_MODE_CON, 8, 7, rk3288_cpll_rates),
	[gpll] = PLL(pll_rk3066, 0, "gpll", "xin24m", 0, RK3288_PLL_CON(12),
		     RK3288_MODE_CON, 12, 8, rk3288_gpll_rates),
	[npll] = PLL(pll_rk3066, 0, "npll", "xin24m", 0, RK3288_PLL_CON(16),
		     RK3288_MODE_CON, 14, 9, NULL),
};


#define MFLAGS CLK_MUX_HIWORD_MASK
static struct rockchip_mux_clock rk3288_mux_clks[] __initdata = {
};

/* 2 ^ (val + 1) */
static struct clk_div_table div_core_peri_t[] = {
	{ .val = 0, .div = 2 },
	{ .val = 1, .div = 4 },
	{ .val = 2, .div = 8 },
	{ .val = 3, .div = 16 },
	{ /* sentinel */},
};

static struct clk_div_table div_aclk_core_t[] = {
	{ .val = 0, .div = 1 },
	{ .val = 1, .div = 2 },
	{ .val = 2, .div = 3 },
	{ .val = 3, .div = 4 },
	{ .val = 4, .div = 8 },
	{ /* sentinel */},
};

#define DFLAGS CLK_DIVIDER_HIWORD_MASK
static struct rockchip_div_clock rk3288_div_clks[] __initdata = {
	/* these two are set by the cpuclk and should not be changed */
/*	DIV(0, "div_core_peri", "armclk", RK2928_CLKSEL_CON(0), 6, 2, 0, DFLAGS | CLK_DIVIDER_READ_ONLY, div_core_peri_t),
	DIV(0, "div_aclk_core", "armclk", RK2928_CLKSEL_CON(1), 3, 3, 0, DFLAGS | CLK_DIVIDER_READ_ONLY, div_aclk_core_t),
*/
};

#define GFLAGS (CLK_GATE_HIWORD_MASK | CLK_GATE_SET_TO_DISABLE)
static struct rockchip_gate_clock rk3288_gate_clks[] __initdata = {
};


struct rockchip_clk_init_table rk3288_clk_init_tbl[] __initdata = {
};

static void __init rk3288_clock_apply_init_table(void)
{
}

static void __init rk3288_clk_init(struct device_node *np)
{
	void __iomem *reg_base, *reg_grf_soc_status;

	reg_base = of_iomap(np, 0);
	if (!reg_base) {
		pr_err("%s: could not map cru region\n", __func__);
		return;
	}

	reg_grf_soc_status = of_iomap(np, 1);
	if (!reg_grf_soc_status) {
		pr_err("%s: could not map soc_status register\n", __func__);
		return;
	}

	rockchip_clk_init(np, reg_base, NR_CLKS);

	rockchip_clk_register_plls(rk3288_pll_clks,
				   ARRAY_SIZE(rk3288_pll_clks),
				   reg_grf_soc_status);

	rockchip_clk_register_mux(rk3288_mux_clks,
				  ARRAY_SIZE(rk3288_mux_clks));
	rockchip_clk_register_div(rk3288_div_clks,
				  ARRAY_SIZE(rk3288_div_clks));
	rockchip_clk_register_gate(rk3288_gate_clks,
				   ARRAY_SIZE(rk3288_gate_clks));

//	rockchip_clk_register_armclk(SCLK_ARMCLK, "armclk", mux_armclk_p,
//				     ARRAY_SIZE(mux_armclk_p), reg_base, np);

	rockchip_register_softrst(np, 9, reg_base + RK3288_SOFTRST_CON(0),
				  ROCKCHIP_SOFTRST_HIWORD_MASK);

	rockchip_clk_apply_init_table = rk3288_clock_apply_init_table;
}
CLK_OF_DECLARE(rk3288_cru, "rockchip,rk3288-cru", rk3288_clk_init);
