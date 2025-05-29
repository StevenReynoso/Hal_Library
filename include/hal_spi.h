#ifndef HAL_SPI_H
#define HAL_SPI_H
#include <stdint.h>
#include "stm32f4_spi.h"

uint8_t spi_transfer(SPI_TypeDef *spix, uint8_t data);
void spi_init(SPI_TypeDef *spix);
#endif // HAL_SPI_H