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

#include <linux/init.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/clockchips.h>
#include "arm_arch_timer.h"

#define TIMER_LOAD_COUNT0		0x00
#define TIMER_LOAD_COUNT1		0x04
#define TIMER_CURRENT_VALUE0		0x08
#define TIMER_CURRENT_VALUE1		0x0c
#define TIMER_CONTROL_REG		0x10
#define TIMER_INT_STATUS		0x18

#define TIMER_DISABLE			(0 << 0)
#define TIMER_ENABLE			(1 << 0)
#define TIMER_MODE_FREE_RUNNING		(0 << 1)
#define TIMER_MODE_USER_DEFINED_COUNT	(1 << 1)
#define TIMER_INT_MASK			(0 << 2)
#define TIMER_INT_UNMASK		(1 << 2)

static __init void rk3288_arch_timer_init(struct device_node *np)
{
	void __iomem *reg_base;

	reg_base = of_io_request_and_map(np, 0, "rk3288-armv7-timer");
	if (!reg_base) {
		pr_warn("%s: Can't get resource\n", __func__);
		return;
	}

	writel(TIMER_DISABLE, reg_base + TIMER_CONTROL_REG);

	writel(0xffffffff, reg_base + TIMER_LOAD_COUNT0);
	writel(0xffffffff, reg_base + TIMER_LOAD_COUNT1);

	writel(TIMER_ENABLE | TIMER_MODE_FREE_RUNNING,
	       reg_base + TIMER_CONTROL_REG);

	arch_timer_init(np);
}
CLOCKSOURCE_OF_DECLARE(rk3288_arch_timer, "rockchip,rk3288-armv7-timer",
		       rk3288_arch_timer_init);
