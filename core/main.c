#include "../hal_systick.h"
#include "../hal_types.h"
#include "../hal_gpio.h"
#include "../hal_rcc.h"
#include "../hal_uart.h"

int main(void){
    gpio_config_t led_cfg = {
        .pin = PIN('A', 5),
        .mode = GPIO_MODE_OUTPUT,
        .otype = GPIO_OTYPE_PUSHPULL,
        .speed = GPIO_SPEED_FAST,
        .pull = GPIO_NO_PULL,
    };

    gpio_config_t uart_cfg ={   //pa2 is uart2_tx 
        .pin = PIN('A', 2),
        .mode = GPIO_MODE_ALTFUNC,
        .otype = GPIO_OTYPE_PUSHPULL,
        .speed = GPIO_SPEED_HIGH,
        .pull = GPIO_NO_PULL
    };
    rcc_enable_gpio(GET_PORT(led_cfg.pin));
    rcc_enable_uart(USART2);
    gpio_init(led_cfg);
    gpio_init(uart_cfg);
    uart_init(USART2, 16000000, UART_BAUD_115200);
    gpio_set_af(uart_cfg.pin, 7);

    uart_print(USART2, "UART INITIALIZED!\r\n");
    while(1){

        gpio_write(led_cfg.pin, 1);

        uart_print(USART2, "UART INITIALIZED!\r\n");
        for (volatile uint32_t i = 0; i < 800000; i++)
        {
            __asm__ volatile ("NOP");
        }

        gpio_write(led_cfg.pin, 0);

        for (volatile uint32_t i = 0; i < 800000; i++)
        {
            __asm__ volatile ("NOP");
        }
    }
}