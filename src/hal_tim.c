/**
 * @file hal_tim.c
 * @brief Timer driver for STM32F446RE (PWM and basic timer functions).
 *
 * This file provides simple timer functions for:
 * - Generating basic delays (1 Hz overflow)
 * - Setting up PWM output (for motors, LEDs, etc.)
 *
 * This is part of a custom STM32F4 HAL written from scratch with no STM HAL or CMSIS.
 * All register access is direct and uses only official STM32 documentation.
 *
 * @author Steven Reynoso
 */

#include <stdint.h>
#include "hal_tim.h"
#include "hal_rcc.h"

/**
 * @brief Initialize a timer to overflow every 1 second (1Hz).
 *
 * This sets up a basic timer using a fixed prescaler and a computed auto-reload value.
 * When started, the timer will count up and overflow once every second.
 *
 * Useful for:
 * - Blinking an LED
 * - Basic delay loops (without interrupts)
 * - Timing functions where accuracy is not critical
 *
 * @param timx Pointer to the TIMx peripheral (e.g., TIM2, TIM3).
 * @param clk_hz The clock frequency driving the timer (in Hz).
 *
 * @note This function starts the timer immediately in upcounting mode.
 * @warning Assumes a hardcoded prescaler of 1600.
 */
void tim_1hz_init(TIM_TypeDef *timx, uint32_t clk_hz) {
    rcc_enable_tim(timx);

    timx->PSC = 1600 - 1;                            // Divide timer clock by 1600
    timx->ARR = clk_hz / (timx->PSC + 1);            // Set auto-reload value for 1 Hz
    timx->CNT = 0;                                   // Reset timer counter
    timx->CR1 |= TIM_CR1_CEN;                        // Start the timer
}

/**
 * @brief Configure a timer for PWM generation (base setup only).
 *
 * Sets the prescaler and ARR (auto-reload) values so the timer can run in PWM mode.
 * This does NOT configure any output channels. Use @ref tim_pwm_config_channel() for that.
 *
 * Useful for:
 * - Controlling servo motors
 * - Dimming LEDs
 * - Generating analog-like voltages via filtering
 *
 * @param timx Pointer to the TIMx peripheral (e.g., TIM2, TIM3).
 * @param prescaler Timer prescaler (raw value, not PSC - 1).
 *        Example: A value of 1600 divides the timer clock by 1600.
 * @param arr Auto-reload value — this sets the PWM period (raw).
 *        Example: An ARR of 100 creates a 0–99 count range.
 *
 * @note This function does NOT start the timer. Call @ref tim_pwm_start() to begin output.
 */
void tim_pwm_init(TIM_TypeDef *timx, uint16_t prescaler, uint16_t arr) {
    rcc_enable_tim(timx);

    timx->PSC = prescaler - 1;          // Set prescaler
    timx->ARR = arr - 1;                // Set auto-reload value
    timx->CR1 |= TIM_CR1_ARPE;          // Enable auto-reload preload
    timx->EGR |= TIM_EGR_UG;            // Apply changes immediately
}

/**
 * @brief Set up a specific PWM output channel on a timer.
 *
 * This configures a timer channel in PWM Mode 1, sets its duty cycle,
 * and enables output. It only supports Channel 1 for now.
 *
 * PWM Mode 1:
 * - Output is HIGH while counter < duty
 * - Output is LOW when counter ≥ duty
 *
 * @param timx Pointer to the TIMx peripheral (e.g., TIM2).
 * @param channel PWM channel to configure (1–4).
 * @param duty Duty cycle in ticks (0 to ARR value).
 *        Example: If ARR=100 and duty=25, output will be high for 25% of the time.
 *
 * @note Currently, only channel 1 is implemented. You can extend this function to handle CH2–CH4.
 */
void tim_pwm_config_channel(TIM_TypeDef *timx, uint8_t channel, uint16_t duty) {
    switch (channel) {
        case 1:
            // Configure Channel 1 for PWM Mode 1
            timx->CCMR1 &= ~(0x7 << 4);                              // Clear output mode bits
            timx->CCMR1 |= TIM_CCMR1_OC1M_PWM1 | TIM_CCMR1_OC1PE;    // Set PWM1 mode, enable preload
            timx->CCR1 = duty;                                       // Set duty cycle
            timx->CCER |= TIM_CCER_CC1E;                             // Enable output on channel 1
            break;

        default:
            // Not implemented
            break;
    }

    timx->EGR |= TIM_EGR_UG;  // Apply preload register changes
}

/**
 * @brief Start the timer to begin PWM or counting.
 *
 * This enables the counter and applies all preload values immediately.
 * It does NOT configure any output channels—only starts the base timer.
 *
 * @param timx Pointer to the TIMx peripheral.
 *
 * @note If PWM output is configured, the waveform will begin after this call.
 */
void tim_pwm_start(TIM_TypeDef *timx) {
    timx->EGR |= TIM_EGR_UG;        // Apply register preload values
    timx->CR1 |= TIM_CR1_CEN;       // Enable timer counter
}
