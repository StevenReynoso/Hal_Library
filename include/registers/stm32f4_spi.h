/**
 * @file stm32f4_spi.h
 * @brief Register definition for SPI peripheral on STM32F4 series.
 *
 * This header defines the memory-mapped base addresses and register layout for
 * SPI1–SPI4 peripherals on STM32F4 devices. SPI is used for full-duplex serial
 * communication with external devices like sensors, displays, or memory chips.
 *
 * The layout is based on RM0390 Reference Manual.
 */

#ifndef STM32F4_SPI_H
#define STM32F4_SPI_H

#include <stdint.h>

/// @name SPI Base Addresses
/// STM32F4 SPI peripherals are on APB1 or APB2 buses.
/// @{
#define SPI1 ((SPI_TypeDef *) 0x40013000UL)  /**< SPI1 base address (APB2) */
#define SPI2 ((SPI_TypeDef *) 0x40003800UL)  /**< SPI2 base address (APB1) */
#define SPI3 ((SPI_TypeDef *) 0x40003C00UL)  /**< SPI3 base address (APB1) */
#define SPI4 ((SPI_TypeDef *) 0x40013400UL)  /**< SPI4 base address (APB2) */
/// @}

/**
 * @brief Register map of the SPI peripheral.
 *
 * Each SPI peripheral (SPI1–SPI4) exposes this register layout. 
 * Used to configure control, manage data transmission, and check status flags.
 */
typedef struct 
{
    volatile uint32_t CR1;      /**< Control Register 1  
                                 *  - Clock phase (CPHA), polarity (CPOL)  
                                 *  - Master/slave mode  
                                 *  - Baud rate prescaler  
                                 *  - Data frame format (8/16-bit)  
                                 *  - Software slave management  
                                 */
    volatile uint32_t CR2;      /**< Control Register 2  
                                 *  - Interrupt enables  
                                 *  - TX/RX buffer DMA enable  
                                 *  - NSS output enable  
                                 */
    volatile uint32_t SR;       /**< Status Register  
                                 *  - TXE (transmit buffer empty)  
                                 *  - RXNE (receive buffer not empty)  
                                 *  - BSY (busy flag)  
                                 *  - Overrun, CRC error  
                                 */
    volatile uint32_t DR;       /**< Data Register  
                                 *  - Write to transmit  
                                 *  - Read to receive  
                                 */
    volatile uint32_t CRCPR;    /**< CRC Polynomial Register  
                                 *  - Used if CRC is enabled (optional)  
                                 */
    volatile uint32_t RXCRCR;   /**< RX CRC Register (read-only)  
                                 *  - Holds CRC for last received word  
                                 */
    volatile uint32_t TXCRCR;   /**< TX CRC Register (read-only)  
                                 *  - Holds CRC for last transmitted word  
                                 */
    volatile uint32_t I2SCFGR;  /**< I2S Configuration Register  
                                 *  - SPI peripheral can operate in I2S mode  
                                 *  - Controls audio-specific configuration  
                                 */
    volatile uint32_t I2SPR;    /**< I2S Prescaler Register  
                                 *  - Prescaler for audio sampling rate  
                                 */
} SPI_TypeDef;

#endif // STM32F4_SPI_H
