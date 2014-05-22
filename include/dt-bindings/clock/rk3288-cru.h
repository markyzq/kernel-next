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

/* core clocks from 1 */


/* sclk gates (special clocks) from 64 */
#define SCLK_GPU		64
#define SCLK_SPI0		65
#define SCLK_SPI1		66
#define SCLK_SPI2		67
#define SCLK_SDMMC		68
#define SCLK_SDIO0		69
#define SCLK_SDIO1		70
#define SCLK_EMMC		71
#define SCLK_TSADC		72
#define SCLK_SARADC		73
#define SCLK_PS2C		74
#define SCLK_NANDC0		75
#define SCLK_NANDC1		76
#define SCLK_UART0		77
#define SCLK_UART1		78
#define SCLK_UART2		79
#define SCLK_UART3		80
#define SCLK_UART4		81

/* aclk gates from 192*/
#define ACLK_GPU		192
#define ACLK_DMAC1		193
#define ACLK_DMAC2		194
#define ACLK_MMU		195
#define ACLK_GMAC		196

/* pclk gates from 320*/
#define PCLK_GPIO0		320
#define PCLK_GPIO1		321
#define PCLK_GPIO2		322
#define PCLK_GPIO3		323
#define PCLK_GPIO4		324
#define PCLK_GPIO5		325
#define PCLK_GPIO6		326
#define PCLK_GPIO7		327
#define PCLK_GPIO8		328
#define PCLK_GRF		329
#define PCLK_PMU		330
#define PCLK_I2C0		331
#define PCLK_I2C1		332
#define PCLK_I2C2		333
#define PCLK_I2C3		334
#define PCLK_I2C4		335
#define PCLK_I2C5		336
#define PCLK_SPI0		337
#define PCLK_SPI1		338
#define PCLK_SPI2		339
#define PCLK_PS2C		340
#define PCLK_UART0		330
#define PCLK_UART1		331
#define PCLK_UART2		332
#define PCLK_UART3		333
#define PCLK_UART4		334
#define PCLK_TSADC		335
#define PCLK_SARADC		336
#define PCLK_SIM		337
#define PCLK_GMAC		338

/* hclk gates from 448 */
#define HCLK_GPS		448
#define HCLK_OTG0		449
#define HCLK_HOST0		450
#define HCLK_HOST1		451
#define HCLK_HSIC		452
#define HCLK_NANDC0		453
#define HCLK_NANDC1		454
#define HCLK_TSP		455
#define HCLK_SDMMC		456
#define HCLK_SDIO0		457
#define HCLK_SDIO1		458
#define HCLK_EMMC		459
#define HCLK_HSADC		460

#define CLK_NR_CLKS		576
