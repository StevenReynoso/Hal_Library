/**
 * @file hal_spi.h
 * @brief High-level SPI interface for STM32F411RE using register-level access.
 *
 * This header provides user-facing functions for initializing SPI peripherals
 * and transmitting/receiving data over SPI. It uses direct register access,
 * and is intended to be lightweight and beginner-friendly.
 */

#ifndef HAL_SPI_H
#define HAL_SPI_H

#include <stdint.h>
#include "stm32f4_spi.h"

/**
 * @brief Sends and receives one byte over SPI.
 *
 * This function transmits a byte of data to the connected SPI device and waits
 * until a response is received. SPI is full-duplex, so reading happens while writing.
 *
 * @param spix Pointer to the SPI peripheral (e.g., `SPI1`, `SPI2`, etc.)
 * @param data The byte to transmit.
 * @return uint8_t The byte received from the SPI slave during transmission.
 *
 * @note This function blocks until transmission and reception are complete.
 */
uint8_t spi_transfer(SPI_TypeDef *spix, uint8_t data);

/**
 * @brief Initializes the given SPI peripheral in master mode.
 *
 * This function sets up the SPI peripheral with standard configuration:
 * - Master mode
 * - 8-bit data frame
 * - Software slave select (NSS)
 * - Clock polarity = 0, phase = 0 (Mode 0)
 * - MSB first
 * - Baud rate prescaler = /16 (adjust as needed)
 *
 * @param spix Pointer to the SPI peripheral to initialize (e.g., `SPI1`, `SPI2`, etc.)
 *
 * @note GPIO pins for SCK, MISO, and MOSI must be configured before calling this function.
 */
void spi_init(SPI_TypeDef *spix);

#endif // HAL_SPI_H
