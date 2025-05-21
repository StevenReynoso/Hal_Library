#ifndef HAL_SYSTICK_H
#define HAL_SYSTICK_H
#include <stdint.h>
#include "stm32f4_systick.h"


void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void systick_init(uint32_t ticks);
void system_core_clock_update(uint32_t new_freq);

#endif // HAL_SYSTICK_H