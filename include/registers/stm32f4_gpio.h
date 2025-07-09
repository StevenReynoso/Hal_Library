/**
 * @file hal_gpio.h
 * @brief STM32F4 GPIO peripheral definitions and configuration structures.
 *
 * This header provides:
 * - Base address macros for all GPIO ports (A–H)
 * - A compact pin representation using packed encoding
 * - A register layout for direct register access
 * - GPIO configuration structures and enums
 *
 * Designed for use in bare-metal STM32F411RE projects without STM HAL or CMSIS.
 */

#ifndef STM32F4_GPIO_H
#define STM32F4_GPIO_H

#include <stdint.h>

/// @name GPIO Base Addresses (AHB1 bus mapped)
/// @{
#define GPIOA ((GPIO_TypeDef *) 0x40020000UL)
#define GPIOB ((GPIO_TypeDef *) 0x40020400UL)
#define GPIOC ((GPIO_TypeDef *) 0x40020800UL)
#define GPIOD ((GPIO_TypeDef *) 0x40020C00UL)
#define GPIOE ((GPIO_TypeDef *) 0x40021000UL)
#define GPIOF ((GPIO_TypeDef *) 0x40021400UL)
#define GPIOG ((GPIO_TypeDef *) 0x40021800UL)
#define GPIOH ((GPIO_TypeDef *) 0x40021C00UL)
/// @}

/**
 * @brief Helper macro to pack a GPIO port and pin number into a single value.
 * 
 * @param port Letter ('A' to 'H')
 * @param pin  Pin number (0 to 15)
 * @return uint16_t Encoded pin: (port_index << 8) | pin_number
 */
#define PIN(port, pin) (((port - 'A') << 8) | (pin))

/**
 * @brief Extract GPIO port index from packed pin.
 * 
 * @param p Packed pin value.
 * @return uint8_t Port index: 0 = A, 1 = B, ..., 7 = H
 */
#define GET_PORT(p) (((p) >> 8) & 0xFF)

/**
 * @brief Extract GPIO pin number from packed pin.
 * 
 * @param p Packed pin value.
 * @return uint8_t Pin number (0 to 15)
 */
#define GET_PIN(p) ((p) & 0xFF)

/**
 * @brief Register map for STM32F4 GPIO peripheral.
 */
typedef struct {
    volatile uint32_t MODER;    /**< Mode register */
    volatile uint32_t OTYPER;   /**< Output type register */
    volatile uint32_t OSPEEDR;  /**< Output speed register */
    volatile uint32_t PUPDR;    /**< Pull-up/pull-down register */
    volatile uint32_t IDR;      /**< Input data register */
    volatile uint32_t ODR;      /**< Output data register */
    volatile uint32_t BSRR;     /**< Bit set/reset register */
    volatile uint32_t LCKR;     /**< Port configuration lock register */
    volatile uint32_t AFRL;     /**< Alternate function low register (pins 0–7) */
    volatile uint32_t AFRH;     /**< Alternate function high register (pins 8–15) */
} GPIO_TypeDef;

/**
 * @brief GPIO pin mode options (MODER register).
 */
typedef enum {
    GPIO_MODE_INPUT      = 0x00, /**< Input mode */
    GPIO_MODE_OUTPUT     = 0x01, /**< General purpose output */
    GPIO_MODE_ALTFUNC    = 0x02, /**< Alternate function (e.g. UART, SPI) */
    GPIO_MODE_ANALOG     = 0x03  /**< Analog mode */
} gpio_mode_t;

/**
 * @brief GPIO output type (OTYPER register).
 */
typedef enum {
    GPIO_OTYPE_PUSHPULL  = 0x00, /**< Push-pull output */
    GPIO_OTYPE_OPENDRAIN = 0x01  /**< Open-drain output */
} gpio_type_t;

/**
 * @brief GPIO output speed (OSPEEDR register).
 */
typedef enum {
    GPIO_SPEED_LOW       = 0x00, /**< Low speed */
    GPIO_SPEED_MEDIUM    = 0x01, /**< Medium speed */
    GPIO_SPEED_FAST      = 0x02, /**< Fast speed */
    GPIO_SPEED_HIGH      = 0x03  /**< High speed */
} gpio_speed_t;

/**
 * @brief Pull-up/pull-down options (PUPDR register).
 */
typedef enum {
    GPIO_NO_PULL         = 0x00, /**< No pull resistor */
    GPIO_PULL_UP         = 0x01, /**< Enable pull-up */
    GPIO_PULL_DOWN       = 0x02  /**< Enable pull-down */
} gpio_pupdr_t;

/**
 * @brief GPIO configuration structure used in gpio_init().
 */
typedef struct {
    uint16_t pin;            /**< Packed pin value: use PIN('A', 5) for PA5 */
    gpio_mode_t mode;        /**< Pin mode (input/output/alt/analog) */
    gpio_type_t otype;       /**< Output type (push-pull/open-drain) */
    gpio_speed_t speed;      /**< Output speed (low/medium/high) */
    gpio_pupdr_t pull;       /**< Pull resistor config (none/up/down) */
} gpio_config_t;

/**
 * @brief Enum for selecting GPIO ports by index.
 * Useful when referencing registers dynamically.
 */
typedef enum {
    GPIO_PORT_A = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G,
    GPIO_PORT_H
} gpio_port_t;

#endif // STM32F4_GPIO_H
