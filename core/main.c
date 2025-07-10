/**
 * @file main.c
 * @brief Entry point for STM32F411RE user application.
 *
 * This is the starting point for user code using the custom bare-metal HAL.
 * 
 * You can include your application logic inside the `main()` function.
 * Peripherals such as GPIO, UART, SPI, timers, and SysTick can be initialized
 * using the provided HAL functions. See each module’s documentation for usage examples.
 *
 * @note This file is intentionally left empty to let you build your application from scratch.
 * You can refer to `main_template.c` or peripheral test files for working examples.
 *
 * @example
 * @code
 * int main(void) {
 *     // Your initialization and loop code here
 *     while (1) {
 *         // Application loop
 *     }
 * }
 * @endcode
 */


#include "../hal_types.h"


int main(void){
    gpio_config_t pa5_Tim = {
        .pin  = PIN('A', 5),
        .mode = GPIO_MODE_ALTFUNC,
        .otype= GPIO_OTYPE_PUSHPULL,
        .speed= GPIO_SPEED_HIGH,
        .pull = GPIO_NO_PULL
    };

    gpio_config_t uart_cfg ={   //pa2 is uart2_tx 
        .pin = PIN('A', 2),
        .mode = GPIO_MODE_ALTFUNC,
        .otype = GPIO_OTYPE_PUSHPULL,
        .speed = GPIO_SPEED_HIGH,
        .pull = GPIO_NO_PULL
    };



    rcc_enable_gpio(GET_PORT(pa5_Tim.pin));
    rcc_enable_uart(USART2);
    rcc_enable_tim(TIM2);


    gpio_init(uart_cfg);
    gpio_init(pa5_Tim);
    gpio_set_af(pa5_Tim.pin, 1);
    gpio_set_af(uart_cfg.pin, 7);

    tim_pwm_init(TIM2, 16000, 1000);
    tim_pwm_config_channel(TIM2, 1, 500);
    tim_pwm_start(TIM2);

    uart_init(USART2, 16000000, UART_BAUD_115200);
    uart_print(USART2, "UART INITIALIZED!\r\n");

    while(1){
        uart_print(USART2, "WE still going\r\n");

    }

}