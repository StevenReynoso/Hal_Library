/**
 * @file hal_tim.c
 * @brief Timer initialization for 1 Hz timebase using STM32F411RE general-purpose timers.
 *
 * Implements a simple timer setup for generating a 1-second overflow interval using prescaler
 * and auto-reload configuration. Intended for polling loops, LED blinking, or software timers.
 */

#include <stdint.h>
#include "hal_tim.h"
#include "hal_rcc.h"

/**
 * @brief Initializes the specified timer to overflow at 1 Hz.
 *
 * This function calculates a prescaler and auto-reload value so that the timer
 * overflows every 1 second. It assumes the timer is driven by `clk_hz`, which should
 * be the correct APB1 or APB2 timer clock depending on the TIM peripheral.
 *
 * @param timx Pointer to the timer peripheral (e.g., `TIM2`, `TIM3`, etc.)
 * @param clk_hz The timer input clock frequency in Hz.
 *
 * @note This function enables the timer but does not enable interrupts.
 *       You must call `rcc_enable_tim()` beforehand to ensure the clock is active.
 */
void tim_1hz_init(TIM_TypeDef *timx, uint32_t clk_hz){
    // Enable timer clock through RCC
    rcc_enable_tim(timx);

    // Set prescaler: divides clock down to 45_000 Hz (assuming 72 MHz clock)
    timx->PSC = 1600 - 1;

    // Set auto-reload so timer overflows every 1 second
    timx->ARR = (clk_hz / (timx->PSC + 1));

    // Clear the counter
    timx->CNT = 0;

    // Enable the timer (CEN = 1)
    timx->CR1 |= (1U << 0); 
}