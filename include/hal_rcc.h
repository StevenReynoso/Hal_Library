#ifndef HAL_RCC_H
#define HAL_RCC_H

#include "stm32f4_rcc.h"
#include "../hal_spi.h"
#include "../hal_tim.h"
#include "../hal_uart.h"

void rcc_enable(volatile uint32_t *reg, uint8_t bit_pos);
void rcc_enable_tim(TIM_TypeDef *timx);
void rcc_enable_gpio(uint16_t port_index);
void rcc_enable_uart(UART_TypeDef *uart);
void rcc_enable_spi(SPI_TypeDef * spix);
#endif //HAL_RCC_H