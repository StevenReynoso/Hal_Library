/*
 * Systick Hal Driver
 * ------------------------
 * - systick_init(ticks): initalizes systick with given tick rate 
 * - delay_us(us) : delays in microseconds using the systick timer after initialized
 * - delay_ms(ms) : delays in milliseconds, turns on systick, then disables, for power management.
 * - system_core_clock_update(new_freq) : allows the user to change the default core clock to their liking or system.
 * 
 * Default system clock value is set to 72000000U 
 * systick load configured as SystemCoreClock/1000000U
*/

#include <stdint.h>
#include "../hal_systick.h"

uint32_t SystemCoreClock = 72000000U;

void systick_init(uint32_t ticks){
    SysTick->LOAD = ticks - 1;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x05; // Enable + processor clock
}

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

void delay_us(uint32_t us){
    uint32_t ticks = (us * SYSTICK_LOAD) - SYSTICK_DELAY_CALIB;
    uint32_t start = SysTick->VAL;
    while ((start - SysTick->VAL) < ticks);
}

void system_core_clock_update(uint32_t new_freq){
    SystemCoreClock = new_freq;
}