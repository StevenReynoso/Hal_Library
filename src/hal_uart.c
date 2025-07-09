/**
 * @file hal_uart.c
 * @brief UART initialization and communication functions for STM32F411RE.
 *
 * Implements basic UART send/receive routines using polling.
 * Includes baud rate configuration and a simple `printf`-style string writer.
 * This setup assumes no interrupt or DMA use — purely blocking mode.
 */

#include <stdint.h>
#include "hal_uart.h"

/**
 * @brief Configures the UART baud rate register (BRR).
 *
 * Computes and sets the baud rate using the formula:
 *   BRR = peripheral_clock / desired_baud_rate
 *
 * Rounded with integer division for better accuracy without floating point math.
 *
 * @param uart Pointer to UART peripheral.
 * @param periph_clk UART peripheral clock frequency in Hz.
 * @param rate Desired baud rate (as a `baud_rate_t` enum).
 */
static void configure_baud(UART_TypeDef *uart, uint32_t periph_clk, baud_rate_t rate) {
    uart->BRR = ((periph_clk + (rate / 2U)) / rate);
}

/**
 * @brief Reads a single byte from UART (blocking).
 *
 * Waits until a byte is received (RXNE flag is set), then returns it.
 *
 * @param uart Pointer to UART peripheral.
 * @return uint8_t The received byte.
 */
uint8_t uart_read(UART_TypeDef *uart) {
    while (!(uart->SR & USART_SR_RXNE)) {
        // wait until data is received
    }

    return (uint8_t)(uart->DR & 0xFF);
}

/**
 * @brief Sends a single character over UART (blocking).
 *
 * Waits until TXE is set, then writes to the data register.
 *
 * @param uart Pointer to UART peripheral.
 * @param data Character to transmit.
 */
static void uart_write(UART_TypeDef *uart, char data) {
    while (!(uart->SR & USART_SR_TXE)) {
        // wait until transmit buffer is empty
    }

    uart->DR = data;
}

/**
 * @brief Sends a null-terminated string over UART (blocking).
 *
 * Calls `uart_write()` repeatedly to send each character in the string.
 *
 * @param uart Pointer to UART peripheral.
 * @param msg Null-terminated string to send.
 */
void uart_print(UART_TypeDef *uart, const char *msg) {
    while (*msg) {
        uart_write(uart, *msg++);
    }
}

/**
 * @brief Initializes UART peripheral for standard 8N1 config.
 *
 * Sets baud rate, disables parity, selects 1 stop bit and 8 data bits,
 * and enables both transmit and receive logic.
 *
 * @param uart Pointer to UART peripheral to initialize.
 * @param periph_clk Peripheral clock frequency in Hz.
 * @param baud Desired baud rate.
 *
 * @note You must enable the RCC clock for the UART externally before calling this.
 */
void uart_init(UART_TypeDef *uart, uint32_t periph_clk, baud_rate_t baud) {
    // Disable UART before configuration
    uart->CR1 &= ~USART_CR1_UE;

    configure_baud(uart, periph_clk, baud);

    uart->CR1 &= ~(1 << 12);  /**< 8 data bits */
    uart->CR2 &= ~(3 << 12);  /**< 1 stop bit */
    uart->CR1 &= ~(1 << 10);  /**< No parity */

    // Enable UART, transmitter, and receiver
    uart->CR1 |= USART_CR1_UE;
    uart->CR1 |= USART_CR1_TE | USART_CR1_RE;
}
