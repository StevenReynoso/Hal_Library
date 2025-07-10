/**
 * @section example_pwm_basic Example: Basic PWM Output + UART Logging
 *
 * This example sets up TIM2 to generate a PWM signal on pin PA5 with a 50% duty cycle.
 * Simultaneously, USART2 (on PA2) is used to log data to a serial terminal.
 *
 * PWM Settings:
 * - TIM2 channel 1 (PA5)
 * - Frequency: 1 kHz (prescaler 16,000, ARR 1000)
 * - Duty cycle: 50% (CCR1 = 500)
 *
 * UART Settings:
 * - USART2 TX on PA2 (Alternate Function 7)
 * - Baud Rate: 115200
 *
 * @code
 * int main(void){
 *     gpio_config_t pa5_Tim = {
 *         .pin  = PIN('A', 5),
 *         .mode = GPIO_MODE_ALTFUNC,
 *         .otype= GPIO_OTYPE_PUSHPULL,
 *         .speed= GPIO_SPEED_HIGH,
 *         .pull = GPIO_NO_PULL
 *     };
 *
 *     gpio_config_t uart_cfg = {
 *         .pin = PIN('A', 2),
 *         .mode = GPIO_MODE_ALTFUNC,
 *         .otype = GPIO_OTYPE_PUSHPULL,
 *         .speed = GPIO_SPEED_HIGH,
 *         .pull = GPIO_NO_PULL
 *     };
 *
 *     rcc_enable_gpio(GET_PORT(pa5_Tim.pin));
 *     rcc_enable_uart(USART2);
 *     rcc_enable_tim(TIM2);
 *
 *     gpio_init(uart_cfg);
 *     gpio_init(pa5_Tim);
 *     gpio_set_af(pa5_Tim.pin, 1); // AF1 for TIM2_CH1
 *     gpio_set_af(uart_cfg.pin, 7); // AF7 for USART2_TX
 *
 *     tim_pwm_init(TIM2, 16000, 1000);   // 1 kHz PWM
 *     tim_pwm_config_channel(TIM2, 1, 500); // 50% duty cycle
 *     tim_pwm_start(TIM2);
 *
 *     uart_init(USART2, 16000000, UART_BAUD_115200);
 *     uart_print(USART2, "UART INITIALIZED!\r\n");
 *
 *     while(1){
 *         uart_print(USART2, "WE still going\r\n");
 *     }
 * }
 * @endcode
 */
