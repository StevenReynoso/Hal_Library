/**
 * @file hal_systick.c
 * @brief SysTick timer implementation for STM32F411RE.
 *
 * This file implements initialization and delay routines using the Cortex-M4 SysTick timer.
 * Designed for simple blocking delays in microseconds or milliseconds. Suitable for
 * low-frequency, low-complexity tasks or startup-time code in bare-metal applications.
 */

#include <stdint.h>
#include "hal_systick.h"

/// @brief Default core clock frequency in Hz (used for delay calculations).
uint32_t SystemCoreClock = 72000000U;

/**
 * @brief Initializes the SysTick timer with a given tick interval.
 *
 * Sets the SysTick LOAD and VAL registers, and enables the counter using the processor clock.
 *
 * @param ticks Number of core clock cycles between rollovers.
 *
 * @note This does not set up interrupts. The timer is just running passively unless used manually.
 */
void systick_init(uint32_t ticks){
    SysTick->LOAD = ticks - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x05; // Enable SysTick with processor clock, no interrupt
}

/**
 * @brief Blocks for a specified number of milliseconds using SysTick.
 *
 * Configures SysTick for 1ms tick rate and blocks the CPU until the full delay is complete.
 * After the delay, SysTick is disabled to save power.
 *
 * @param ms Number of milliseconds to delay.
 */
void delay_ms(uint32_t ms)
{
    SysTick->LOAD = (SystemCoreClock / 1000U) - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = CTRL_CLKSOURCE | CTRL_ENABLE;

    for (uint32_t i = 0; i < ms; i++) {
        while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0);
    }

    SysTick->CTRL = 0; // Disable after delay
}

/**
 * @brief Blocks for a specified number of microseconds using SysTick.
 *
 * Uses a single-shot delay by measuring elapsed ticks from the SysTick value register.
 *
 * @param us Number of microseconds to delay.
 *
 * @note Assumes `SystemCoreClock` is valid and SYSTICK_LOAD is set appropriately.
 */
void delay_us(uint32_t us){
    uint32_t ticks = (us * SYSTICK_LOAD) - SYSTICK_DELAY_CALIB;
    uint32_t start = SysTick->VAL;
    while ((start - SysTick->VAL) < ticks);
}

/**
 * @brief Updates the global SystemCoreClock variable.
 *
 * Used to keep delay calculations accurate after PLL or clock source changes.
 * This does not change the hardware clock — it only updates software logic.
 *
 * @param new_freq New core clock frequency in Hz.
 */
void system_core_clock_update(uint32_t new_freq){
    SystemCoreClock = new_freq;
}
