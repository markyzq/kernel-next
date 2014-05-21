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

PNAME(mux_pll_p)	= { "xin24m", "xin32k" };

static struct rockchip_pll_clock rk3288_pll_clks[] __initdata = {
	[apll] = PLL(pll_rk3066, 0, "apll", mux_pll_p, 0, RK3288_PLL_CON(0),
		     RK3288_MODE_CON, 0, 6, rk3288_apll_rates),
	[dpll] = PLL(pll_rk3066, 0, "dpll", mux_pll_p, 0, RK3288_PLL_CON(4),
		     RK3288_MODE_CON, 4, 5, NULL),
	[cpll] = PLL(pll_rk3066, 0, "cpll", mux_pll_p, 0, RK3288_PLL_CON(8),
		     RK3288_MODE_CON, 8, 7, rk3288_cpll_rates),
	[gpll] = PLL(pll_rk3066, 0, "gpll", mux_pll_p, 0, RK3288_PLL_CON(12),
		     RK3288_MODE_CON, 12, 8, rk3288_gpll_rates),
	[npll] = PLL(pll_rk3066, 0, "npll",  mux_pll_p, 0, RK3288_PLL_CON(16),
		     RK3288_MODE_CON, 14, 9, NULL),
};

/* included:
 * clksels_con0
 * clksels_con1
 * clksels_con2
 * clksels_con3
 * clksels_con4
 * clksels_con5
 * clksels_con6
 * clksels_con7
 * clksels_con8
 * clksels_con9
 * clksels_con10
 * clksels_con11
 * clksels_con12
 * clksels_con13
 * clksels_con14
 * clksels_con15
 * clksels_con16
 * clksels_con17
 * clksels_con18
 * clksels_con19
 * clksels_con20
 * clksels_con21
 * clksels_con22
 * 
 * clksels_con24
 * clksels_con25
 * clksels_con26
 * clksels_con27
 * clksels_con28
 * clksels_con29
 * clksels_con30
 * clksels_con31
 * 
 * clksels_con33
 * clksels_con34
 * clksels_con35
 * clksels_con36
 * clksels_con37
 * clksels_con38
 * clksels_con39
 * clksels_con40
 * clksels_con41
 * clksels_con42
 */

PNAME(mux_armclk_p) = { "apll_core", "gpll_core" };
PNAME(mux_ddrphy_p) = { "dpll_ddr", "gpll_ddr" };
PNAME(mux_aclk_bus_src_p) = { "cpll_aclk_bus", "gpll_aclk_bus" };

PNAME(mux_pll_src_cpll_gpll_p)	= { "cpll", "gpll" };
PNAME(mux_pll_src_cpll_gpll_24m_24m_p)	= { "cpll", "gpll", "xin24m", "xin24m" };
PNAME(mux_pll_src_npll_cpll_gpll_p)	= { "npll", "cpll", "gpll" };
PNAME(mux_pll_src_cpll_gpll_npll_p)	= { "cpll", "gpll", "npll" };
PNAME(mux_pll_src_cpll_gpll_usb480m_p) = { "cpll", "gpll", "usb480m" };
PNAME(mux_i2s_pre_p) = { "i2s_src", "i2s_frac", "i2s_clkin", "xin12m" };
PNAME(mux_i2s_clkout_p) = { "i2s_pre", "xin12m" };
PNAME(mux_spdif_p) = { "spdif_pre", "spdif_frac", "xin12m" };
PNAME(mux_spdif_8ch_p) = { "spdif_8ch_pre", "spdif_8ch_frac", "xin12m" };

PNAME(mux_uart0_pll_p) = { "cpll", "gpll", "usb480m", "npll" };

PNAME(mux_uart0_p) = { "gate_div_uart0", "gate_frac_uart0", "xin24m" };
PNAME(mux_uart1_p) = { "gate_div_uart1", "gate_frac_uart1", "xin24m" };
PNAME(mux_uart2_p) = { "gate_div_uart2", "gate_frac_uart2", "xin24m" };
PNAME(mux_uart3_p) = { "gate_div_uart3", "gate_frac_uart3", "xin24m" };
PNAME(mux_uart4_p) = { "gate_div_uart4", "gate_frac_uart4", "xin24m" };

PNAME(mux_cif_out_p) = { "cif_src", "xin24m" };

PNAME(mux_mac_p) = { "gate_div_mac_pll", "gmac_clkin" };
PNAME(mux_hsadc_p) = { "gate_div_hsadc_pll", "hsadc_ext" };
PNAME(mux_edp_24m_p) = { "edp_24m_clkin", "xin24m" };

PNAME(mux_tspout_p)	= { "cpll", "gpll", "npll", "io_27m_in" };


//FIXME: gate_something instead?
PNAME(mux_usbphy_480m_p) = { "otgphy0", "otgphy1", "otgphy2_480m" };

static struct clk_div_table div_hclk_bus_t[] = {
	{ .val = 0, .div = 1 },
	{ .val = 1, .div = 2 },
	{ .val = 3, .div = 4 },
	{ /* sentinel */},
};

#define MFLAGS CLK_MUX_HIWORD_MASK
#define DFLAGS CLK_DIVIDER_HIWORD_MASK
#define GFLAGS (CLK_GATE_HIWORD_MASK | CLK_GATE_SET_TO_DISABLE)

static struct rockchip_clk_branch rk3288_clk_branches[] __initdata = {
	/*
	 * Clock-Architecture Diagram 1
	 */

	GATE(0, "apll_core", "apll", RK3288_CLKGATE_CON(0), 1, 0, GFLAGS),
	GATE(0, "gpll_core", "gpll", RK3288_CLKGATE_CON(0), 2, 0, GFLAGS),
	COMPOSITE_NOGATE(0, "armclk", mux_armclk_p, 0,
			RK3288_CLKSEL_CON(0), 15, 1, MFLAGS, 8, 5, DFLAGS),

	/* these are set by cpufreq transistions should not be changed */
	COMPOSITE_NOMUX(0, "aclk_core_m0", "armclk", 0,
			RK3288_CLKSEL_CON(0), 0, 4, DFLAGS | CLK_DIVIDER_READ_ONLY,
			RK3288_CLKGATE_CON(12), 5, GFLAGS),
	COMPOSITE_NOMUX(0, "aclk_core_mp", "armclk", 0,
			RK3288_CLKSEL_CON(0), 4, 4, DFLAGS | CLK_DIVIDER_READ_ONLY,
			RK3288_CLKGATE_CON(12), 6, GFLAGS),
	COMPOSITE_NOMUX(0, "armcore0", "armclk", 0,
			RK3288_CLKSEL_CON(36), 0, 3, DFLAGS | CLK_DIVIDER_READ_ONLY,
			RK3288_CLKGATE_CON(12), 0, GFLAGS),
	COMPOSITE_NOMUX(0, "armcore1", "armclk", 0,
			RK3288_CLKSEL_CON(36), 4, 3, DFLAGS | CLK_DIVIDER_READ_ONLY,
			RK3288_CLKGATE_CON(12), 1, GFLAGS),
	COMPOSITE_NOMUX(0, "armcore2", "armclk", 0,
			RK3288_CLKSEL_CON(36), 8, 3, DFLAGS | CLK_DIVIDER_READ_ONLY,
			RK3288_CLKGATE_CON(12), 2, GFLAGS),
	COMPOSITE_NOMUX(0, "armcore3", "armclk", 0,
			RK3288_CLKSEL_CON(36), 12, 3, DFLAGS | CLK_DIVIDER_READ_ONLY,
			RK3288_CLKGATE_CON(12), 3, GFLAGS),
	COMPOSITE_NOMUX(0, "l2ram", "armclk", 0,
			RK3288_CLKSEL_CON(37), 0, 3, DFLAGS | CLK_DIVIDER_READ_ONLY,
			RK3288_CLKGATE_CON(12), 4, GFLAGS),
	COMPOSITE_NOMUX(0, "atclk", "armclk", 0,
			RK3288_CLKSEL_CON(37), 4, 5, DFLAGS | CLK_DIVIDER_READ_ONLY,
			RK3288_CLKGATE_CON(12), 7, GFLAGS),
	COMPOSITE_NOMUX(0, "pclk_dbg_pre", "armclk", 0,
			RK3288_CLKSEL_CON(37), 9, 5, DFLAGS | CLK_DIVIDER_READ_ONLY,
			RK3288_CLKGATE_CON(12), 8, GFLAGS),
	GATE(0, "pclk_dbg", "pclk_dbg_pre", 0, RK3288_CLKGATE_CON(12), 9, GFLAGS),
	GATE(0, "cs_dbg", "pclk_dbg_pre", 0, RK3288_CLKGATE_CON(12), 10, GFLAGS),
	GATE(0, "pclk_core_niu", "pclk_dbg_pre", 0, RK3288_CLKGATE_CON(12), 11, GFLAGS),

