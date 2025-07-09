/**
 * @file stm32f4_uart.h
 * @brief Register map and macro definitions for UART/USART on STM32F411RE.
 *
 * This header defines memory-mapped structures and constants for the STM32F4 UART and USART
 * peripherals. UART is used for asynchronous serial communication between the MCU and
 * devices like PCs, GPS modules, Bluetooth, or other microcontrollers.
 *
 * Supported registers include control, status, baud rate, and data registers.
 */

#ifndef STM32F4_UART_H
#define STM32F4_UART_H

#include <stdint.h>

/// @name UART Base Addresses
/// These addresses correspond to USART peripherals supported on STM32F411RE.
/// @{
#define USART1 ((UART_TypeDef *) 0x40011000UL)  /**< High-speed USART (APB2) */
#define USART2 ((UART_TypeDef *) 0x40004400UL)  /**< General-purpose USART (APB1) */
#define USART3 ((UART_TypeDef *) 0x40004800UL)  /**< General-purpose USART (APB1) */
#define UART4  ((UART_TypeDef *) 0x40004C00UL)  /**< UART-only peripheral (APB1) */
#define UART5  ((UART_TypeDef *) 0x40005000UL)  /**< UART-only peripheral (APB1) */
#define USART6 ((UART_TypeDef *) 0x40011400UL)  /**< High-speed USART (APB2) */
/// @}

/// @name USART_CR1 Bit Definitions
/// @{
#define USART_CR1_RE   (1 << 2)   /**< Receiver enable */
#define USART_CR1_TE   (1 << 3)   /**< Transmitter enable */
#define USART_CR1_UE   (1 << 13)  /**< USART enable */
/// @}

/// @name USART_SR Bit Flags
/// @{
#define USART_SR_RXNE  (1 << 5)   /**< Receive data register not empty */
#define USART_SR_TXE   (1 << 7)   /**< Transmit data register empty */
/// @}

/**
 * @brief Register layout of a UART/USART peripheral.
 *
 * This struct matches the hardware layout for each USART on STM32F411RE.
 * Each register has a specific role in data transmission, control, and error handling.
 *
 * - SR:  Status register (flags like RXNE, TXE)
 * - DR:  Data register (read to receive, write to transmit)
 * - BRR: Baud rate register (mantissa + fraction for baud setup)
 * - CR1: Control register 1 (enables TX/RX, interrupts, parity)
 * - CR2: Control register 2 (stop bits, clock modes)
 * - CR3: Control register 3 (DMA, flow control, error settings)
 * - GTPR: Guard time and prescaler (rarely used; for smartcard mode)
 */
typedef struct {
    volatile uint32_t SR;    /**< Status Register: flags like TXE, RXNE, ORE, etc. */
    volatile uint32_t DR;    /**< Data Register: write to transmit, read to receive */
    volatile uint32_t BRR;   /**< Baud Rate Register: controls bit rate (mantissa/fraction) */
    volatile uint32_t CR1;   /**< Control Register 1: enable bits, parity, interrupts */
    volatile uint32_t CR2;   /**< Control Register 2: stop bits, LIN/clock modes */
    volatile uint32_t CR3;   /**< Control Register 3: flow control, DMA, error control */
    volatile uint32_t GTPR;  /**< Guard Time and Prescaler Register (for smartcard mode) */
} UART_TypeDef;

/**
 * @brief Enumeration of standard baud rates.
 *
 * Common values used in serial communication. These enums can be passed
 * to UART initialization functions to simplify configuration.
 */
typedef enum {
    UART_BAUD_300     = 300,     /**< 300 baud (slow, legacy devices) */
    UART_BAUD_9600    = 9600,    /**< 9600 baud (default for many modules) */
    UART_BAUD_19200   = 19200,   /**< 19200 baud */
    UART_BAUD_115200  = 115200   /**< 115200 baud (typical for debug/USB-serial) */
} baud_rate_t;

#endif // STM32F4_UART_H
