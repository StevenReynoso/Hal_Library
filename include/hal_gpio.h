/**
 * @file hal_gpio.h
 * @brief Public GPIO HAL API for STM32F4xx.
 *
 * This header provides high-level GPIO control functions for use with
 * STM32F411RE microcontrollers in bare-metal applications.
 *
 * All functions operate using the `gpio_config_t` structure and packed pin macros.
 *
 * Tip: In VS Code, you can hide all comments using `Ctrl + K`, then `Ctrl + 0`.
 */

#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>
#include "stm32f4_gpio.h"

/**
 * @brief Initialize a GPIO pin with a specified configuration.
 *
 * Applies mode, output type, speed, and pull-up/down settings using direct register writes.
 *
 * @param cfg GPIO configuration struct containing pin, mode, type, speed, and pull options.
 */
void gpio_init(gpio_config_t cfg);

/**
 * @brief Configure the alternate function for a GPIO pin.
 *
 * Sets the appropriate AFRL or AFRH bits based on pin number.
 *
 * @param pin Packed pin format (port << 8 | pin number).
 * @param af  Alternate function number (0–15).
 */
void gpio_set_af(uint16_t pin, uint8_t af);

/**
 * @brief Dynamically change the mode of a GPIO pin at runtime.
 *
 * Useful for switching a pin between input/output/alternate/analog modes.
 *
 * @param gpio_pin Packed pin format (port << 8 | pin number).
 * @param mode     New GPIO mode (see `gpio_mode_t`).
 */
void gpio_mode(uint16_t gpio_pin, gpio_mode_t mode);

/**
 * @brief Read the current logic level on a GPIO input pin.
 *
 * @param gpio_pin Packed pin format (port << 8 | pin number).
 * @return int Returns 1 if pin is HIGH, 0 if LOW.
 */
int gpio_read(uint16_t gpio_pin);

/**
 * @brief Write a logic level to a GPIO output pin.
 *
 * Uses the BSRR register for atomic set/reset.
 *
 * @param gpio_pin Packed pin format (port << 8 | pin number).
 * @param state    Logic level: 0 = LOW, non-zero = HIGH.
 */
void gpio_write(uint16_t gpio_pin, uint8_t state);

#endif // HAL_GPIO_H