	GATE(0, "dpll_ddr", "dpll", 0, RK3288_CLKGATE_CON(0), 8, GFLAGS),
	GATE(0, "gpll_ddr", "gpll", 0, RK3288_CLKGATE_CON(0), 9, GFLAGS),
	COMPOSITE_NOGATE(0, "ddrphy", mux_ddrphy_p, 0,
			RK3288_CLKSEL_CON(26), 2, 1, MFLAGS, 0, 2, DFLAGS | CLK_DIVIDER_POWER_OF_TWO),

	GATE(0, "gpll_aclk_bus", "gpll", 0, RK3288_CLKGATE_CON(0), 10, GFLAGS),
	GATE(0, "cpll_aclk_bus", "cpll", 0, RK3288_CLKGATE_CON(0), 11, GFLAGS),
	COMPOSITE_NOGATE(0, "aclk_bus_src", mux_aclk_bus_src_p, 0,
			RK3288_CLKSEL_CON(1), 15, 1, MFLAGS, 3, 5, DFLAGS),
	DIV(0, "aclk_bus_pre", "aclk_bus_src", 0, RK3288_CLKSEL_CON(1), 0, 3, DFLAGS),
	GATE(0, "aclk_bus", "aclk_bus_pre", 0, RK3288_CLKGATE_CON(0), 3, GFLAGS),
	COMPOSITE_NOMUX(0, "pclk_bus", "aclk_bus_pre", 0,
			RK3288_CLKSEL_CON(1), 12, 3, DFLAGS,
			RK3288_CLKGATE_CON(0), 5, GFLAGS),
	COMPOSITE_NOMUX_DIVTBL(0, "hclk_bus", "aclk_bus_pre", 0,
			RK3288_CLKSEL_CON(1), 8, 2, DFLAGS, div_hclk_bus_t,
			RK3288_CLKGATE_CON(0), 4, GFLAGS),
	GATE(0, "c2c_host", "aclk_src", 0, RK3288_CLKGATE_CON(13), 8, GFLAGS),
	COMPOSITE_NOMUX(0, "crypto", "aclk_bus_pre", 0,
			RK3288_CLKSEL_CON(26), 6, 2, DFLAGS,
			RK3288_CLKGATE_CON(5), 4, GFLAGS),
	GATE(0, "gate_aclk_bus_2pmu", "aclk_bus_pre", 0, RK3288_CLKGATE_CON(0), 7, GFLAGS),

	COMPOSITE(0, "i2s_src", mux_pll_src_cpll_gpll_p, 0,
			RK3288_CLKSEL_CON(4), 15, 1, MFLAGS, 0, 7, DFLAGS,
			RK3288_CLKGATE_CON(4), 1, GFLAGS),
	MUX(0, "i2s_pre", mux_i2s_pre_p, 0, RK3288_CLKSEL_CON(4), 8, 2, MFLAGS),
	COMPOSITE_NODIV(0, "i2s_clkout", mux_i2s_clkout_p, 0,
			RK3288_CLKSEL_CON(4), 12, 1, MFLAGS,
			RK3288_CLKGATE_CON(4), 0, GFLAGS),
	COMPOSITE_FRAC(0, "i2s_frac", "i2s_src", 0, RK3288_CLKGATE_CON(8), 0,
			RK3288_CLKGATE_CON(4), 2, GFLAGS),
	GATE(0, "sclk_i2s", "i2s_pre", 0, RK3288_CLKGATE_CON(4), 3, GFLAGS),

	MUX(0, "spdif_src", mux_pll_src_cpll_gpll_p, 0, RK3288_CLKSEL_CON(5), 15, 1, MFLAGS),
	COMPOSITE_NOMUX(0, "spdif_pre", "spdif_src", 0,
			RK3288_CLKSEL_CON(5), 0, 7, DFLAGS,
			RK3288_CLKGATE_CON(4), 4, GFLAGS),
	COMPOSITE_FRAC(0, "spdif_frac", "spdif_src", 0, RK3288_CLKGATE_CON(9), 0,
			RK3288_CLKGATE_CON(4), 5, GFLAGS),
	COMPOSITE_NODIV(0, "sclk_spdif", mux_spdif_p, 0,
			RK3288_CLKSEL_CON(5), 8, 2, MFLAGS,
			RK3288_CLKGATE_CON(4), 6, GFLAGS),
	COMPOSITE_NOMUX(0, "spdif_8ch_pre", "spdif_src", 0,
			RK3288_CLKSEL_CON(40), 0, 7, DFLAGS,
			RK3288_CLKGATE_CON(4), 7, GFLAGS),
	COMPOSITE_FRAC(0, "spdif_8ch_frac", "spdif_8ch_src", 0, RK3288_CLKGATE_CON(41), 0,
			RK3288_CLKGATE_CON(4), 8, GFLAGS),
	COMPOSITE_NODIV(0, "sclk_spdif_8ch", mux_spdif_8ch_p, 0,
			RK3288_CLKSEL_CON(40), 8, 2, MFLAGS,
			RK3288_CLKGATE_CON(4), 9, GFLAGS),

	GATE(0, "sclk_acc_efuse", "xin24m", RK3288_CLKGATE_CON(0), 12, 0, GFLAGS),

	GATE(0, "sclk_timer0", "xin24m", RK3288_CLKGATE_CON(1), 0, 0, GFLAGS),
	GATE(0, "sclk_timer1", "xin24m", RK3288_CLKGATE_CON(1), 1, 0, GFLAGS),
	GATE(0, "sclk_timer2", "xin24m", RK3288_CLKGATE_CON(1), 2, 0, GFLAGS),
	GATE(0, "sclk_timer3", "xin24m", RK3288_CLKGATE_CON(1), 3, 0, GFLAGS),
	GATE(0, "sclk_timer4", "xin24m", RK3288_CLKGATE_CON(1), 4, 0, GFLAGS),
	GATE(0, "sclk_timer5", "xin24m", RK3288_CLKGATE_CON(1), 5, 0, GFLAGS),

