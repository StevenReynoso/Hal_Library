
#include <stdint.h>
#include "../hal_rcc.h"
#include "../hal_uart.h"


void rcc_enable_gpio(uint16_t port_index){
    RCC->AHB1ENR |= (1 << port_index);
}

void rcc_enable_uart(UART_TypeDef *uart) {
    if      (uart == USART1) RCC->APB2ENR |= (1 << 4);   // USART1 = bit 4 on APB2
    else if (uart == USART2) RCC->APB1ENR |= (1 << 17);  // USART2 = bit 17 on APB1
    else if (uart == USART3) RCC->APB1ENR |= (1 << 18);  // USART3 = bit 18 on APB1
    else if (uart == UART4)  RCC->APB1ENR |= (1 << 19);  // UART4  = bit 19 on APB1
    else if (uart == UART5)  RCC->APB1ENR |= (1 << 20);  // UART5  = bit 20 on APB1
    else if (uart == USART6) RCC->APB2ENR |= (1 << 5);   // USART6 = bit 5 on APB2
}
