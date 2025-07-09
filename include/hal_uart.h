/**
 * @file hal_uart.h
 * @brief High-level UART interface for STM32F411RE.
 *
 * Provides simple UART communication functions including initialization,
 * string transmission, and byte reception using polling (blocking mode).
 * Built on top of direct register access to STM32F4 UART hardware.
 */

#ifndef HAL_UART_H
#define HAL_UART_H

#include "stm32f4_uart.h"

/**
 * @brief Receives a single byte from the UART peripheral (blocking).
 *
 * Waits until the RXNE (Receive Not Empty) flag is set, then reads from the data register.
 *
 * @param uart Pointer to UART peripheral (e.g., `USART1`, `USART2`, etc.)
 * @return uint8_t Received byte from the UART.
 *
 * @note This function blocks until a byte is available in the receive buffer.
 */
uint8_t uart_read(UART_TypeDef *uart);

/**
 * @brief Sends a null-terminated string over UART (blocking).
 *
 * Transmits each character in the given string one by one, waiting for
 * the TXE (Transmit Empty) flag before sending the next character.
 *
 * @param uart Pointer to UART peripheral.
 * @param msg  Null-terminated string to transmit.
 *
 * @note This function blocks until all characters have been sent.
 */
void uart_print(UART_TypeDef *uart, const char *msg);

/**
 * @brief Initializes the UART peripheral with the given baud rate.
 *
 * Enables the UART clock (must be done separately), configures the baud rate
 * using BRR, and enables transmitter and receiver functionality.
 *
 * @param uart       Pointer to UART peripheral to configure.
 * @param periph_clk Peripheral clock frequency in Hz (e.g., 16000000 for 16 MHz).
 * @param baud       Desired baud rate (use `baud_rate_t` enum for common rates).
 *
 * @note Does not configure interrupts or DMA. This is a basic polling-based setup.
 */
void uart_init(UART_TypeDef *uart, uint32_t periph_clk, baud_rate_t baud);

#endif // HAL_UART_H
