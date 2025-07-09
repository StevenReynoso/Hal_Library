/**
 * @file hal_rcc.h
 * @brief Clock control utility functions for enabling STM32F4 peripherals.
 *
 * This header provides simplified clock enabling functions for peripherals
 * like GPIO, UART, SPI, and TIM using direct register access. Works in 
 * conjunction with `stm32f4_rcc.h` register definitions.
 */


#ifndef HAL_RCC_H
#define HAL_RCC_H

#include "stm32f4_rcc.h"
#include "hal_spi.h"
#include "hal_tim.h"
#include "hal_uart.h"


/**
 * @brief Generic register-based peripheral clock enable.
 *
 * Sets the bit at `bit_pos` in the register pointed to by `reg`. Useful for enabling
 * any RCC clock register (e.g., `RCC->APB1ENR`, `RCC->AHB1ENR`).
 *
 * @param reg Pointer to RCC register to modify.
 * @param bit_pos Bit position to set (0–31).
 */
void rcc_enable(volatile uint32_t *reg, uint8_t bit_pos);

/**
 * @brief Enables the peripheral clock for a specific TIM instance.
 *
 * Determines the correct RCC register and bit position based on the `TIMx` pointer
 * and sets the appropriate bit to enable the clock.
 *
 * @param timx Pointer to TIM peripheral base (e.g., `TIM2`, `TIM3`).
 */
void rcc_enable_tim(TIM_TypeDef *timx);

/**
 * @brief Enables the peripheral clock for a GPIO port.
 *
 * Accepts a port index (e.g., 0 = GPIOA, 1 = GPIOB, ...) and enables the corresponding
 * bit in `RCC->AHB1ENR`.
 *
 * @param port_index Integer index representing the GPIO port.
 */
void rcc_enable_gpio(uint16_t port_index);

/**
 * @brief Enables the peripheral clock for a UART/USART peripheral.
 *
 * Automatically determines whether the UART is on APB1 or APB2 and sets the
 * corresponding enable bit.
 *
 * @param uart Pointer to UART peripheral (e.g., `USART1`, `USART2`).
 */
void rcc_enable_uart(UART_TypeDef *uart);

/**
 * @brief Enables the peripheral clock for an SPI peripheral.
 *
 * Determines whether the SPI instance is on APB1 or APB2 and enables the correct bit.
 *
 * @param spix Pointer to SPI peripheral (e.g., `SPI1`, `SPI2`).
 */
void rcc_enable_spi(SPI_TypeDef * spix);
#endif //HAL_RCC_H