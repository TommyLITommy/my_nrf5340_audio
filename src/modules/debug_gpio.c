/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define DBG01_NODE DT_ALIAS(dbg01)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec dbg01 = GPIO_DT_SPEC_GET(DBG01_NODE, gpios);

int debug_gpio_init(void)
{
	int ret;

    printk("debug_gpio_init\n");

	ret = gpio_is_ready_dt(&dbg01);
    if (!ret) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&dbg01, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return -2;
	}

	return 0;
}
