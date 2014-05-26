/**
 * dwmac-rockchip.c - Allwinner rockchip DWMAC specific glue layer
 *
 * Copyright (C) 2013 Chen-Yu Tsai
 *
 * Chen-Yu Tsai  <wens@csie.org>
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

#include <linux/stmmac.h>
#include <linux/clk.h>
#include <linux/phy.h>
#include <linux/of_net.h>
#include <linux/regulator/consumer.h>
#include <linux/mfd/syscon.h>

struct rockchip_priv_data {
	struct regmap *grf;
	int interface;

//	int clk_enabled;
//	struct clk *tx_clk;
//	struct regulator *regulator;
};

static void *rk3288_gmac_setup(struct platform_device *pdev)
{
	struct rockchip_priv_data *gmac;
	struct device *dev = &pdev->dev;

	gmac = devm_kzalloc(dev, sizeof(*gmac), GFP_KERNEL);
	if (!gmac)
		return ERR_PTR(-ENOMEM);

	gmac->interface = of_get_phy_mode(dev->of_node);

	gmac->grf = syscon_regmap_lookup_by_phandle(dev->of_node, "rockchip,grf");
	if (IS_ERR(gmac->grf)) {
		dev_err(dev, "could not get grf syscon\n");
		return gmac->grf;
	}

/*	gmac->tx_clk = devm_clk_get(dev, "allwinner_gmac_tx");
	if (IS_ERR(gmac->tx_clk)) {
		dev_err(dev, "could not get tx clock\n");
		return gmac->tx_clk;
	}
*/
	/* Optional regulator for PHY */
/*	gmac->regulator = devm_regulator_get_optional(dev, "phy");
	if (IS_ERR(gmac->regulator)) {
		if (PTR_ERR(gmac->regulator) == -EPROBE_DEFER)
			return ERR_PTR(-EPROBE_DEFER);
		dev_info(dev, "no regulator found\n");
		gmac->regulator = NULL;
	}
*/
	return gmac;
}

//#define SUN7I_GMAC_GMII_RGMII_RATE	125000000
//#define SUN7I_GMAC_MII_RATE		25000000

static int rk3288_gmac_init(struct platform_device *pdev, void *priv)
{
	struct rockchip_priv_data *gmac = priv;
	int ret;

/*	if (gmac->regulator) {
		ret = regulator_enable(gmac->regulator);
		if (ret)
			return ret;
	}*/

	/* Set GMAC interface port mode
	 */
	if (gmac->interface == PHY_INTERFACE_MODE_RGMII) {
//		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_GMII_RGMII_RATE);
//		clk_prepare_enable(gmac->tx_clk);
//		gmac->clk_enabled = 1;
	} else {
//		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_RMII_RATE);
//		clk_prepare(gmac->tx_clk);
	}

	return 0;
}

static void rk3288_gmac_exit(struct platform_device *pdev, void *priv)
{
	struct rockchip_priv_data *gmac = priv;

/*	if (gmac->clk_enabled) {
		clk_disable(gmac->tx_clk);
		gmac->clk_enabled = 0;
	}
	clk_unprepare(gmac->tx_clk);

	if (gmac->regulator)
		regulator_disable(gmac->regulator);*/
}

static void rk3288_fix_speed(void *priv, unsigned int speed)
{
	struct rockchip_priv_data *gmac = priv;

	/* only GMII mode requires us to reconfigure the clock lines */
/*	if (gmac->interface != PHY_INTERFACE_MODE_GMII)
		return;

	if (gmac->clk_enabled) {
		clk_disable(gmac->tx_clk);
		gmac->clk_enabled = 0;
	}
	clk_unprepare(gmac->tx_clk);

	if (speed == 1000) {
		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_GMII_RGMII_RATE);
		clk_prepare_enable(gmac->tx_clk);
		gmac->clk_enabled = 1;
	} else {
		clk_set_rate(gmac->tx_clk, SUN7I_GMAC_MII_RATE);
		clk_prepare(gmac->tx_clk);
	}*/
}

/* of_data specifying hardware features and callbacks.
 * hardware features were copied from Allwinner drivers. */
const struct stmmac_of_data rk3288_gmac_data = {
	.has_gmac = 1,
	.tx_coe = 1,
	.fix_mac_speed = rk3288_fix_speed,
	.setup = rk3288_gmac_setup,
	.init = rk3288_gmac_init,
	.exit = rk3288_gmac_exit,
};
