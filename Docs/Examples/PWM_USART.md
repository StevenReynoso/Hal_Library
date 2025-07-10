/**
 * @section example_pwm_basic Example: Basic PWM Output + UART Logging
 *
 * This example sets up TIM2 to generate a PWM signal on pin PA5 with a 50% duty cycle.
 * It also configures USART2 on PA2 to send debug messages over serial.
 * 
 * **Oscilloscope Test Tip**:
 * You can visualize the PWM waveform with an oscilloscope or logic analyzer:
 * - Connect PA5 (TIM2_CH1) to the **anode** of an LED.
 * - Connect a **220Ω resistor** between the LED cathode and **GND**.
 * - Also connect the oscilloscope **GND** to board GND.
 * - Probe **between PA5 and LED** to see the PWM waveform.
 *
 * **PWM Configuration**:
 * - Timer: TIM2 Channel 1
 * - Output Pin: PA5 (AF1)
 * - Frequency: 1 kHz  → Prescaler = 16000, ARR = 1000
 * - Duty Cycle: 50%   → CCR1 = 500
 *
 * **UART Configuration**:
 * - Peripheral: USART2
 * - TX Pin: PA2 (AF7)
 * - Baud Rate: 115200
 *
 * **Warning**: This example sends serial messages in a tight loop — it will spam!
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
 *     gpio_set_af(pa5_Tim.pin, 1);     // TIM2_CH1 on AF1
 *     gpio_set_af(uart_cfg.pin, 7);    // USART2_TX on AF7
 *
 *     tim_pwm_init(TIM2, 16000, 1000);        // PWM: 1 kHz
 *     tim_pwm_config_channel(TIM2, 1, 500);   // 50% duty
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
