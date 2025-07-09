/**
 * @file stm32f4_tim.h
 * @brief STM32F446RE Timer peripheral base addresses and register map.
 *
 * Provides base address definitions and register struct for general-purpose,
 * advanced-control, and basic timers on STM32F446RE. Use this header to interact
 * with TIMx peripherals directly via memory-mapped I/O.
 *
 * @note
 * - This struct is modeled after the most feature-complete timers (TIM1/TIM8).
 * - Not all timers implement all fields (e.g., TIM6/7 lack CCRx, BDTR, etc).
 * - Check the STM32F446RE reference manual (RM0390) before accessing advanced fields.
 *
 * @author
 * Steven Reynoso
 */

#ifndef STM32F4_TIM_H
#define STM32F4_TIM_H

#include <stdint.h>

/* === APB2 Timers (Advanced / GP) === */
#define TIM1  ((TIM_TypeDef *) 0x40010000UL)
#define TIM8  ((TIM_TypeDef *) 0x40010400UL)
#define TIM9  ((TIM_TypeDef *) 0x40014000UL)
#define TIM10 ((TIM_TypeDef *) 0x40014400UL)
#define TIM11 ((TIM_TypeDef *) 0x40014800UL)

/* === APB1 Timers (General Purpose / Basic) === */
#define TIM2  ((TIM_TypeDef *) 0x40000000UL)
#define TIM3  ((TIM_TypeDef *) 0x40000400UL)
#define TIM4  ((TIM_TypeDef *) 0x40000800UL)
#define TIM5  ((TIM_TypeDef *) 0x40000C00UL)
#define TIM6  ((TIM_TypeDef *) 0x40001000UL)
#define TIM7  ((TIM_TypeDef *) 0x40001400UL)
#define TIM12 ((TIM_TypeDef *) 0x40001800UL)
#define TIM13 ((TIM_TypeDef *) 0x40001C00UL)
#define TIM14 ((TIM_TypeDef *) 0x40002000UL)

/**
 * @brief Register map for STM32F4 TIMx peripheral.
 *
 * Represents the memory layout of a typical timer. Use this with TIMx defines
 * to access or configure timer features directly.
 *
 * @note
 * - TIM1 and TIM8 support all fields, including `RCR` and `BDTR`.
 * - Basic timers (TIM6, TIM7) lack many fields like `CCR1-CCR4`, `BDTR`, etc.
 * - General-purpose timers support capture/compare, but not break/dead-time.
 */
typedef struct {
    volatile uint32_t CR1;     /**< Control Register 1 */
    volatile uint32_t CR2;     /**< Control Register 2 */
    volatile uint32_t SMCR;    /**< Slave Mode Control Register */
    volatile uint32_t DIER;    /**< DMA/Interrupt Enable Register */
    volatile uint32_t SR;      /**< Status Register */
    volatile uint32_t EGR;     /**< Event Generation Register */
    volatile uint32_t CCMR1;   /**< Capture/Compare Mode Register 1 */
    volatile uint32_t CCMR2;   /**< Capture/Compare Mode Register 2 */
    volatile uint32_t CCER;    /**< Capture/Compare Enable Register */
    volatile uint32_t CNT;     /**< Counter */
    volatile uint32_t PSC;     /**< Prescaler */
    volatile uint32_t ARR;     /**< Auto-Reload Register */
    volatile uint32_t RCR;     /**< Repetition Counter (Only TIM1, TIM8) */
    volatile uint32_t CCR1;    /**< Capture/Compare Register 1 */
    volatile uint32_t CCR2;    /**< Capture/Compare Register 2 */
    volatile uint32_t CCR3;    /**< Capture/Compare Register 3 */
    volatile uint32_t CCR4;    /**< Capture/Compare Register 4 */
    volatile uint32_t BDTR;    /**< Break and Dead-Time Register (Only TIM1, TIM8) */
    volatile uint32_t DCR;     /**< DMA Control Register */
    volatile uint32_t DMAR;    /**< DMA Address for Full Transfer */
} TIM_TypeDef;

#endif // STM32F4_TIM_H
