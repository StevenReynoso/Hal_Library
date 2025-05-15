#ifndef STM32F4_SYSTICK_H
#define STM32F4_SYSTICK_H

#include <stdint.h>

typedef struct{
    volatile uint32_t SYST_CSR;
    volatile uint32_t SYST_RVR;
    volatile uint32_t SYST_CVR;
    volatile uint32_t SYST_CALIB;

} SysTick_Type;

#endif //STM32F4_SYSTICK_H