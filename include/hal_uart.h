#ifndef HAL_UART_H
#define HAL_UART_H

#include "stm32f4_uart.h"

//void configure_baud(UART_TypeDef *uart, uint32_t periph_clk, baud_rate_t rate);
uint8_t uart_read(UART_TypeDef *uart);
void uart_print(UART_TypeDef *uart, const char *msg);
void uart_init(UART_TypeDef *uart, uint32_t periph_clk, baud_rate_t baud);
#endif //HAL_UART_H