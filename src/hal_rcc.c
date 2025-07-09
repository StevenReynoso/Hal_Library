/**
 * @file hal_rcc.c
 * @brief RCC peripheral clock enable implementation for STM32F4 series.
 *
 * Contains implementation of high-level RCC utility functions for enabling
 * peripheral clocks (GPIO, UART, SPI, TIM) by writing to AHB and APB RCC registers.
 */


#include <stdint.h>
#include "hal_spi.h"
#include "hal_tim.h"
#include "hal_rcc.h"
#include "hal_uart.h"

/**
 * @brief Enables the clock for a GPIO port.
 *
 * @param port_index Index of GPIO port (0 = GPIOA, 1 = GPIOB, etc.).
 */
void rcc_enable_gpio(uint16_t port_index){
    RCC->AHB1ENR |= (1 << port_index);
}

/**
 * @brief Generic RCC bus register enable function.
 *
 * Sets the given bit in the provided RCC register.
 *
 * @param reg Pointer to RCC register (e.g., &RCC->APB1ENR).
 * @param bit_pos Bit position to enable.
 */
void rcc_enable_bus(volatile uint32_t *reg, uint8_t bit_pos){
    *reg |= (1U << bit_pos);    
}

/**
 * @brief Enables the clock for a specific UART peripheral.
 *
 * Determines the APB bus and appropriate bit position for the given UART.
 *
 * @param uart Pointer to UART peripheral base (e.g., USART1, USART2).
 */
void rcc_enable_uart(UART_TypeDef *uart) {
    if      (uart == USART1) RCC->APB2ENR |= (1 << 4);   // USART1 = bit 4 on APB2
    else if (uart == USART2) RCC->APB1ENR |= (1 << 17);  // USART2 = bit 17 on APB1
    else if (uart == USART3) RCC->APB1ENR |= (1 << 18);  // USART3 = bit 18 on APB1
    else if (uart == UART4)  RCC->APB1ENR |= (1 << 19);  // UART4  = bit 19 on APB1
    else if (uart == UART5)  RCC->APB1ENR |= (1 << 20);  // UART5  = bit 20 on APB1
    else if (uart == USART6) RCC->APB2ENR |= (1 << 5);   // USART6 = bit 5 on APB2
}


/**
 * @brief Enables the clock for a TIM peripheral.
 *
 * Determines whether the timer is on APB1 or APB2 and enables its clock accordingly.
 *
 * @param timx Pointer to TIM peripheral (e.g., TIM2, TIM3, TIM1).
 */
void rcc_enable_tim(TIM_TypeDef *timx){
    if (timx == TIM1)      RCC->APB2ENR |= (1U << 11); // TIM1EN
    else if (timx == TIM8) RCC->APB2ENR |= (1U << 13); // TIM8EN
    else if (timx == TIM2) RCC->APB1ENR |= (1U << 0);  // TIM2EN
    else if (timx == TIM3) RCC->APB1ENR |= (1U << 1);  // TIM3EN
    else if (timx == TIM4) RCC->APB1ENR |= (1U << 2);  // TIM4EN
    else if (timx == TIM5) RCC->APB1ENR |= (1U << 3);  // TIM5EN
    else if (timx == TIM6) RCC->APB1ENR |= (1U << 4);  // TIM6EN
    else if (timx == TIM7) RCC->APB1ENR |= (1U << 5);  // TIM7EN
    else if (timx == TIM12) RCC->APB1ENR |= (1U << 6); // TIM12EN
    else if (timx == TIM13) RCC->APB1ENR |= (1U << 7); // TIM13EN
    else if (timx == TIM14) RCC->APB1ENR |= (1U << 8); // TIM14EN
    else return; 
}

/**
 * @brief Enables the clock for a SPI peripheral.
 *
 * Identifies the correct RCC register and bit to enable SPI peripheral clocks.
 *
 * @param spix Pointer to SPI peripheral (e.g., SPI1, SPI2, SPI3).
 */
void rcc_enable_spi(SPI_TypeDef * spix){ 
    if (spix == SPI1) RCC->APB2ENR |= (1 << 12);        // enables SPI1EN
    else if (spix == SPI2) RCC->APB1ENR |= (1 << 14);   // enables SPI2EN
    else if (spix == SPI3) RCC->APB1ENR |= (1 << 15);   // enables SPI3EN
    else if (spix == SPI4) RCC->APB2ENR |= (1 << 13);   // enables SPI4EN
}