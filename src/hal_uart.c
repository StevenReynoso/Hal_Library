/*
 * UART - Universal Asynchronous Receiver/Transmitter
 * USART - Universal Synchronous/Asynchronous Receiver/Transmitter
 * --------------------------------------------------------
 * Baud Rates
 * • 300 bps: Very slow, often used for long-distance communication where bandwidth is limited
 * • 9,600 bps: A widely used default rate for many devices, including microcontrollers
 * • 19,200 bps: Faster, often used in more data-intensive applications
 * • 115,200 bps: High-speed communication, common in applications requiring quick data transfer
 * 
*/
#include <stdint.h>
#include "../hal_uart.h"

static void configure_baud(UART_TypeDef *uart, uint32_t periph_clk, baud_rate_t rate){
    uart->BRR = ((periph_clk + (rate/2U))/rate);
}

uint8_t uart_read(UART_TypeDef *uart) {
    while (!(uart->SR & USART_SR_RXNE)) {
        
    }

    return (uint8_t)(uart->DR & 0xFF);
}

static void uart_write(UART_TypeDef *uart , char data){
    while(!(uart->SR & USART_SR_TXE)){}
    uart->DR = data;
}

void uart_print(UART_TypeDef *uart, const char *msg){
    while(*msg){
        uart_write(uart, *msg++);
    }
}

void uart_init(UART_TypeDef *uart, uint32_t periph_clk, baud_rate_t baud){
    uart->CR1 &= ~USART_CR1_UE;

    configure_baud(uart, periph_clk, (uint32_t)baud);

    uart->CR1 &= ~(1 << 12);   // 8 data bits
    uart->CR2 &= ~(3 << 12);   // 1 stop bit
    uart->CR1 &= ~(1 << 10);   // No parity
    
    uart->CR1 |= USART_CR1_UE;
    uart->CR1 |= USART_CR1_TE | USART_CR1_RE;

}