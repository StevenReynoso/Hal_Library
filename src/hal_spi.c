/**
 * @file hal_spi.c
 * @brief Implementation of SPI transmit and initialization functions for STM32F411RE.
 *
 * Provides low-level routines for sending and receiving SPI data and setting up
 * SPI peripherals in master mode using direct register access. Built to match
 * STM32F411RE peripheral capabilities.
 */

#include <stdint.h>
#include "hal_spi.h"
#include "hal_uart.h"

/**
 * @brief Transmits a single byte over SPI and receives a byte in return.
 *
 * This function blocks until the transmit buffer is empty, writes the outgoing byte,
 * then waits for the receive buffer to be full. The SPI peripheral always receives 
 * a byte while sending one due to its full-duplex nature.
 *
 * @param spix Pointer to SPI peripheral (e.g., `SPI1`, `SPI2`, etc.)
 * @param data Byte to transmit.
 * @return uint8_t Byte received from SPI slave device.
 */
uint8_t spi_transfer(SPI_TypeDef *spix, uint8_t data){
    // Wait until transmit buffer is empty (TXE = 1)
    while (!(spix->SR & (1 << 1)));

    // Write data to the data register to start transmission
    spix->DR = data;

    // Wait until receive buffer is full (RXNE = 1)
    while (!(spix->SR & (1 << 0)));

    // Read and return received data
    return spix->DR;
}

/**
 * @brief Initializes the SPI peripheral in master mode with default settings.
 *
 * This function sets up the SPI peripheral for master-mode operation with:
 * - Clock polarity = 0, phase = 0 (Mode 0)
 * - Baud rate = PCLK / 16
 * - Software slave select enabled
 * - 8-bit data frame, MSB first
 *
 * NSS (chip select) is controlled via software using SSM/SSI, so physical NSS pin is not required.
 *
 * @param spix Pointer to SPI peripheral to configure (e.g., `SPI1`, `SPI2`, etc.)
 *
 * @note Make sure GPIO pins for SCK, MOSI, and MISO are configured in alternate function mode
 *       before calling this function.
 */
void spi_init(SPI_TypeDef *spix) {
    spix->CR1 = 0;            /**< Clear previous configuration */

    spix->CR1 |= (1 << 2);    /**< MSTR = 1 → Master mode */
    spix->CR1 |= (3 << 3);    /**< BR[2:0] = 011 → Baud rate = f_PCLK / 16 */
    spix->CR1 |= (0 << 1);    /**< CPOL = 0 → Clock polarity low when idle */
    spix->CR1 |= (0 << 0);    /**< CPHA = 0 → Capture on first clock edge */

    spix->CR1 |= (1 << 9);    /**< SSM = 1 → Software slave select management */
    spix->CR1 |= (1 << 8);    /**< SSI = 1 → Internal NSS signal high */

    spix->CR1 |= (1 << 6);    /**< SPE = 1 → SPI peripheral enabled */
}
