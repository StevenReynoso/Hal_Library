/**
 * @file hal_types.h
 * @brief Core HAL type definitions and centralized module includes for STM32F411RE.
 *
 * This header includes all major HAL modules (GPIO, RCC, SysTick, TIM, UART, SPI)
 * and defines basic types used across the HAL codebase. It serves as a common import
 * point for user applications and higher-level drivers.
 */

#ifndef HAL_TYPES_H
#define HAL_TYPES_H

#include <stdint.h>

#include "hal_gpio.h"
#include "hal_rcc.h"
#include "hal_systick.h"
#include "hal_tim.h"
#include "hal_uart.h"
#include "hal_spi.h"

/**
 * @brief Boolean type definition.
 *
 * Provides a basic `BOOL` type with `TRUE` and `FALSE` values for clarity.
 * Useful in embedded code where `stdbool.h` may be avoided for portability
 * or coding style preference.
 */
typedef enum {
    FALSE = 0,  /**< Logical false (0) */
    TRUE  = 1   /**< Logical true  (1) */
} BOOL;

#endif // HAL_TYPES_H
