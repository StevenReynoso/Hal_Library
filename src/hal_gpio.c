/**
 * @file hal_gpio.c
 * @brief STM32F4 GPIO driver implementation for bare-metal HAL.
 * 
 * Provides GPIO control: initialization, alternate function setup,
 * mode switching, digital read/write—all via direct register access.
 * No CMSIS or STM32 HAL used.
 * 
 * Author: Steven Reynoso
 */

#include "hal_gpio.h"
#include <stdint.h>

/**
 * @brief Returns GPIO port base address from index.
 *
 * Used internally to get the memory-mapped struct for a given port.
 *
 * @param port_index Port index: 0 = A, 1 = B, ..., 7 = H.
 * @return GPIO_TypeDef* Pointer to the correct GPIO struct or 0 if out of range.
 */
static inline GPIO_TypeDef *get_gpio_port(uint8_t port_index) {
    static GPIO_TypeDef *const ports[] = {
        GPIOA, GPIOB, GPIOC, GPIOD,
        GPIOE, GPIOF, GPIOG, GPIOH
    };
    if (port_index > 7) return 0;
    return ports[port_index];
}

/**
 * @brief Initializes a GPIO pin with the given configuration.
 *
 * Clears and sets relevant registers for mode, type, speed, and pull.
 *
 * @param cfg GPIO configuration struct.
 */
void gpio_init(gpio_config_t cfg) {
    uint8_t port_index = GET_PORT(cfg.pin);
    uint8_t pin_num = GET_PIN(cfg.pin);
    GPIO_TypeDef *port = get_gpio_port(port_index);

    // Clear previous config
    port->MODER   &= ~(0x03 << (pin_num * 2));
    port->OTYPER  &= ~(1 << pin_num);
    port->OSPEEDR &= ~(0x03 << (pin_num * 2));
    port->PUPDR   &= ~(0x03 << (pin_num * 2));

    // Apply new config
    port->MODER   |= ((cfg.mode   & 0x03) << (pin_num * 2));
    port->OTYPER  |= ((cfg.otype  & 0x01) << pin_num);
    port->OSPEEDR |= ((cfg.speed  & 0x03) << (pin_num * 2));
    port->PUPDR   |= ((cfg.pull   & 0x03) << (pin_num * 2));
}

/**
 * @brief Sets alternate function (AFx) for a GPIO pin.
 *
 * Uses AFRL (pins 0–7) or AFRH (pins 8–15).
 *
 * @param pin Packed pin format (port << 8 | pin number).
 * @param af  Alternate function number (0–15).
 */
void gpio_set_af(uint16_t pin, uint8_t af) {
    uint8_t port_index = GET_PORT(pin);
    uint8_t pin_num = GET_PIN(pin);
    GPIO_TypeDef *port = get_gpio_port(port_index);

    if (pin_num <= 7) {
        port->AFRL &= ~(0xF << (4 * pin_num));
        port->AFRL |=  (af  << (4 * pin_num));
    } else {
        port->AFRH &= ~(0xF << (4 * (pin_num - 8)));
        port->AFRH |=  (af  << (4 * (pin_num - 8)));
    }
}

/**
 * @brief Changes the mode of a pin at runtime.
 *
 * Can be used to repurpose a pin without full re-initialization.
 *
 * @param gpio_pin Packed pin format.
 * @param mode New GPIO mode (input/output/etc.).
 */
void gpio_mode(uint16_t gpio_pin, gpio_mode_t mode) {
    uint8_t port_index = GET_PORT(gpio_pin);
    uint8_t pin_num = GET_PIN(gpio_pin);
    GPIO_TypeDef *port = get_gpio_port(port_index);

    port->MODER &= ~(0x3 << (2 * pin_num));
    port->MODER |=  ((mode & 0x3U) << (2 * pin_num));
}

/**
 * @brief Writes HIGH or LOW to a GPIO pin.
 *
 * Uses BSRR for atomic set/reset.
 *
 * @param gpio_pin Packed pin format.
 * @param state 0 = LOW, non-zero = HIGH.
 */
void gpio_write(uint16_t gpio_pin, uint8_t state) {
    uint8_t port_index = GET_PORT(gpio_pin);
    uint8_t pin_num = GET_PIN(gpio_pin);
    GPIO_TypeDef *port = get_gpio_port(port_index);

    if (state) {
        port->BSRR = (1 << pin_num);           // Set
    } else {
        port->BSRR = (1 << (pin_num + 16));    // Reset
    }
}

/**
 * @brief Reads the current digital state of a pin.
 *
 * @param gpio_pin Packed pin format.
 * @return int 1 = HIGH, 0 = LOW.
 */
int gpio_read(uint16_t gpio_pin) {
    uint8_t port_index = GET_PORT(gpio_pin);
    uint8_t pin_num = GET_PIN(gpio_pin);
    GPIO_TypeDef *port = get_gpio_port(port_index);

    return (port->IDR & (1 << pin_num)) ? 1 : 0;
}