	/*
	 * Clock-Architecture Diagram 2
	 */

//FIXME aclk_vepu + aclk_vdpu -> hclk_vcodec


	COMPOSITE(0, "aclk_vio0", mux_pll_src_cpll_gpll_usb480m_p, 0,
			RK3288_CLKSEL_CON(31), 6, 2, MFLAGS, 0, 5, DFLAGS,
			RK3288_CLKGATE_CON(3), 0, GFLAGS),
	DIV(0, "hclk_vio", "aclk_vio0", 0, RK3288_CLKSEL_CON(28), 8, 5, DFLAGS),
	COMPOSITE(0, "aclk_vio1", mux_pll_src_cpll_gpll_usb480m_p, 0,
			RK3288_CLKSEL_CON(31), 14, 2, MFLAGS, 8, 5, DFLAGS,
			RK3288_CLKGATE_CON(3), 2, GFLAGS),

	COMPOSITE(0, "aclk_rga", mux_pll_src_cpll_gpll_usb480m_p, 0,
			RK3288_CLKSEL_CON(30), 6, 2, MFLAGS, 0, 5, DFLAGS,
			RK3288_CLKGATE_CON(3), 4, GFLAGS),
	COMPOSITE(0, "sclk_rga", mux_pll_src_cpll_gpll_usb480m_p, 0,
			RK3288_CLKSEL_CON(30), 14, 2, MFLAGS, 8, 5, DFLAGS,
			RK3288_CLKGATE_CON(3), 5, GFLAGS),

	COMPOSITE(0, "dclk_lcdc0", mux_pll_src_cpll_gpll_npll_p, 0,
			RK3288_CLKSEL_CON(27), 0, 2, MFLAGS, 8, 8, DFLAGS,
			RK3288_CLKGATE_CON(3), 1, GFLAGS),
	COMPOSITE(0, "dclk_lcdc1", mux_pll_src_cpll_gpll_npll_p, 0,
			RK3288_CLKSEL_CON(29), 6, 2, MFLAGS, 8, 8, DFLAGS,
			RK3288_CLKGATE_CON(3), 3, GFLAGS),

	COMPOSITE_NODIV(0, "sclk_edp_24m", mux_edp_24m_p, 0,
			RK3288_CLKSEL_CON(28), 15, 1, MFLAGS,
			RK3288_CLKGATE_CON(3), 12, GFLAGS),
	COMPOSITE(0, "sclk_edp", mux_pll_src_cpll_gpll_npll_p, 0,
			RK3288_CLKSEL_CON(28), 6, 2, MFLAGS, 0, 6, DFLAGS,
			RK3288_CLKGATE_CON(3), 13, GFLAGS),

	COMPOSITE(0, "sclk_isp", mux_pll_src_cpll_gpll_npll_p, 0,
			RK3288_CLKSEL_CON(6), 6, 2, MFLAGS, 0, 6, DFLAGS,
			RK3288_CLKGATE_CON(3), 14, GFLAGS),
	COMPOSITE(0, "sclk_isp_jpe", mux_pll_src_cpll_gpll_npll_p, 0,
			RK3288_CLKSEL_CON(6), 14, 2, MFLAGS, 8, 6, DFLAGS,
			RK3288_CLKGATE_CON(3), 15, GFLAGS),

	GATE(0, "sclk_hdmi_hdcp", "xin24m", RK3288_CLKGATE_CON(5), 12, 0, GFLAGS),
	GATE(0, "sclk_hdmi_cec", "xin32k", RK3288_CLKGATE_CON(5), 11, 0, GFLAGS),

	COMPOSITE(0, "aclk_hevc", mux_pll_src_cpll_gpll_npll_p, 0,
			RK3288_CLKSEL_CON(39), 14, 2, MFLAGS, 8, 5, DFLAGS,
			RK3288_CLKGATE_CON(13), 13, GFLAGS),
	DIV(0, "hclk_hevc", "aclk_hevc", 0, RK3288_CLKSEL_CON(40), 12, 2, DFLAGS),

	COMPOSITE(0, "sclk_hevc_cabac", mux_pll_src_cpll_gpll_npll_p, 0,
			RK3288_CLKSEL_CON(42), 6, 2, MFLAGS, 0, 5, DFLAGS,
			RK3288_CLKGATE_CON(13), 14, GFLAGS),
	COMPOSITE(0, "sclk_hevc_core", mux_pll_src_cpll_gpll_npll_p, 0,
			RK3288_CLKSEL_CON(42), 14, 2, MFLAGS, 8, 5, DFLAGS,
			RK3288_CLKGATE_CON(13), 15, GFLAGS),

	COMPOSITE_NODIV(0, "cif_src", mux_pll_src_cpll_gpll_p, 0,
			RK3288_CLKSEL_CON(26), 8, 1, MFLAGS,
			RK3288_CLKGATE_CON(3), 7, GFLAGS),

	COMPOSITE_NOGATE(0, "sclk_cif_out", mux_cif_out_p, 0,
			RK3288_CLKSEL_CON(26), 15, 1, MFLAGS, 9, 5, DFLAGS),

	DIV(0, "pclk_pd_alive", "gpll", 0, RK3288_CLKSEL_CON(33), 8, 5, DFLAGS),
	COMPOSITE_NOMUX(0, "pclk_pd_pmu", "gpll", 0,
			RK3288_CLKSEL_CON(33), 0, 5, DFLAGS,
			RK3288_CLKGATE_CON(5), 8, GFLAGS),

	COMPOSITE(0, "sclk_gpu", mux_pll_src_cpll_gpll_usb480m_p, 0,
			RK3288_CLKSEL_CON(34), 6, 2, MFLAGS, 0, 5, DFLAGS,
			RK3288_CLKGATE_CON(5), 7, GFLAGS),

	COMPOSITE(0, "aclk_peri_src", mux_pll_src_cpll_gpll_p, 0,
			RK3288_CLKSEL_CON(10), 15, 1, MFLAGS, 0, 5, DFLAGS,
			RK3288_CLKGATE_CON(2), 0, GFLAGS),
	GATE(0, "aclk_peri", "aclk_peri_src", 0, RK3288_CLKGATE_CON(2), 1, GFLAGS),
	COMPOSITE_NOMUX(0, "hclk_peri", "aclk_peri_pre", 0,
			RK3288_CLKSEL_CON(10), 8, 2, DFLAGS | CLK_DIVIDER_POWER_OF_TWO,
			RK3288_CLKGATE_CON(2), 2, GFLAGS),
	COMPOSITE_NOMUX(0, "pclk_peri", "aclk_peri_pre", 0,
			RK3288_CLKSEL_CON(10), 12, 2, DFLAGS | CLK_DIVIDER_POWER_OF_TWO,
			RK3288_CLKGATE_CON(2), 3, GFLAGS),

	/*
	 * Clock-Architecture Diagram 3
	 */

	COMPOSITE(0, "sclk_spi0", mux_pll_src_cpll_gpll_p, 0,
			RK3288_CLKSEL_CON(25), 7, 1, MFLAGS, 0, 7, DFLAGS,
			RK3288_CLKGATE_CON(2), 9, GFLAGS),
	COMPOSITE(0, "sclk_spi1", mux_pll_src_cpll_gpll_p, 0,
			RK3288_CLKSEL_CON(25), 15, 1, MFLAGS, 8, 7, DFLAGS,
			RK3288_CLKGATE_CON(2), 10, GFLAGS),
	COMPOSITE(0, "sclk_spi2", mux_pll_src_cpll_gpll_p, 0,
			RK3288_CLKSEL_CON(39), 7, 1, MFLAGS, 0, 7, DFLAGS,
			RK3288_CLKGATE_CON(2), 11, GFLAGS),

