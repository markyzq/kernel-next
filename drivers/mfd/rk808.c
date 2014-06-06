/*
 * Regulator driver for rk808 PMIC chip for rk31xx
 *
 * Based on rk808.c that is work by zhangqing<zhangqing@rock-chips.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/bug.h>
#include <linux/err.h>
#include <linux/i2c.h>
#include <linux/kernel.h>
#include <linux/regulator/driver.h>
#include <linux/mfd/rk808.h>
#include <linux/mfd/core.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/of_irq.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/regulator/of_regulator.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regmap.h>





#define RK808_BUCK1_CONFIG_REG		0x2e
#define RK808_BUCK1_ON_VSEL_REG		0x2f
#define RK808_BUCK1_SLP_VSEL_REG	0x30
#define RK808_BUCK1_DVS_VSEL_REG	0x31
#define RK808_BUCK2_CONFIG_REG		0x32
#define RK808_BUCK2_ON_VSEL_REG		0x33
#define RK808_BUCK2_SLP_VSEL_REG	0x34
#define RK808_BUCK2_DVS_VSEL_REG	0x35
#define RK808_BUCK3_CONFIG_REG		0x36
#define RK808_BUCK4_CONFIG_REG		0x37
#define RK808_BUCK4_ON_VSEL_REG		0x38
#define RK808_BUCK4_SLP_VSEL_REG	0x39
#define RK808_BOOST_CONFIG_REG		0x3a
#define RK808_LDO1_ON_VSEL_REG		0x3b
#define RK808_LDO1_SLP_VSEL_REG		0x3c
#define RK808_LDO2_ON_VSEL_REG		0x3d
#define RK808_LDO2_SLP_VSEL_REG		0x3e
#define RK808_LDO3_ON_VSEL_REG		0x3f
#define RK808_LDO3_SLP_VSEL_REG		0x40
#define RK808_LDO4_ON_VSEL_REG		0x41
#define RK808_LDO4_SLP_VSEL_REG		0x42
#define RK808_LDO5_ON_VSEL_REG		0x43
#define RK808_LDO5_SLP_VSEL_REG		0x44
#define RK808_LDO6_ON_VSEL_REG		0x45
#define RK808_LDO6_SLP_VSEL_REG		0x46
#define RK808_LDO7_ON_VSEL_REG		0x47
#define RK808_LDO7_SLP_VSEL_REG		0x48
#define RK808_LDO8_ON_VSEL_REG		0x49
#define RK808_LDO8_SLP_VSEL_REG		0x4a


struct rk808 *g_rk808;

static struct mfd_cell rk808s[] = {
	{
		.name = "rk808-rtc",
	},
};

#define RK808_BUCK_VSEL_MASK	0x3f
#define RK808_BUCK4_VSEL_MASK	0xf
#define RK808_LDO_VSEL_MASK	0x1f

const static int buck_set_vol_base_addr[] = {
	RK808_BUCK1_ON_REG,
	RK808_BUCK2_ON_REG,
	RK808_BUCK3_CONFIG_REG,
	RK808_BUCK4_ON_REG,
};
const static int buck_contr_base_addr[] = {
	RK808_BUCK1_CONFIG_REG,
 	RK808_BUCK2_CONFIG_REG,
 	RK808_BUCK3_CONFIG_REG,
 	RK808_BUCK4_CONFIG_REG,
};
#define rk808_BUCK_SET_VOL_REG(x) (buck_set_vol_base_addr[x])
#define rk808_BUCK_CONTR_REG(x) (buck_contr_base_addr[x])


const static int ldo_set_vol_base_addr[] = {
	RK808_LDO1_ON_VSEL_REG,
	RK808_LDO2_ON_VSEL_REG,
	RK808_LDO3_ON_VSEL_REG,
	RK808_LDO4_ON_VSEL_REG, 
	RK808_LDO5_ON_VSEL_REG, 
	RK808_LDO6_ON_VSEL_REG, 
	RK808_LDO7_ON_VSEL_REG, 
	RK808_LDO8_ON_VSEL_REG, 
};

#define rk808_LDO_SET_VOL_REG(x) (ldo_set_vol_base_addr[x])

static const struct regmap_config rk808_regmap_config = {
	.reg_bits = 8,
	.val_bits = 8,
	.max_register = RK808_IO_POL_REG,
};

static const struct regulator_linear_range rk808_buck_voltage_ranges[] = {
	REGULATOR_LINEAR_RANGE(700000, 0, 63, 12500),
};

static const struct regulator_linear_range rk808_buck4_voltage_ranges[] = {
	REGULATOR_LINEAR_RANGE(1800000, 0, 15, 100000),
};

static const struct regulator_linear_range rk808_ldo_voltage_ranges[] = {
	REGULATOR_LINEAR_RANGE(1800000, 0, 16, 100000),
};

static const struct regulator_linear_range rk808_ldo3_voltage_ranges[] = {
	REGULATOR_LINEAR_RANGE(800000, 0, 13, 100000),
	REGULATOR_LINEAR_RANGE(2500000, 15, 15, 0),
};

static const struct regulator_linear_range rk808_ldo6_voltage_ranges[] = {
	REGULATOR_LINEAR_RANGE(800000, 0, 17, 100000),
};

static struct regulator_ops rk808_reg_ops = {
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
};

static struct regulator_ops rk808_switch_ops = {
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
};

static const struct regulator_desc rk808_reg[] = {
	{
		.name = "DCDC_REG1",
		.id = RK808_ID_DCDC1,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 64,
		.linear_ranges = rk808_buck_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_buck_voltage_ranges),
		.vsel_reg = RK808_BUCK1_ON_VSEL_REG,
		.vsel_mask = RK808_BUCK_VSEL_MASK,
		.enable_reg = RK808_DCDC_EN_REG,
		.enable_mask = BIT(0),
		.owner = THIS_MODULE,
	}, {
		.name = "DCDC_REG2",
		.id = RK808_ID_DCDC2,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 64,
		.linear_ranges = rk808_buck_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_buck_voltage_ranges),
		.vsel_reg = RK808_BUCK2_ON_VSEL_REG,
		.vsel_mask = RK808_BUCK_VSEL_MASK,
		.enable_reg = RK808_DCDC_EN_REG,
		.enable_mask = BIT(1),
		.owner = THIS_MODULE,
	}, {
		.name = "DCDC_REG3",
		.id = RK808_ID_DCDC3,
		.ops = &rk808_switch_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 1,
		.enable_reg = RK808_DCDC_EN_REG,
		.enable_mask = BIT(2),
		.owner = THIS_MODULE,
	}, {
		.name = "DCDC_REG4",
		.id = RK808_ID_DCDC4,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 17,
		.linear_ranges = rk808_buck4_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_buck4_voltage_ranges),
		.vsel_reg = RK808_BUCK4_ON_VSEL_REG,
		.vsel_mask = RK808_BUCK4_VSEL_MASK,
		.enable_reg = RK808_DCDC_EN_REG,
		.enable_mask = BIT(3),
		.owner = THIS_MODULE,
	}, {
		.name = "SWITCH_REG1",
		.id = RK808_ID_SWITCH1,
		.ops = &rk808_switch_ops,
		.type = REGULATOR_VOLTAGE,
		.enable_reg = RK808_DCDC_EN_REG,
		.enable_mask = BIT(5),
		.owner = THIS_MODULE,
	}, {
		.name = "SWITCH_REG2",
		.id = RK808_ID_SWITCH2,
		.ops = &rk808_switch_ops,
		.type = REGULATOR_VOLTAGE,
		.enable_reg = RK808_DCDC_EN_REG,
		.enable_mask = BIT(6),
		.owner = THIS_MODULE,
	}, {
		.name = "LDO_REG1",
		.id = RK808_ID_LDO1,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 17,
		.linear_ranges = rk808_ldo_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_ldo_voltage_ranges),
		.vsel_reg = RK808_LDO1_ON_VSEL_REG,
		.vsel_mask = RK808_LDO_VSEL_MASK,
		.enable_reg = RK808_LDO_EN_REG,
		.enable_mask = BIT(0),
		.owner = THIS_MODULE,
	}, {
		.name = "LDO_REG2",
		.id = RK808_ID_LDO2,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 17,
		.linear_ranges = rk808_ldo_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_ldo_voltage_ranges),
		.vsel_reg = RK808_LDO2_ON_VSEL_REG,
		.vsel_mask = RK808_LDO_VSEL_MASK,
		.enable_reg = RK808_LDO_EN_REG,
		.enable_mask = BIT(1),
		.owner = THIS_MODULE,
	}, {
		.name = "LDO_REG3",
		.id = RK808_ID_LDO3,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 16,
		.linear_ranges = rk808_ldo3_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_ldo3_voltage_ranges),
		.vsel_reg = RK808_LDO3_ON_VSEL_REG,
		.vsel_mask = RK808_BUCK4_VSEL_MASK,
		.enable_reg = RK808_LDO_EN_REG,
		.enable_mask = BIT(2),
		.owner = THIS_MODULE,
	}, {
		.name = "LDO_REG4",
		.id = RK808_ID_LDO4,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 17,
		.linear_ranges = rk808_ldo_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_ldo_voltage_ranges),
		.vsel_reg = RK808_LDO4_ON_VSEL_REG,
		.vsel_mask = RK808_LDO_VSEL_MASK,
		.enable_reg = RK808_LDO_EN_REG,
		.enable_mask = BIT(3),
		.owner = THIS_MODULE,
	}, {
		.name = "LDO_REG5",
		.id = RK808_ID_LDO5,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 17,
		.linear_ranges = rk808_ldo_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_ldo_voltage_ranges),
		.vsel_reg = RK808_LDO5_ON_VSEL_REG,
		.vsel_mask = RK808_LDO_VSEL_MASK,
		.enable_reg = RK808_LDO_EN_REG,
		.enable_mask = BIT(4),
		.owner = THIS_MODULE,
	}, {
		.name = "LDO_REG6",
		.id = RK808_ID_LDO6,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 18,
		.linear_ranges = rk808_ldo6_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_ldo6_voltage_ranges),
		.vsel_reg = RK808_LDO6_ON_VSEL_REG,
		.vsel_mask = RK808_LDO_VSEL_MASK,
		.enable_reg = RK808_LDO_EN_REG,
		.enable_mask = BIT(5),
		.owner = THIS_MODULE,
	}, {
		.name = "LDO_REG7",
		.id = RK808_ID_LDO7,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 18,
		.linear_ranges = rk808_ldo6_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_ldo6_voltage_ranges),
		.vsel_reg = RK808_LDO7_ON_VSEL_REG,
		.vsel_mask = RK808_LDO_VSEL_MASK,
		.enable_reg = RK808_LDO_EN_REG,
		.enable_mask = BIT(6),
		.owner = THIS_MODULE,
	}, {
		.name = "LDO_REG8",
		.id = RK808_ID_LDO8,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 17,
		.linear_ranges = rk808_ldo_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_ldo_voltage_ranges),
		.vsel_reg = RK808_LDO8_ON_VSEL_REG,
		.vsel_mask = RK808_LDO_VSEL_MASK,
		.enable_reg = RK808_LDO_EN_REG,
		.enable_mask = BIT(7),
		.owner = THIS_MODULE,
	},
};

static irqreturn_t rk808_vbat_lo_irq(int irq, void *data)
{
	int ret;
        printk("rk808 vbat low %s:irq=%d\n",__func__,irq);
	ret = regmap_update_bits(g_rk808->regmap,0x4c,(0x1 << 1),(0x1 <<1));
        return IRQ_HANDLED;
}

#ifdef CONFIG_OF
static struct of_device_id rk808_of_match[] = {
	{ .compatible = "rockchip,rk808"},
	{ },
};
MODULE_DEVICE_TABLE(of, rk808_of_match);


static struct of_regulator_match rk808_reg_matches[] = {
	[RK808_ID_DCDC1]	= { .name = "DCDC_REG1" },
	[RK808_ID_DCDC2]	= { .name = "DCDC_REG2" },
	[RK808_ID_DCDC3]	= { .name = "DCDC_REG3" },
	[RK808_ID_DCDC4]	= { .name = "DCDC_REG4" },
	[RK808_ID_SWITCH1]	= { .name = "SWITCH_REG1" },
	[RK808_ID_SWITCH2]	= { .name = "SWITCH_REG2" },
	[RK808_ID_LDO1]		= { .name = "LDO_REG1" },
	[RK808_ID_LDO2]		= { .name = "LDO_REG2" },
	[RK808_ID_LDO3]		= { .name = "LDO_REG3" },
	[RK808_ID_LDO4]		= { .name = "LDO_REG4" },
	[RK808_ID_LDO5]		= { .name = "LDO_REG5" },
	[RK808_ID_LDO6]		= { .name = "LDO_REG6" },
	[RK808_ID_LDO7]		= { .name = "LDO_REG7" },
	[RK808_ID_LDO8]		= { .name = "LDO_REG8" },
};

static struct rk808_board *rk808_parse_dt(struct rk808 *rk808)
{
	struct rk808_board *pdata;
	struct device_node *np, *reg_np;
	int i, count;

	rk808_pmic_np = rk808->dev->of_node);
	if (!rk808_pmic_np) {
		printk("could not find pmic sub-node\n");
		return NULL;
	}

	regs = of_find_node_by_name(rk808_pmic_np, "regulators");
	if (!regs)
		return NULL;

	count = of_regulator_match(rk808->dev, regs, rk808_reg_matches,
				   rk808_NUM_REGULATORS);
	of_node_put(regs);
	if ((count < 0) || (count > rk808_NUM_REGULATORS))
		return NULL;

	pdata = devm_kzalloc(rk808->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;

	for (i = 0; i < count; i++) {
		if (!rk808_reg_matches[i].init_data || !rk808_reg_matches[i].of_node)
			continue;

		pdata->rk808_init_data[i] = rk808_reg_matches[i].init_data;
		pdata->of_node[i] = rk808_reg_matches[i].of_node;
	}
	pdata->irq = rk808->chip_irq;
	pdata->irq_base = -1;
	
	pdata->pmic_sleep_gpio = of_get_named_gpio(rk808_pmic_np,"gpios",0);
			if (!gpio_is_valid(pdata->pmic_sleep_gpio)) {
				printk("invalid gpio: %d\n",  pdata->pmic_sleep_gpio);
		}
	pdata->pmic_sleep = true;
	
	pdata->pm_off = of_property_read_bool(rk808_pmic_np,"rk808,system-power-controller");
		
	return pdata;
}

#else
static struct rk808_board *rk808_parse_dt(struct i2c_client *i2c)
{
	return NULL;
}
#endif


static int rk808_device_shutdown(void)
{
	int ret;
	int err = -1;
	struct rk808 *rk808 = g_rk808;
	
	printk("%s\n",__func__);

	ret = rk808_reg_read(rk808,RK808_DEVCTRL_REG);
	ret = regmap_update_bits(rk808->regmap, RK808_DEVCTRL_REG,(0x1<<3),(0x1<<3));
	if (ret < 0) {
		printk("rk808 power off error!\n");
		return err;
	}
	return 0;	
}
EXPORT_SYMBOL_GPL(rk808_device_shutdown);

static int rk808_pre_init(struct rk808 *rk808)
{
	int ret,val;
	 printk("%s,line=%d\n", __func__,__LINE__);
	 /***********set ILIM ************/
	val = rk808_reg_read(rk808,RK808_BUCK3_CONFIG_REG);
	val &= (~(0x7 <<0));
	val |= (0x2 <<0);
	ret = rk808_reg_write(rk808,RK808_BUCK3_CONFIG_REG,val);
	if (ret < 0) {
                printk(KERN_ERR "Unable to write RK808_BUCK3_CONFIG_REG reg\n");
                return ret;
        }

	val = rk808_reg_read(rk808,RK808_BUCK4_CONFIG_REG);
	val &= (~(0x7 <<0));
	val |= (0x3 <<0);
	ret = rk808_reg_write(rk808,RK808_BUCK4_CONFIG_REG,val);
	if (ret < 0) {
                printk(KERN_ERR "Unable to write RK808_BUCK4_CONFIG_REG reg\n");
                return ret;
        }
	
	val = rk808_reg_read(rk808,RK808_BOOST_CONFIG_REG);
	val &= (~(0x7 <<0));
	val |= (0x1 <<0);
	ret = rk808_reg_write(rk808,RK808_BOOST_CONFIG_REG,val);
	if (ret < 0) {
                printk(KERN_ERR "Unable to write RK808_BOOST_CONFIG_REG reg\n");
                return ret;
        }
	/*****************************************/
	/***********set buck OTP function************/
	ret = rk808_reg_write(rk808,0x6f,0x5a);
	if (ret < 0) {
                printk(KERN_ERR "Unable to write 0x6f reg\n");
                return ret;
        }
	
	ret = rk808_reg_write(rk808,0x91,0x80);
	if (ret < 0) {
                printk(KERN_ERR "Unable to write 0x91 reg\n");
                return ret;
        }

        ret = rk808_reg_write(rk808,0x92,0x55);
	 if (ret <0) {
                printk(KERN_ERR "Unable to write 0x92 reg\n");
                return ret;
        }
	/*****************************************/
	/***********set buck 12.5mv/us ************/
	val = rk808_reg_read(rk808,RK808_BUCK1_CONFIG_REG);
	val &= (~(0x3 <<3));
	val |= (0x3 <<0);
	ret = rk808_reg_write(rk808,RK808_BUCK1_CONFIG_REG,val);
	if (ret < 0) {
                printk(KERN_ERR "Unable to write RK808_BUCK1_CONFIG_REG reg\n");
                return ret;
        }

	val = rk808_reg_read(rk808,RK808_BUCK2_CONFIG_REG);
        val &= (~(0x3 <<3));
	val |= (0x3 <<0);
        ret = rk808_reg_write(rk808,RK808_BUCK2_CONFIG_REG,val);
	 if (ret <0) {
                printk(KERN_ERR "Unable to write RK808_BUCK2_CONFIG_REG reg\n");
                return ret;
        }
	/*****************************************/

	/*******enable switch and boost***********/
	val = rk808_reg_read(rk808,RK808_DCDC_EN_REG);
        val |= (0x3 << 5);    //enable switch1/2
	val |= (0x1 << 4);    //enable boost
        ret = rk808_reg_write(rk808,RK808_DCDC_EN_REG,val);
         if (ret <0) {
                printk(KERN_ERR "Unable to write RK808_DCDC_EN_REG reg\n");
                return ret;
	}
	/****************************************/
	
	/****************set vbat low **********/
	val = rk808_reg_read(rk808,RK808_VB_MON_REG);
       val &=(~(VBAT_LOW_VOL_MASK | VBAT_LOW_ACT_MASK));
       val |= (RK808_VBAT_LOW_3V5 | EN_VBAT_LOW_IRQ);
       ret = rk808_reg_write(rk808,RK808_VB_MON_REG,val);
         if (ret <0) {
                printk(KERN_ERR "Unable to write RK818_VB_MON_REG reg\n");
                return ret;
        }
	/**************************************/
	
	/**********mask int****************/
	 val = rk808_reg_read(rk808,RK808_INT_STS_MSK_REG1);
         val |= (0x1<<0); //mask vout_lo_int    
        ret = rk808_reg_write(rk808,RK808_INT_STS_MSK_REG1,val);
         if (ret <0) {
                printk(KERN_ERR "Unable to write RK808_INT_STS_MSK_REG1 reg\n");
                return ret;
        }
	/**********************************/
	/**********enable clkout2****************/
        ret = rk808_reg_write(rk808,RK808_CLK32OUT_REG,0x01);
         if (ret <0) {
                printk(KERN_ERR "Unable to write RK808_CLK32OUT_REG reg\n");
                return ret;
        }
	/**********************************/
	return 0;
}

