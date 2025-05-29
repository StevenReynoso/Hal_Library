#ifndef STM32F4_TIM_H
#define STM32F4_TIM_H
#include "stdint.h"

//APB2
#define TIM1  ((TIM_TypeDef *) 0x40010000UL)
#define TIM8  ((TIM_TypeDef *) 0x40010400UL)
#define TIM9  ((TIM_TypeDef *) 0x40014000UL)
#define TIM10 ((TIM_TypeDef *) 0x40014400UL)
#define TIM11 ((TIM_TypeDef *) 0x40014800UL)

//APB1
#define TIM2  ((TIM_TypeDef *) 0x40000000UL)
#define TIM3  ((TIM_TypeDef *) 0x40000400UL)
#define TIM4  ((TIM_TypeDef *) 0x40000800UL)
#define TIM5  ((TIM_TypeDef *) 0x40000C00UL)
#define TIM6  ((TIM_TypeDef *) 0x40001000UL)
#define TIM7  ((TIM_TypeDef *) 0x40001400UL)
#define TIM12 ((TIM_TypeDef *) 0x40001800UL)
#define TIM13 ((TIM_TypeDef *) 0x40001C00UL)
#define TIM14 ((TIM_TypeDef *) 0x40002000UL)

typedef struct{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;  // has output and input modes
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t RCR;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t BDTR;
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
}   TIM_TypeDef;

#endif // STM32F4_TIM_H