	COMPOSITE(0, "sclk_sdmmc", mux_pll_src_cpll_gpll_24m_24m_p, 0,
			RK3288_CLKSEL_CON(11), 6, 2, MFLAGS, 0, 6, DFLAGS,
			RK3288_CLKGATE_CON(13), 0, GFLAGS),
	COMPOSITE(0, "sclk_sdio0", mux_pll_src_cpll_gpll_24m_24m_p, 0,
			RK3288_CLKSEL_CON(12), 6, 2, MFLAGS, 0, 6, DFLAGS,
			RK3288_CLKGATE_CON(13), 1, GFLAGS),
	COMPOSITE(0, "sclk_sdio1", mux_pll_src_cpll_gpll_24m_24m_p, 0,
			RK3288_CLKSEL_CON(34), 14, 2, MFLAGS, 8, 6, DFLAGS,
			RK3288_CLKGATE_CON(13), 2, GFLAGS),
	COMPOSITE(0, "sclk_emmc", mux_pll_src_cpll_gpll_24m_24m_p, 0,
			RK3288_CLKSEL_CON(12), 14, 2, MFLAGS, 8, 6, DFLAGS,
			RK3288_CLKGATE_CON(13), 3, GFLAGS),

	COMPOSITE(0, "sclk_tsp", mux_pll_src_cpll_gpll_npll_p, 0,
			RK3288_CLKSEL_CON(35), 6, 2, MFLAGS, 0, 5, DFLAGS,
			RK3288_CLKGATE_CON(4), 10, GFLAGS),
	COMPOSITE(0, "sclk_tspout", mux_tspout_p, 0,
			RK3288_CLKSEL_CON(35), 14, 2, MFLAGS, 8, 5, DFLAGS,
			RK3288_CLKGATE_CON(4), 11, GFLAGS),

	GATE(0, "sclk_otgphy0", "usb480m", 0, RK3288_CLKGATE_CON(13), 4, GFLAGS),
	GATE(0, "sclk_otgphy1", "usb480m", 0, RK3288_CLKGATE_CON(13), 5, GFLAGS),
	GATE(0, "sclk_otgphy2", "usb480m", 0, RK3288_CLKGATE_CON(13), 6, GFLAGS),
	GATE(0, "sclk_otg_adp", "xin32k", 0, RK3288_CLKGATE_CON(13), 7, GFLAGS),

	COMPOSITE_NOMUX(0, "sclk_tsadc", "xin32k", 0,
			RK3288_CLKSEL_CON(2), 0, 6, DFLAGS,
			RK3288_CLKGATE_CON(2), 7, GFLAGS),

	COMPOSITE_NOMUX(0, "sclk_saradc", "xin24m", 0,
			RK3288_CLKSEL_CON(24), 8, 8, DFLAGS,
			RK3288_CLKGATE_CON(2), 8, GFLAGS),

	GATE(0, "sclk_ps2c", "xin24m", 0, RK3288_CLKGATE_CON(5), 13, GFLAGS),

	COMPOSITE(0, "sclk_nandc0", mux_pll_src_cpll_gpll_p, 0,
			RK3288_CLKSEL_CON(38), 7, 1, MFLAGS, 0, 5, DFLAGS,
			RK3288_CLKGATE_CON(5), 5, GFLAGS),
	COMPOSITE(0, "sclk_nandc1", mux_pll_src_cpll_gpll_p, 0,
			RK3288_CLKSEL_CON(38), 15, 1, MFLAGS, 8, 5, DFLAGS,
			RK3288_CLKGATE_CON(5), 6, GFLAGS),

	COMPOSITE(0, "uart0_pll", mux_uart0_pll_p, 0,
			RK3288_CLKSEL_CON(13), 13, 2, MFLAGS, 0, 7, DFLAGS,
			RK3288_CLKGATE_CON(1), 8, GFLAGS),
	COMPOSITE_FRAC(0, "uart0_frac", "uart0_pll", 0, RK3288_CLKSEL_CON(17), 0,
			RK3288_CLKGATE_CON(1), 9, GFLAGS),
	MUX(0, "mux_uart0", mux_uart0_p, 0, RK3288_CLKSEL_CON(13), 8, 2, MFLAGS),
	MUX(0, "uart_pll", mux_pll_src_cpll_gpll_p, 0, RK3288_CLKSEL_CON(13), 15, 1, MFLAGS),
	COMPOSITE_NOMUX(0, "uart1_pll", "uart_pll", 0,
			RK3288_CLKSEL_CON(14), 0, 7, DFLAGS,
			RK3288_CLKGATE_CON(1), 10, GFLAGS),
	COMPOSITE_FRAC(0, "uart1_frac", "uart0_pll", 0, RK3288_CLKSEL_CON(18), 0,
			RK3288_CLKGATE_CON(1), 11, GFLAGS),
	MUX(0, "mux_uart1", mux_uart1_p, 0, RK3288_CLKSEL_CON(14), 8, 2, MFLAGS),
	COMPOSITE_NOMUX(0, "uart2_pll", "uart_pll", 0,
			RK3288_CLKSEL_CON(15), 0, 7, DFLAGS,
			RK3288_CLKGATE_CON(1), 12, GFLAGS),
	COMPOSITE_FRAC(0, "uart2_frac", "uart0_pll", 0, RK3288_CLKSEL_CON(19), 0,
			RK3288_CLKGATE_CON(1), 13, GFLAGS),
	MUX(0, "mux_uart2", mux_uart2_p, 0, RK3288_CLKSEL_CON(15), 8, 2, MFLAGS),
	COMPOSITE_NOMUX(0, "uart3_pll", "uart_pll", 0,
			RK3288_CLKSEL_CON(16), 0, 7, DFLAGS,
			RK3288_CLKGATE_CON(1), 14, GFLAGS),
	COMPOSITE_FRAC(0, "uart3_frac", "uart0_pll", 0, RK3288_CLKSEL_CON(20), 0,
			RK3288_CLKGATE_CON(1), 15, GFLAGS),
	MUX(0, "mux_uart3", mux_uart3_p, 0, RK3288_CLKSEL_CON(16), 8, 2, MFLAGS),
	COMPOSITE_NOMUX(0, "uart4_pll", "uart_pll", 0,
			RK3288_CLKSEL_CON(3), 0, 7, DFLAGS,
			RK3288_CLKGATE_CON(2), 12, GFLAGS),
	COMPOSITE_FRAC(0, "uart4_frac", "uart0_pll", 0, RK3288_CLKSEL_CON(7), 0,
			RK3288_CLKGATE_CON(2), 13, GFLAGS),
	MUX(0, "mux_uart4", mux_uart4_p, 0, RK3288_CLKSEL_CON(3), 8, 2, MFLAGS),

///////////////// clk_mac from here





/*
				clk_sel_con2: sel-con@0068 {
					testout_div: testout_div {
						compatible = "rockchip,rk3188-div-con";
						rockchip,bits = <8 5>;
						clocks = <&dummy>;
						clock-output-names = "testout_div";
						rockchip,div-type = <CLK_DIVIDER_PLUS_ONE>;
						#clock-cells = <0>;
					};
				};
*/

/*
				clk_sel_con11: sel-con@008c {
					compatible = "rockchip,rk3188-selcon";
					reg = <0x008c 0x4>;
					#address-cells = <1>;
					#size-cells = <1>;

					hsicphy_12m_div: hsicphy_12m_div {
						compatible = "rockchip,rk3188-div-con";
						rockchip,bits = <8 6>;
						clocks = <&hsicphy_480m>;
						clock-output-names = "hsicphy_12m_div";
						rockchip,div-type = <CLK_DIVIDER_PLUS_ONE>;
						#clock-cells = <0>;
					};

				};




				clk_gates4: gate-clk@0170 {
					compatible = "rockchip,rk3188-gate-clk";
					reg = <0x0170 0x4>;
					clocks =
						ok<&clk_i2s_out>,		ok<&clk_i2s_pll>,
						ok<&i2s_frac>,			ok<&clk_i2s>,

						ok<&spdif_div>,		ok<&spdif_frac>,
						ok<&clk_spdif>,		ok<&spdif_8ch_div>,

						ok<&spdif_8ch_frac>,		ok<&clk_spdif_8ch>,
						ok<&clk_tsp>,		ok<&clk_tspout>,

						<&clk_ddr>,		<&clk_ddr>,
						<&jtag_clkin>,		<&dummy>;

					clock-output-names =
						ok"clk_i2s_out",		ok"clk_i2s_pll",
						ok"i2s_frac",		ok"clk_i2s",

						ok"spdif_div",		ok"spdif_frac",
						ok"clk_spdif",		ok"spdif_8ch_div",

						ok"spdif_8ch_frac",		ok"clk_spdif_8ch",
						ok"clk_tsp",		ok"clk_tspout",

						// Not use these ddr gates
						"reserved",		"reserved",	   //"g_clk_ddrphy0",		"g_clk_ddrphy1",
						"clk_jtag",		"reserved";		//"testclk_gate_en";

                                            rockchip,suspend-clkgating-setting=<0xf000 0xf000>;
					#clock-cells = <1>;
				};
*/
////////////////

