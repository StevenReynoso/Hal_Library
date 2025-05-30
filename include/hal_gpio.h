#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>
#include "stm32f4_gpio.h"


void gpio_init(gpio_config_t cfg);
void gpio_set_af(uint16_t pin, uint8_t af);
void gpio_mode(uint16_t gpio_pin, gpio_mode_t mode);
int gpio_read(uint16_t gpio_pin);
void gpio_write(uint16_t gpio_pin, uint8_t state);
#endif // HAL_GPIO_H