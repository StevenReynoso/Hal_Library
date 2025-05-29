#include <stdint.h>
#include "../hal_spi.h"
#include "../hal_uart.h"

uint8_t spi_transfer(SPI_TypeDef *spix, uint8_t data){
    while(!(spix->SR & (1 << 1)));
    spix->DR = data;
    while(!(spix->SR & (1 << 0)));
    return spix->DR;
}

void spi_init(SPI_TypeDef *spix) {
    spix->CR1 = 0;           
    spix->CR1 |= (1 << 2);   // MSTR enable
    spix->CR1 |= (3 << 3);   // BR[2:0] = 011 = f_PCLK / 16 
    spix->CR1 |= (0 << 1);   // CPOL = 0
    spix->CR1 |= (0 << 0);   // CPHA = 0

    spix->CR1 |= (1 << 9);  // SSM = 1 (Software NSS management) ← ADD THIS
    spix->CR1 |= (1 << 8);  // SSI = 1 (Internal NSS high) ← ADD THIS


    spix->CR1 |= (1 << 6);   // SPE = SPI Enable
}