	//FIXME: naming
	MUX(0, "mux_usbphy_480m", mux_usbphy_480m_p, 0, RK3288_CLKSEL_CON(13), 11, 2, MFLAGS),

	MUX(0, "mux_mac_pll", mux_pll_src_npll_cpll_gpll_p, 0, RK3288_CLKSEL_CON(21), 0, 2, MFLAGS),
	MUX(0, "mux_mac", mux_mac_p, 0, RK3288_CLKSEL_CON(21), 4, 1, MFLAGS),
///////////////////////////
	MUX(0, "mux_hsadc_pll", mux_pll_src_cpll_gpll_p, RK3288_CLKSEL_CON(22), 0, 1, 0, MFLAGS),
//	MUX(0, "mux_hsadc_out", mux_hsadc_out_p, RK3288_CLKSEL_CON(22), 4, 1, 0, MFLAGS),
	//FIXME: mux_hsadc (from hsadc_out and hsadc_inv, in <CLKSEL_CON(22), 7, 1>




	DIV(0, "div_mac_pll", "mux_mac_pll", 0, RK3288_CLKSEL_CON(21), 8, 5, DFLAGS),
	DIV(0, "div_hsadc_pll", "mux_hsadc_pll", 0, RK3288_CLKSEL_CON(22), 8, 8, DFLAGS),



/*
				clk_sel_con29: sel-con@00d4 {
					compatible = "rockchip,rk3188-selcon";
					reg = <0x00d4 0x4>;
					#address-cells = <1>;
					#size-cells = <1>;

					hsicphy_480m: hsicphy_480m_mux {
						compatible = "rockchip,rk3188-mux-con";
						rockchip,bits = <0 2>;
						clocks = <&clk_cpll>, <&clk_gpll>, <&usbphy_480m>;
						clock-output-names = "hsicphy_480m";
						#clock-cells = <0>;
					};

					hsicphy_12m: hsicphy_12m_mux {
						compatible = "rockchip,rk3188-mux-con";
						rockchip,bits = <2 1>;
						clocks = <&clk_gates13 9>, <&hsicphy_12m_div>;
						clock-output-names = "hsicphy_12m";
						#clock-cells = <0>;
					};

					clkin_isp: clkin_isp {
						compatible = "rockchip,rk3188-mux-con";
						rockchip,bits = <3 1>;
						clocks = <&clk_gates16 3>, <&pclkin_isp_inv>;
						clock-output-names = "clkin_isp";
						#clock-cells = <0>;
					};

					clkin_cif: clkin_cif {
						compatible = "rockchip,rk3188-mux-con";
						rockchip,bits = <4 1>;
						clocks = <&clk_gates16 0>, <&pclkin_cif_inv>;
						clock-output-names = "clkin_cif";
						#clock-cells = <0>;
					};
				};
*/


	/* CLKGATE_CON_0 */

	/* CLKGATE_CON_2 */

	GATE(0, "gate_div_mac_pll", "div_mac_pll", RK3288_CLKGATE_CON(2), 5, 0, GFLAGS),
	GATE(0, "gate_div_hsadc_pll", "div_hsadc_pll", RK3288_CLKGATE_CON(2), 6, 0, GFLAGS),

	/* CLKGATE_CON_3 */

	GATE(0, "gate_hsicphy_480m", "mux_hsicphy_480m", RK3288_CLKGATE_CON(3), 6, 0, GFLAGS),
	/* FIXME: bits 8 to 11 are marked as FIXME */



/*
				clk_gates3: gate-clk@016c {
					compatible = "rockchip,rk3188-gate-clk";
					reg = <0x016c 0x4>;
					clocks =
						ok<&aclk_vio0>,		<&dclk_lcdc0>,
						ok<&aclk_vio1>,		<&dclk_lcdc1>,

						ok<&clk_rga>,			ok<&aclk_rga>,
						<&hsicphy_480m>,		<&clk_cif_pll>,

						<&dummy>,		<&clk_vepu>,
						<&dummy>,		<&clk_vdpu>,

						ok<&clk_edp_24m>,		ok<&clk_edp>,
						ok<&clk_isp>,		ok<&clk_isp_jpe>;

					clock-output-names =
						ok"aclk_vio0",		"dclk_lcdc0",
						ok"aclk_vio1",		"dclk_lcdc1",

						ok"clk_rga",		ok"aclk_rga",
						"hsicphy_480m",		"clk_cif_pll",

						//Not use hclk_vpu_gate tmp, fixme
						"reserved",		"clk_vepu",
						"reserved",		"clk_vdpu",

						ok"clk_edp_24m",		ok"clk_edp",
						ok"clk_isp",		ok"clk_isp_jpe";
                                                rockchip,suspend-clkgating-setting=<0x0000 0x0000>;

					#clock-cells = <1>;
				};

*/
	GATE(0, "gate_mac_rx", "mux_mac", RK3288_CLKGATE_CON(5), 0, 0, GFLAGS),
	GATE(0, "gate_mac_tx", "mux_mac", RK3288_CLKGATE_CON(5), 1, 0, GFLAGS),
	GATE(0, "gate_mac_ref", "mux_mac", RK3288_CLKGATE_CON(5), 2, 0, GFLAGS),
	GATE(0, "gate_mac_refout", "mux_mac", RK3288_CLKGATE_CON(5), 3, 0, GFLAGS),

