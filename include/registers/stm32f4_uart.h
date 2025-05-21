/*
 * UART
 *---------------------------
 * USe SR    : Status Register          -for TXE, RXNE, ect  
 * Use Dr    : Data Reister             -for writing to send, read to recieve
 * Use Brr   : Baud Rate Register       -for setting baud rate, mantissa + fraction
 * Use CR1   : Control Register         -for enabling USART, TX/RX interrupts
 * Use CR2   : Control Register 2       -for Stop bits, LIN mode
 * USE CR3   : Control Register 3       -for Flow control, DMA, error handling
 * use GTPR  : Guard Time & Prescaler   -for smartcards, not really touched
*/

#ifndef STM32F4_UART_H
#define STM32F4_UART_H

#include <stdint.h>

// APB2
#define USART1 ((UART_TypeDef *) 0x40011000)
#define USART6 ((UART_TypeDef *) 0x40011400)

// APB1 
#define USART2 ((UART_TypeDef *) 0x40004400)
#define USART3 ((UART_TypeDef *) 0x40004800)
#define UART4  ((UART_TypeDef *) 0x40004C00)
#define UART5  ((UART_TypeDef *) 0x40005000)

#define USART_CR1_TE   (1 << 3)  // Transmitter enable
#define USART_CR1_RE   (1 << 2)  // Receiver enable
#define USART_CR1_UE   (1 << 13) // USART enable
#define USART_SR_TXE   (1 << 7)
#define USART_SR_RXNE  (1 << 5)

typedef struct{
    volatile uint32_t SR;       //0x00
    volatile uint32_t DR;       //0x04
    volatile uint32_t BRR;      //0x08
    volatile uint32_t CR1;      //0x0C
    volatile uint32_t CR2;      //0x10
    volatile uint32_t CR3;      //0x14
    volatile uint32_t GTPR;     //0x18
}UART_TypeDef;

typedef enum{
    UART_BAUD_300       = 300,
    UART_BAUD_9600      = 9600,
    UART_BAUD_19200     = 19200,
    UART_BAUD_115200    = 115200,
}baud_rate_t;

#endif //STM32F4_UART_H