/**
 * @file hal_systick.h
 * @brief High-level SysTick interface for STM32F411RE.
 *
 * Provides basic delay functions and initialization routines using
 * the Cortex-M4 SysTick timer. Designed for precise microsecond
 * and millisecond delays in bare-metal applications.
 */

#ifndef HAL_SYSTICK_H
#define HAL_SYSTICK_H

#include <stdint.h>
#include "stm32f4_systick.h"

/**
 * @brief Delays execution for a specified number of microseconds.
 *
 * This function uses the SysTick timer to block the CPU for an accurate
 * delay in microseconds. Assumes SysTick has been configured for 1µs ticks.
 *
 * @param us Number of microseconds to delay.
 *
 * @note This is a blocking delay — the CPU will halt until the delay finishes.
 */
void delay_us(uint32_t us);

/**
 * @brief Delays execution for a specified number of milliseconds.
 *
 * Uses `delay_us()` internally to create a millisecond-scale blocking delay.
 *
 * @param ms Number of milliseconds to delay.
 *
 * @note This is a blocking delay — not suitable for power-efficient sleep modes.
 */
void delay_ms(uint32_t ms);

/**
 * @brief Initializes the SysTick timer with a specific tick interval.
 *
 * This function configures the SysTick LOAD register to define how often
 * the timer will roll over. Typically used for creating fixed timebases.
 *
 * @param ticks Number of core clock cycles between timer rollovers.
 *
 * @note A value of (SystemCoreClock / 1000) results in a 1ms tick interval.
 */
void systick_init(uint32_t ticks);

/**
 * @brief Updates the system core clock frequency.
 *
 * Updates the global variable `SystemCoreClock` so delay functions
 * and tick calculations stay accurate after PLL changes or clock reconfiguration.
 *
 * @param new_freq New system clock frequency in Hz (e.g., 16000000 for 16 MHz).
 *
 * @note This does not actually change the hardware clock — it only updates
 *       the variable used in delay calculations.
 */
void system_core_clock_update(uint32_t new_freq);

#endif // HAL_SYSTICK_H