	//FIXME what are these and are they really sourced from xin24m
	GATE(0, "g_clk_pvtm_core", "xin24m", RK3288_CLKGATE_CON(5), 9, 0, GFLAGS),
	GATE(0, "g_clk_pvtm_gpu", "xin24m", RK3288_CLKGATE_CON(5), 10, 0, GFLAGS),
	//FIXME
	GATE(0, "gate_usbphy480m", "usbphy_480m", RK3288_CLKGATE_CON(5), 15, 0, GFLAGS),
	GATE(0, "g_mipidsi_24m", "xin24m", RK3288_CLKGATE_CON(5), 15, 0, GFLAGS),

	/* CLKGATE_CON_6 */
	GATE(0, "gate_hclk_peri_matrix", "gate_hclk_peri", RK3288_CLKGATE_CON(6), 0, 0, GFLAGS),
	GATE(0, "gate_pclk_peri_matrix", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 1, 0, GFLAGS),
	GATE(0, "gate_aclk_peri_axi_matrix", "gate_aclk_peri", RK3288_CLKGATE_CON(6), 2, 0, GFLAGS),
	GATE(0, "gate_aclk_dmac2", "gate_aclk_peri", RK3288_CLKGATE_CON(6), 3, 0, GFLAGS),
	GATE(0, "gate_pclk_spi0", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 4, 0, GFLAGS),
	GATE(0, "gate_pclk_spi1", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 5, 0, GFLAGS),
	GATE(0, "gate_pclk_spi2", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 6, 0, GFLAGS),
	GATE(0, "gate_pclk_ps2c", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 7, 0, GFLAGS),
	GATE(0, "gate_pclk_uart0", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 8, 0, GFLAGS),
	GATE(0, "gate_pclk_uart1", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 9, 0, GFLAGS),
	GATE(0, "gate_pclk_uart3", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 11, 0, GFLAGS),
	GATE(0, "gate_pclk_uart4", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 12, 0, GFLAGS),
	GATE(0, "gate_pclk_i2c2", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 13, 0, GFLAGS),
	GATE(0, "gate_pclk_i2c3", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 14, 0, GFLAGS),
	GATE(0, "gate_pclk_i2c4", "gate_pclk_peri", RK3288_CLKGATE_CON(6), 15, 0, GFLAGS),

	/* CLKGATE_CON_7 */
	GATE(0, "gate_pclk_i2c5", "gate_pclk_peri", RK3288_CLKGATE_CON(7), 0, 0, GFLAGS),
	GATE(0, "gate_pclk_saradc", "gate_pclk_peri", RK3288_CLKGATE_CON(7), 1, 0, GFLAGS),
	GATE(0, "gate_pclk_tsadc", "gate_pclk_peri", RK3288_CLKGATE_CON(7), 2, 0, GFLAGS),
	GATE(0, "gate_pclk_sim", "gate_pclk_peri", RK3288_CLKGATE_CON(7), 3, 0, GFLAGS),
	GATE(0, "gate_hclk_otg0", "gate_hclk_peri", RK3288_CLKGATE_CON(7), 4, 0, GFLAGS),
	//FIXME what is pmu_hclk_otg0
	GATE(0, "gate_pmu_hclk_otg0", "gate_hclk_peri", RK3288_CLKGATE_CON(7), 5, 0, GFLAGS),
	GATE(0, "gate_hclk_host0", "gate_hclk_peri", RK3288_CLKGATE_CON(7), 6, 0, GFLAGS),
	GATE(0, "gate_hclk_host1", "gate_hclk_peri", RK3288_CLKGATE_CON(7), 7, 0, GFLAGS),
	GATE(0, "gate_hclk_hsic", "gate_hclk_peri", RK3288_CLKGATE_CON(7), 8, 0, GFLAGS),
	GATE(0, "gate_hclk_usb_peri", "gate_hclk_peri", RK3288_CLKGATE_CON(7), 9, 0, GFLAGS),
	GATE(0, "gate_hclk_peri_ahb_arbi", "gate_hclk_peri", RK3288_CLKGATE_CON(7), 10, 0, GFLAGS),
	GATE(0, "gate_aclk_peri_niu", "gate_aclk_peri", RK3288_CLKGATE_CON(7), 11, 0, GFLAGS),
	GATE(0, "gate_hclk_emem", "gate_hclk_peri", RK3288_CLKGATE_CON(7), 12, 0, GFLAGS),
	GATE(0, "gate_hclk_mem", "gate_hclk_peri", RK3288_CLKGATE_CON(7), 13, 0, GFLAGS),
	GATE(0, "gate_hclk_nandc0", "gate_hclk_peri", RK3288_CLKGATE_CON(7), 14, 0, GFLAGS),
	GATE(0, "gate_hclk_nandc1", "gate_hclk_peri", RK3288_CLKGATE_CON(7), 14, 0, GFLAGS),

	/* CLKGATE_CON_8 */
	GATE(0, "gate_aclk_gmac", "gate_aclk_peri", RK3288_CLKGATE_CON(8), 0, 0, GFLAGS),
	GATE(0, "gate_pclk_gmac", "gate_pclk_peri", RK3288_CLKGATE_CON(8), 1, 0, GFLAGS),
	//FIXME: is this really correct, hclk_gps being sourced from aclk_peri?
	GATE(0, "gate_hclk_gps", "gate_aclk_peri", RK3288_CLKGATE_CON(8), 2, 0, GFLAGS),
	//hclk_sdmmc
	GATE(0, "gate_hclk_mmc0", "gate_hclk_peri", RK3288_CLKGATE_CON(8), 3, 0, GFLAGS),
	//hclk_sdio0 and hclk_sdio1
	GATE(0, "gate_hclk_mmc1", "gate_hclk_peri", RK3288_CLKGATE_CON(8), 4, 0, GFLAGS),
	GATE(0, "gate_hclk_mmc2", "gate_hclk_peri", RK3288_CLKGATE_CON(8), 5, 0, GFLAGS),
	//hclk_emmc
	GATE(0, "gate_hclk_mmc3", "gate_hclk_peri", RK3288_CLKGATE_CON(8), 6, 0, GFLAGS),
	GATE(0, "gate_hclk_hsadc", "gate_hclk_peri", RK3288_CLKGATE_CON(8), 7, 0, GFLAGS),
	GATE(0, "gate_hclk_tsp", "gate_hclk_peri", RK3288_CLKGATE_CON(8), 8, 0, GFLAGS),
	//FIXME: these are source from dummy fixed clocks in the upstream source
	GATE(0, "gate_hclk_hsadc_0_tsp", "dummy", RK3288_CLKGATE_CON(8), 9, 0, GFLAGS),
	GATE(0, "gate_hclk_hsadc_1_tsp", "dummy", RK3288_CLKGATE_CON(8), 10, 0, GFLAGS),
	GATE(0, "gate_clk_27m_tsp", "dummy", RK3288_CLKGATE_CON(8), 11, 0, GFLAGS),
	GATE(0, "gate_aclk_mmu", "gate_aclk_peri", RK3288_CLKGATE_CON(8), 12, 0, GFLAGS),

	/* CLKGATE_CON_9 */
	//FIXME is this really empty?
	//FIXME bits 0 and 1 seem to contain "aclk_video_gate_en", "hclk_video_clock_en",
	//FIXME what are these and where do they come from (originally "dummy")

