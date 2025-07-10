/**
 * @file stm32f4_tim.h
 * @brief Register map and base addresses for STM32F446RE TIM peripherals.
 *
 * This header defines memory-mapped register structures and base addresses
 * for general-purpose, advanced-control, and basic timers in the STM32F446RE.
 * Use this for low-level, register-direct control of TIM peripherals.
 *
 * @note
 * - TIM1 and TIM8 are advanced-control timers (support RCR, BDTR, etc.).
 * - TIM2–5, TIM9–14 are general-purpose timers with capture/compare.
 * - TIM6 and TIM7 are basic timers (no CCRx, BDTR, etc.).
 *
 * Refer to RM0390 for full timer functionality and limitations per TIMx instance.
 *
 * @author
 * Steven Reynoso
 */

#ifndef STM32F4_TIM_H
#define STM32F4_TIM_H

#include <stdint.h>

/** @defgroup TIM_BaseAddresses Timer Peripheral Base Addresses
 *  @brief Memory-mapped base addresses for STM32F446RE TIM peripherals.
 *  @{
 */
#define TIM1   ((TIM_TypeDef *) 0x40010000UL) /**< APB2: Advanced timer */
#define TIM8   ((TIM_TypeDef *) 0x40010400UL)
#define TIM9   ((TIM_TypeDef *) 0x40014000UL)
#define TIM10  ((TIM_TypeDef *) 0x40014400UL)
#define TIM11  ((TIM_TypeDef *) 0x40014800UL)

#define TIM2   ((TIM_TypeDef *) 0x40000000UL) /**< APB1: General-purpose */
#define TIM3   ((TIM_TypeDef *) 0x40000400UL)
#define TIM4   ((TIM_TypeDef *) 0x40000800UL)
#define TIM5   ((TIM_TypeDef *) 0x40000C00UL)
#define TIM6   ((TIM_TypeDef *) 0x40001000UL) /**< Basic timer (no CCRx) */
#define TIM7   ((TIM_TypeDef *) 0x40001400UL)
#define TIM12  ((TIM_TypeDef *) 0x40001800UL)
#define TIM13  ((TIM_TypeDef *) 0x40001C00UL)
#define TIM14  ((TIM_TypeDef *) 0x40002000UL)
/** @} */

/** @defgroup TIM_CR_BitDefinitions Timer Register Bit Masks
 *  @brief Common bit definitions for configuring TIMx peripherals.
 *  @{
 */
#define TIM_CR1_CEN         (1U << 0)  /**< Counter enable */
#define TIM_CR1_ARPE        (1U << 7)  /**< Auto-reload preload enable */

#define TIM_EGR_UG          (1U << 0)  /**< Update generation */

#define TIM_CCER_CC1E       (1U << 0)  /**< Channel 1 output enable */
#define TIM_CCER_CC2E       (1U << 4)
#define TIM_CCER_CC3E       (1U << 8)
#define TIM_CCER_CC4E       (1U << 12)

#define TIM_CCMR1_OC1M_PWM1 (0x6 << 4) /**< PWM Mode 1 for CH1 */
#define TIM_CCMR1_OC1PE     (1U << 3)  /**< Output Compare 1 preload enable */
/** @} */

/**
 * @brief TIMx register map structure.
 *
 * This struct maps the memory layout of a general-purpose or advanced TIMx
 * peripheral. Not all fields are supported on all timers (e.g., TIM6/7).
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
    volatile uint32_t CNT;     /**< Counter value */
    volatile uint32_t PSC;     /**< Prescaler */
    volatile uint32_t ARR;     /**< Auto-reload register */
    volatile uint32_t RCR;     /**< Repetition counter (advanced timers only) */
    volatile uint32_t CCR1;    /**< Capture/Compare Register 1 */
    volatile uint32_t CCR2;    /**< Capture/Compare Register 2 */
    volatile uint32_t CCR3;    /**< Capture/Compare Register 3 */
    volatile uint32_t CCR4;    /**< Capture/Compare Register 4 */
    volatile uint32_t BDTR;    /**< Break and Dead-Time Register (advanced only) */
    volatile uint32_t DCR;     /**< DMA Control Register */
    volatile uint32_t DMAR;    /**< DMA Address for Full Transfer */
} TIM_TypeDef;

#endif // STM32F4_TIM_H
