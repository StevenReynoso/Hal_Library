/**
 * @file stm32f4_systick.h
 * @brief Register map and macros for SysTick timer on STM32F411RE.
 *
 * This header defines the memory-mapped structure and bit masks for the Cortex-M4 SysTick timer.
 * SysTick is a simple 24-bit timer integrated into the Cortex core, commonly used for 
 * periodic interrupts or delay generation in bare-metal systems.
 */

#ifndef STM32F4_SYSTICK_H
#define STM32F4_SYSTICK_H

#include <stdint.h>

/**
 * @brief Base address of SysTick timer.
 *
 * SysTick is part of the Cortex-M core, not the STM32 peripheral map.
 */
#define SysTick ((SysTick_Type *) 0xE000E010UL)

/**
 * @brief SysTick load value for 1 microsecond tick.
 *
 * This macro assumes `SystemCoreClock` is defined elsewhere in your project.
 * You can use this to configure delays in microseconds.
 */
#define SYSTICK_LOAD (SystemCoreClock / 1000000U)

/**
 * @brief Calibrated delay adjustment value.
 *
 * Used to fine-tune delay loops to account for timing overhead. Default is 0.5µs compensation.
 */
#define SYSTICK_DELAY_CALIB (SYSTICK_LOAD >> 1)

/// @name SysTick Control Register Bit Masks
/// @{
#define CTRL_ENABLE     (1U << 0)   /**< Enables the counter */
#define CTRL_CLKSOURCE  (1U << 2)   /**< Clock source: 1 = processor clock, 0 = external */
#define CTRL_COUNTFLAG  (1U << 16)  /**< Set to 1 when timer counts to 0 (auto-clears on read) */
/// @}

/**
 * @brief Register layout of the SysTick peripheral.
 *
 * The SysTick timer consists of four registers used for setup, value tracking, and calibration.
 * It is commonly used for delay loops and periodic task timing in embedded systems.
 */
typedef struct {
    volatile uint32_t CTRL;   /**< Control and status register */
    volatile uint32_t LOAD;   /**< Reload value register (24-bit max) */
    volatile uint32_t VAL;    /**< Current counter value */
    volatile uint32_t CALIB;  /**< Calibration value register */
} SysTick_Type;

#endif // STM32F4_SYSTICK_H