	/* CLKGATE_CON_10 */
	GATE(0, "gate_pclk_pwm", "gate_pclk_bus", RK3288_CLKGATE_CON(10), 0, 0, GFLAGS),
	GATE(0, "gate_pclk_timer", "gate_pclk_bus", RK3288_CLKGATE_CON(10), 1, 0, GFLAGS),
	GATE(0, "gate_pclk_i2c0", "gate_pclk_bus", RK3288_CLKGATE_CON(10), 2, 0, GFLAGS),
	GATE(0, "gate_pclk_i2c1", "gate_pclk_bus", RK3288_CLKGATE_CON(10), 3, 0, GFLAGS),
	GATE(0, "gate_aclk_intmem", "gate_aclk_bus", RK3288_CLKGATE_CON(10), 4, 0, GFLAGS),
	//FIXME why are these 3 labeled "clk" when they are indeed sourced from aclk_bus
	GATE(0, "gate_clk_intmem0", "gate_aclk_bus", RK3288_CLKGATE_CON(10), 5, 0, GFLAGS),
	GATE(0, "gate_clk_intmem1", "gate_aclk_bus", RK3288_CLKGATE_CON(10), 6, 0, GFLAGS),
	GATE(0, "gate_clk_intmem2", "gate_aclk_bus", RK3288_CLKGATE_CON(10), 7, 0, GFLAGS),
	GATE(0, "gate_hclk_i2s", "gate_hclk_bus", RK3288_CLKGATE_CON(10), 8, 0, GFLAGS),
	GATE(0, "gate_hclk_rom", "gate_hclk_bus", RK3288_CLKGATE_CON(10), 9, 0, GFLAGS),
	GATE(0, "gate_hclk_spdif", "gate_hclk_bus", RK3288_CLKGATE_CON(10), 10, 0, GFLAGS),
	GATE(0, "gate_hclk_spdif_8ch", "gate_hclk_bus", RK3288_CLKGATE_CON(10), 11, 0, GFLAGS),
	GATE(0, "gate_aclk_dmac1", "gate_aclk_bus", RK3288_CLKGATE_CON(10), 12, 0, GFLAGS),
	GATE(0, "gate_aclk_strc_sys", "gate_aclk_bus", RK3288_CLKGATE_CON(10), 13, 0, GFLAGS),
	//FIXME: why are these marked as reserved originally?
	GATE(0, "gate_pclk_ddrupctl0", "gate_pclk_bus", RK3288_CLKGATE_CON(10), 14, 0, GFLAGS),
	GATE(0, "gate_pclk_publ0", "gate_pclk_bus", RK3288_CLKGATE_CON(10), 15, 0, GFLAGS),

	/* CLKGATE_CON_11 */
	//FIXME: why are these 2 marked as reserved originally?
	GATE(0, "gate_pclk_ddrupctl1", "gate_pclk_bus", RK3288_CLKGATE_CON(11), 0, 0, GFLAGS),
	GATE(0, "gate_pclk_publ1", "gate_pclk_bus", RK3288_CLKGATE_CON(11), 1, 0, GFLAGS),
	GATE(0, "gate_pclk_efuse_1024", "gate_pclk_bus", RK3288_CLKGATE_CON(11), 2, 0, GFLAGS),
	GATE(0, "gate_pclk_tzpc", "gate_pclk_bus", RK3288_CLKGATE_CON(11), 3, 0, GFLAGS),
	//FIXME: why are these 2 marked as reserved and where do they come from
	GATE(0, "gate_nclk_ddrupctl0", "dummy", RK3288_CLKGATE_CON(11), 4, 0, GFLAGS),
	GATE(0, "gate_nclk_ddrupctl1", "dummy", RK3288_CLKGATE_CON(11), 5, 0, GFLAGS),
	GATE(0, "gate_aclk_crypto", "gate_aclk_bus", RK3288_CLKGATE_CON(11), 6, 0, GFLAGS),
	GATE(0, "gate_hclk_crypto", "gate_hclk_bus", RK3288_CLKGATE_CON(11), 7, 0, GFLAGS),
	GATE(0, "gate_aclk_ccp", "gate_aclk_bus", RK3288_CLKGATE_CON(11), 8, 0, GFLAGS),
	GATE(0, "gate_pclk_uart2", "gate_pclk_bus", RK3288_CLKGATE_CON(11), 9, 0, GFLAGS),
	GATE(0, "gate_pclk_efuse_256", "gate_pclk_bus", RK3288_CLKGATE_CON(11), 10, 0, GFLAGS),
	//FIXME what is the difference between pclk_pwm and pclk_rkpwm?
	GATE(0, "gate_pclk_rkpwm", "gate_pclk_bus", RK3288_CLKGATE_CON(11), 11, 0, GFLAGS),

	/* CLKGATE_CON_12 */

	GATE(0, "gate_cs_dbg_clk", "gate_pclk_dbg", RK3288_CLKGATE_CON(12), 10, 0, GFLAGS),

	/* CLKGATE_CON_13 */
	/* FIXME: where does xin12m come from */
	GATE(0, "gate_hsic_12m", "xin12m", RK3288_CLKGATE_CON(13), 9, 0, GFLAGS),
	GATE(0, "gate_lcdc_pwm0", "xin24m", RK3288_CLKGATE_CON(13), 10, 0, GFLAGS),
	GATE(0, "gate_lcdc_pwm1", "xin24m", RK3288_CLKGATE_CON(13), 11, 0, GFLAGS),
	//FIXME what is this
	GATE(0, "gate_wifi", "dummy", RK3288_CLKGATE_CON(13), 12, 0, GFLAGS),

	/* CLKGATE_CON_14 */
	/* FIXME: has the pclk_pd_alive a gate? */
	GATE(0, "gate_pclk_gpio1", "div_pclk_pd_alive", RK3288_CLKGATE_CON(14), 1, 0, GFLAGS),
	GATE(0, "gate_pclk_gpio2", "div_pclk_pd_alive", RK3288_CLKGATE_CON(14), 2, 0, GFLAGS),
	GATE(0, "gate_pclk_gpio3", "div_pclk_pd_alive", RK3288_CLKGATE_CON(14), 3, 0, GFLAGS),
	GATE(0, "gate_pclk_gpio4", "div_pclk_pd_alive", RK3288_CLKGATE_CON(14), 4, 0, GFLAGS),
	GATE(0, "gate_pclk_gpio5", "div_pclk_pd_alive", RK3288_CLKGATE_CON(14), 5, 0, GFLAGS),
	GATE(0, "gate_pclk_gpio6", "div_pclk_pd_alive", RK3288_CLKGATE_CON(14), 6, 0, GFLAGS),
	GATE(0, "gate_pclk_gpio7", "div_pclk_pd_alive", RK3288_CLKGATE_CON(14), 7, 0, GFLAGS),
	GATE(0, "gate_pclk_gpio8", "div_pclk_pd_alive", RK3288_CLKGATE_CON(14), 8, 0, GFLAGS),
	GATE(0, "gate_pclk_grf", "div_pclk_pd_alive", RK3288_CLKGATE_CON(14), 11, 0, GFLAGS),
	GATE(0, "gate_pclk_alive_niu", "div_pclk_pd_alive", RK3288_CLKGATE_CON(14), 12, 0, GFLAGS),