static int rk808_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct rk808 *rk808;	
	struct rk808_board *pdev;
	const struct of_device_id *match;
	struct regulator_config config = { };
	struct regulator_dev *rk808_rdev;
	struct regulator_init_data *reg_data;
	const char *rail_name = NULL;
	int ret,vlow_irq,i=0;
	
	printk("%s,line=%d\n", __func__,__LINE__);

	if (client->dev.of_node) {
		match = of_match_device(rk808_of_match, &client->dev);
		if (!match) {
			dev_err(&client->dev,"Failed to find matching dt id\n");
			return -EINVAL;
		}
	}

	rk808 = devm_kzalloc(&client->dev,sizeof(struct rk808), GFP_KERNEL);
	if (rk808 == NULL) {
		ret = -ENOMEM;		
		goto err;
	}
	rk808->i2c = client;
	rk808->dev = &client->dev;
	i2c_set_clientdata(client, rk808);
//	rk808->read = rk808_i2c_read;
//	rk808->write = rk808_i2c_write;

	rk808->regmap = devm_regmap_init_i2c(client, &rk808_regmap_config);
	if (IS_ERR(rk808->regmap)) {
		printk("regmap initialization failed\n");
		return ret;
	}
	
	mutex_init(&rk808->io_lock);	

	ret = rk808_reg_read(rk808, 0x2f);
	if ((ret < 0) || (ret == 0xff)){
		printk("The device is not rk808 %d\n",ret);
		goto err;
	}

	ret = rk808_pre_init(rk808);
	if (ret < 0){
		printk("The rk808_pre_init failed %d\n",ret);
		goto err;
	}

	if (rk808->dev->of_node)
		pdev = rk808_parse_dt(rk808);
	
	/******************************set sleep vol & dcdc mode******************/
	#ifdef CONFIG_OF
	rk808->pmic_sleep_gpio = pdev->pmic_sleep_gpio;
	if (rk808->pmic_sleep_gpio) {
			ret = gpio_request(rk808->pmic_sleep_gpio, "rk808_pmic_sleep");
			if (ret < 0) {
				dev_err(rk808->dev,"Failed to request gpio %d with ret:""%d\n",	rk808->pmic_sleep_gpio, ret);
				return IRQ_NONE;
			}
			gpio_direction_output(rk808->pmic_sleep_gpio,0);
			ret = gpio_get_value(rk808->pmic_sleep_gpio);
			gpio_free(rk808->pmic_sleep_gpio);
			pr_info("%s: rk808_pmic_sleep=%x\n", __func__, ret);
	}	
	#endif
	/**********************************************************/
	
	if (pdev) {
		rk808->num_regulators = rk808_NUM_REGULATORS;
		rk808->rdev = kcalloc(rk808_NUM_REGULATORS,sizeof(struct regulator_dev *), GFP_KERNEL);
		if (!rk808->rdev) {
			return -ENOMEM;
		}
		/* Instantiate the regulators */
		for (i = 0; i < rk808_NUM_REGULATORS; i++) {
		reg_data = pdev->rk808_init_data[i];
		if (!reg_data)
			continue;
		config.dev = rk808->dev;
		config.driver_data = rk808;
		config.regmap = rk808->regmap;
		if (rk808->dev->of_node)
			config.of_node = pdev->of_node[i];
		if (reg_data && reg_data->constraints.name)
				rail_name = reg_data->constraints.name;
			else
				rail_name = regulators[i].name;
			reg_data->supply_regulator = rail_name;
	
		config.init_data =reg_data;

		rk808_rdev = regulator_register(&regulators[i],&config);
		if (IS_ERR(rk808_rdev)) {
			printk("failed to register %d regulator\n",i);
		goto err;
		}
		rk808->rdev[i] = rk808_rdev;
		}
	}

	ret = rk808_irq_init(rk808, client->irq, pdev);
	if (ret < 0)
		goto err;

	ret = mfd_add_devices(rk808->dev, -1,
			      rk808s, ARRAY_SIZE(rk808s),
			      NULL, 0,NULL);
	
	g_rk808 = rk808;
	if (pdev->pm_off && !pm_power_off) {
		pm_power_off = rk808_device_shutdown;
	}

	return 0;

err:
	mfd_remove_devices(rk808->dev);
	return ret;	

}

static int rk808_remove(struct i2c_client *i2c)
{
	struct rk808 *rk808 = i2c_get_clientdata(i2c);
	int i;

	for (i = 0; i < rk808->num_regulators; i++)
		if (rk808->rdev[i])
			regulator_unregister(rk808->rdev[i]);
	kfree(rk808->rdev);
	i2c_set_clientdata(i2c, NULL);
	kfree(rk808);

	return 0;
}

static const struct i2c_device_id rk808_ids[] = {
       { "rk808", 0 },
       { }
};

MODULE_DEVICE_TABLE(i2c, rk808_i2c_id);

static struct i2c_driver rk808_i2c_driver = {
	.driver = {
		.name = "rk808",
		.owner = THIS_MODULE,
		.of_match_table =of_match_ptr(rk808_of_match),
	},
	.probe    = rk808_probe,
	.remove   = rk808_remove,
	.id_table = rk808__ids,
};

module_i2c_driver(rk808_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhangqing <zhangqing@rock-chips.com>");
MODULE_DESCRIPTION("rk808 PMIC driver");

