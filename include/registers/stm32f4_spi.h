#ifndef STM32F4_SPI_H
#define STM32F4_SPI_H
#include <stdint.h>

//APB2
#define SPI4 ((SPI_TypeDef *) 0x40013400)
#define SPI1 ((SPI_TypeDef *) 0x40013000)

//APB1
#define SPI3 ((SPI_TypeDef *) 0x40003C00)
#define SPI2 ((SPI_TypeDef *) 0x40003800)


typedef struct 
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
    volatile uint32_t I2SCFGR;
    volatile uint32_t I2SPR;

} SPI_TypeDef;


#endif //STM32F4_SPI_H