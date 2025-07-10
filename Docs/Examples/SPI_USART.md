/**
 * @file hal_tim.h
 * @brief Header for timer configuration functions (basic timer and PWM setup).
 *
 * This module provides APIs to configure STM32F4 timers for:
 * - 1Hz timebase (for polling or blinking)
 * - PWM output (for servo motors, LEDs, etc.)
 *
 * @author Steven Reynoso
 *
 * @section example_usage Example: Using TIM2 with SPI and USART
 *
 * @code
 * int main(void) {
 *     gpio_config_t uart_cfg = {
 *         .pin = PIN('A', 2),                   // USART2_TX
 *         .mode = GPIO_MODE_ALTFUNC,
 *         .otype = GPIO_OTYPE_PUSHPULL,
 *         .speed = GPIO_SPEED_HIGH,
 *         .pull = GPIO_NO_PULL
 *     };
 *
 *     gpio_config_t spi_sck =  { .pin = PIN('A', 5), ... };
 *     gpio_config_t spi_miso = { .pin = PIN('A', 6), ... };
 *     gpio_config_t spi_mosi = { .pin = PIN('A', 7), ... };
 *
 *     rcc_enable_gpio(GET_PORT(uart_cfg.pin));
 *     rcc_enable_uart(USART2);
 *     rcc_enable_spi(SPI1);
 *     rcc_enable_tim(TIM2);
 *
 *     systick_init(16000);
 *     gpio_init(uart_cfg);
 *     gpio_init(spi_sck);
 *     gpio_init(spi_miso);
 *     gpio_init(spi_mosi);
 *
 *     gpio_set_af(uart_cfg.pin, 7);     // USART2_TX
 *     gpio_set_af(spi_sck.pin, 5);      // SPI1_SCK
 *     gpio_set_af(spi_miso.pin, 5);     // SPI1_MISO
 *     gpio_set_af(spi_mosi.pin, 5);     // SPI1_MOSI
 *
 *     uart_init(USART2, 16000000, UART_BAUD_115200);
 *     spi_init(SPI1);
 *     tim_1hz_init(TIM2, 16000000);     // Overflow every 1 sec
 *
 *     uint8_t tx = 0xAB;
 *
 *     while (1) {
 *         if (TIM2->SR & (1 << 0)) {    // Update interrupt flag
 *             TIM2->SR &= ~(1 << 0);    // Clear flag
 *
 *             uart_print(USART2, "TIM2 Fired\r\n");
 *             uint8_t rx = spi_transfer(SPI1, tx);
 *
 *             if (rx == tx) {
 *                 uart_print(USART2, "SPI Loopback SUCCESS!\r\n");
 *             } else {
 *                 uart_print(USART2, "SPI FAIL\r\n");
 *             }
 *         }
 *     }
 * }
 * @endcode
 *
 * This shows how to:
 * - Set up USART2 on PA2
 * - Set up SPI1 (PA5/6/7) for loopback test
 * - Use TIM2 to create a polling interval (1Hz)
 * - Do SPI transfer every second, and print over UART
 */
