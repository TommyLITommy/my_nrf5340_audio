#ifndef __DEBUG_GPIO_H__
#define __DEBUG_GPIO_H__

#include <stdint.h>

typedef enum{
	DEBUG_GPIO_ID_P1_12,
	DEBUG_GPIO_ID_P1_13,
    DEBUG_GPIO_ID_P1_14,
} DEBUG_GPIO_ID_t ;

extern int debug_gpio_toggle(DEBUG_GPIO_ID_t gpio_id);
extern int debug_gpio_set_level(DEBUG_GPIO_ID_t gpio_id, uint8_t level);
extern int debug_gpio_init(void);
#endif