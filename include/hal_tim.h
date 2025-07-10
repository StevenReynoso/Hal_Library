/**
 * @file hal_tim.h
 * @brief Timer HAL interface for STM32F446RE (basic and PWM modes).
 *
 * Provides initialization and configuration functions for STM32 timers,
 * including basic up-counting timers (e.g., 1 Hz timebase) and PWM output
 * using general-purpose or advanced-control TIMx peripherals.
 *
 * @note Designed for register-level programming without CMSIS or STM HAL.
 * @author
 * Steven Reynoso
 */

#ifndef HAL_TIM_H
#define HAL_TIM_H

#include <stdint.h>
#include "stm32f4_tim.h"

/** @defgroup HAL_TIM_Functions Timer HAL API
 *  @brief High-level timer setup functions for STM32F446RE.
 *  @{
 */

/**
 * @brief Initializes the specified timer to generate a 1 Hz overflow.
 *
 * Sets up prescaler and ARR values to create a 1-second periodic timer overflow.
 * Useful for software delay loops, polling, or LED blinking.
 *
 * @param timx Timer instance (e.g., TIM2, TIM3).
 * @param clk_hz Timer input clock frequency in Hz (APB1/APB2 dependent).
 *
 * @note Timer is started immediately. No interrupt or output configuration is done.
 */
void tim_1hz_init(TIM_TypeDef *timx, uint32_t clk_hz);

/**
 * @brief Initializes a timer for PWM output.
 *
 * Configures prescaler and auto-reload register to define the PWM frequency.
 * Use with `tim_pwm_config_channel()` to assign duty cycle and channel behavior.
 *
 * @param timx Pointer to TIMx instance.
 * @param prescaler Prescaler value (PSC register) — pass raw value, not minus one.
 * @param arr Auto-reload value (ARR register) — pass raw value, not minus one.
 */
void tim_pwm_init(TIM_TypeDef *timx, uint16_t prescaler, uint16_t arr);

/**
 * @brief Configures a specific channel of the timer for PWM output.
 *
 * Sets PWM mode 1 on the given channel, sets duty cycle via CCRx, enables preload
 * for smooth transitions, and enables channel output.
 *
 * @param timx Timer instance (e.g., TIM2).
 * @param channel Channel number (1–4).
 * @param duty PWM duty cycle (0–ARR). Maps directly to CCRx.
 */
void tim_pwm_config_channel(TIM_TypeDef *timx, uint8_t channel, uint16_t duty);

/**
 * @brief Starts the timer counter (CEN = 1).
 *
 * Call this after timer and channel configuration to begin PWM or timebase operation.
 *
 * @param timx Timer instance (e.g., TIM2).
 */
void tim_pwm_start(TIM_TypeDef *timx);

/** @} */

#endif // HAL_TIM_H
