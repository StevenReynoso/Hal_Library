#ifndef HAL_RCC_H
#define HAL_RCC_H

#include "stm32f4_rcc.h"
#include "../hal_uart.h"


void rcc_enable_gpio(uint16_t port_index);
void rcc_enable_uart(UART_TypeDef *uart);
#endif //HAL_RCC_H