/**
 * @file hal_tim.h
 * @brief Basic timer initialization interface for STM32F411RE.
 *
 * This header exposes a helper function for initializing general-purpose timers
 * to generate a 1 Hz timebase using prescaler and auto-reload configuration.
 */

#ifndef HAL_TIM_H
#define HAL_TIM_H

#include <stdint.h>
#include "stm32f4_tim.h"

/**
 * @brief Initializes the specified timer to generate a 1 Hz timebase.
 *
 * Configures the timer's prescaler and auto-reload register (ARR) so that
 * it overflows every 1 second. This can be used for timekeeping, simple
 * blinking, or periodic polling loops.
 *
 * @param timx Pointer to the timer peripheral (e.g., `TIM2`, `TIM3`, etc.)
 * @param clk_hz Input clock frequency in Hz (usually equal to APB1/APB2 timer clock)
 *
 * @note This function only sets up the timer for basic up-counting operation.
 *       It does not enable interrupts or configure any output channels.
 */
void tim_1hz_init(TIM_TypeDef *timx, uint32_t clk_hz);

#endif // HAL_TIM_H
