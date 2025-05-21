#ifndef STM32F4_SYSTICK_H
#define STM32F4_SYSTICK_H

#include <stdint.h>

#define SysTick ((SysTick_Type *) 0xE000E010)
#define SYSTICK_LOAD (SystemCoreClock / 1000000U)
#define SYSTICK_DELAY_CALIB (SYSTICK_LOAD >> 1)

// masks
#define CTRL_ENABLE     (1U << 0)
#define CTRL_CLKSOURCE  (1U << 2)
#define CTRL_COUNTFLAG  (1U << 16)

typedef struct{
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;

} SysTick_Type;

#endif //STM32F4_SYSTICK_H
