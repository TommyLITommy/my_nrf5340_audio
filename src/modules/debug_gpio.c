/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>
#include "debug_gpio.h"
#include "macros_common.h"

// /* 1000 msec = 1 sec */
// #define SLEEP_TIME_MS   1000

// /* The devicetree node identifier for the "led0" alias. */
// #define DBG01_NODE DT_ALIAS(dbg01)

// /*
//  * A build error on this line means your board is unsupported.
//  * See the sample documentation for information on how to fix this.
//  */
// static const struct gpio_dt_spec dbg01 = GPIO_DT_SPEC_GET(DBG01_NODE, gpios);

// int debug_gpio_init(void)
// {
// 	int ret;

//     printk("debug_gpio_init\n");

// 	ret = gpio_is_ready_dt(&dbg01);
//     if (!ret) {
// 		return -1;
// 	}

// 	ret = gpio_pin_configure_dt(&dbg01, GPIO_OUTPUT_ACTIVE);
// 	if (ret < 0) {
// 		return -2;
// 	}

// 	return 0;
// }


#define DT_LABEL_AND_COMMA1(node_id)	    DT_PROP(node_id, label),
#define GPIO_DT_SPEC_GET_AND_COMMA1(node_id) GPIO_DT_SPEC_GET(node_id, gpios),

static const char *const debug_gpio_labels[] = { DT_FOREACH_CHILD(DT_PATH(gpio_custom), DT_LABEL_AND_COMMA1)};
static const struct gpio_dt_spec debug_gpios[] = {
	DT_FOREACH_CHILD(DT_PATH(gpio_custom), GPIO_DT_SPEC_GET_AND_COMMA1)
};

int debug_gpio_toggle(DEBUG_GPIO_ID_t gpio_id) 
{
	gpio_pin_toggle_dt(&debug_gpios[gpio_id]);
	return 0;
}

int debug_gpio_set_level(DEBUG_GPIO_ID_t gpio_id, uint8_t level)
{
	
	__ASSERT(level <= 1, "level is bigger thant 1!");

	gpio_pin_set_dt(&debug_gpios[gpio_id], level);
	return 0;
}

int debug_gpio_init(void)
{
	for (int i = 0; i < sizeof(debug_gpio_labels) / sizeof(char *const); i++) {
		printk("gpio[%d]: label:%s\r\n", i, debug_gpio_labels[i]);
		gpio_pin_configure_dt(&debug_gpios[i], GPIO_OUTPUT_ACTIVE);
	}
	return 0;
} 