	/* CLKGATE_CON_15 */
	//FIXME: does hclk_vio have a gate?
	GATE(0, "gate_aclk_rga", "div_aclk_rga", RK3288_CLKGATE_CON(15), 0, 0, GFLAGS),
	GATE(0, "gate_hclk_rga", "div_hclk_vio", RK3288_CLKGATE_CON(15), 1, 0, GFLAGS),
	GATE(0, "gate_aclk_iep", "gate_aclk_vio0", RK3288_CLKGATE_CON(15), 2, 0, GFLAGS),
	GATE(0, "gate_hclk_iep", "div_hclk_vio", RK3288_CLKGATE_CON(15), 3, 0, GFLAGS),
	//FIXME: where does this come from
	GATE(0, "gate_aclk_lcdc_iep", "dummy", RK3288_CLKGATE_CON(15), 4, 0, GFLAGS),
	GATE(0, "gate_aclk_lcdc0", "gate_aclk_vio0", RK3288_CLKGATE_CON(15), 5, 0, GFLAGS),
	GATE(0, "gate_hclk_lcdc0", "div_hclk_vio", RK3288_CLKGATE_CON(15), 6, 0, GFLAGS),
	GATE(0, "gate_aclk_lcdc1", "gate_aclk_vio1", RK3288_CLKGATE_CON(15), 7, 0, GFLAGS),
	GATE(0, "gate_hclk_lcdc1", "div_hclk_vio", RK3288_CLKGATE_CON(15), 8, 0, GFLAGS),
	GATE(0, "gate_hclk_vio_ahb", "div_hclk_vio", RK3288_CLKGATE_CON(15), 9, 0, GFLAGS),
	GATE(0, "gate_hclk_vio_niu", "div_hclk_vio", RK3288_CLKGATE_CON(15), 10, 0, GFLAGS),
	GATE(0, "gate_aclk_vio0_niu", "gate_aclk_vio0", RK3288_CLKGATE_CON(15), 11, 0, GFLAGS),
	GATE(0, "gate_aclk_vio1_niu", "gate_aclk_vio1", RK3288_CLKGATE_CON(15), 12, 0, GFLAGS),
	GATE(0, "gate_aclk_rga_niu", "gate_aclk_rga", RK3288_CLKGATE_CON(15), 13, 0, GFLAGS),
	GATE(0, "gate_aclk_vip", "gate_aclk_vio0", RK3288_CLKGATE_CON(15), 14, 0, GFLAGS),
	GATE(0, "gate_hclk_vip", "div_hclk_vio", RK3288_CLKGATE_CON(15), 15, 0, GFLAGS),

	/* CLKGATE_CON_16 */
	//FIXME: where does this come from (external clock in upstream source)
	GATE(0, "gate_pclkin_cif", "pclkin_cif", RK3288_CLKGATE_CON(16), 0, 0, GFLAGS),
	GATE(0, "gate_hclk_isp", "div_hclk_vio", RK3288_CLKGATE_CON(16), 1, 0, GFLAGS),
	GATE(0, "gate_aclk_isp", "gate_aclk_vio1", RK3288_CLKGATE_CON(16), 2, 0, GFLAGS),
	//FIXME: where does this come from (external clock in upstream source)
	GATE(0, "gate_pclkin_isp", "pclkin_isp", RK3288_CLKGATE_CON(16), 3, 0, GFLAGS),
	//FIXME are these really pclks when all come from hclk_vio?
	//FIXME especially hclk_vio2_h2p and pclk_vio2_h2p seem dubious
	GATE(0, "gate_pclk_mipi_dsi0", "div_hclk_vio", RK3288_CLKGATE_CON(16), 4, 0, GFLAGS),
	GATE(0, "gate_pclk_mipi_dsi1", "div_hclk_vio", RK3288_CLKGATE_CON(16), 5, 0, GFLAGS),
	GATE(0, "gate_pclk_mipi_csi", "div_hclk_vio", RK3288_CLKGATE_CON(16), 6, 0, GFLAGS),
	GATE(0, "gate_pclk_lvds_phy", "div_hclk_vio", RK3288_CLKGATE_CON(16), 7, 0, GFLAGS),
	GATE(0, "gate_pclk_edp_ctrl", "div_hclk_vio", RK3288_CLKGATE_CON(16), 8, 0, GFLAGS),
	GATE(0, "gate_pclk_hdmi_ctrl", "div_hclk_vio", RK3288_CLKGATE_CON(16), 9, 0, GFLAGS),
	GATE(0, "gate_hclk_vio2_h2p", "div_hclk_vio", RK3288_CLKGATE_CON(16), 10, 0, GFLAGS),
	GATE(0, "gate_pclk_vio2_h2p", "div_hclk_vio", RK3288_CLKGATE_CON(16), 11, 0, GFLAGS),

	/* CLKGATE_CON_17 */
	GATE(0, "gate_pclk_pmu", "gate_pclk_pd_pmu", RK3288_CLKGATE_CON(17), 0, 0, GFLAGS),
	GATE(0, "gate_pclk_intmem1", "gate_pclk_pd_pmu", RK3288_CLKGATE_CON(17), 1, 0, GFLAGS),
	GATE(0, "gate_pclk_pmu_niu", "gate_pclk_pd_pmu", RK3288_CLKGATE_CON(17), 2, 0, GFLAGS),
	GATE(0, "gate_pclk_sgrf", "gate_pclk_pd_pmu", RK3288_CLKGATE_CON(17), 3, 0, GFLAGS),
	GATE(0, "gate_pclk_gpio0", "gate_pclk_pd_pmu", RK3288_CLKGATE_CON(17), 4, 0, GFLAGS),
	/* FIXME: is the rest of the register really empty? */

	/* CLKGATE_CON_18 */
	/* FIXME: why is this labeled _aclk_ when it's supposed from the special gpu clock? */
	GATE(0, "gate_aclk_gpu", "gate_sclk_gpu", RK3288_CLKGATE_CON(18), 0, 0, GFLAGS),
	/* FIXME: is the rest of the register really empty? */

};


struct rockchip_clk_init_table rk3288_clk_init_tbl[] __initdata = {
};

static void __init rk3288_clock_apply_init_table(void)
{
}

static void __init rk3288_clk_init(struct device_node *np)
{
	void __iomem *reg_base, *reg_grf_soc_status;
	struct clk *clk;

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

	/* xin12m is created by an cru-internal divider */
	clk = clk_register_fixed_factor(NULL, "xin12m", "xin24m", 0, 1, 2);
	if (IS_ERR(clk))
		pr_warn("%s: could not register clock xin12m: %ld\n",
			__func__, PTR_ERR(clk));


	clk = clk_register_fixed_factor(NULL, "usb480m", "xin24m", 0, 20, 1);
	if (IS_ERR(clk))
		pr_warn("%s: could not register clock usb480m: %ld\n",
			__func__, PTR_ERR(clk));

	rockchip_clk_register_plls(rk3288_pll_clks,
				   ARRAY_SIZE(rk3288_pll_clks),
				   reg_grf_soc_status);
	rockchip_clk_register_branches(rk3288_clk_branches,
				  ARRAY_SIZE(rk3288_clk_branches));

//	rockchip_clk_register_armclk(SCLK_ARMCLK, "armclk", mux_armclk_p,
//				     ARRAY_SIZE(mux_armclk_p), reg_base, np);

	rockchip_register_softrst(np, 9, reg_base + RK3288_SOFTRST_CON(0),
				  ROCKCHIP_SOFTRST_HIWORD_MASK);

	rockchip_clk_apply_init_table = rk3288_clock_apply_init_table;
}
CLK_OF_DECLARE(rk3288_cru, "rockchip,rk3288-cru", rk3288_clk_init);
