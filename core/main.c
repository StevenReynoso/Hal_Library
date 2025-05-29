#include "../hal_types.h"


int main(void){
    gpio_config_t spi_sck_cfg = {
        .pin = PIN('A', 5),
        .mode = GPIO_MODE_ALTFUNC,
        .otype = GPIO_OTYPE_PUSHPULL,
        .speed = GPIO_SPEED_HIGH,
        .pull = GPIO_NO_PULL,
    };

    gpio_config_t spi_miso_cfg = {
        .pin = PIN('A', 6),
        .mode = GPIO_MODE_ALTFUNC,
        .otype = GPIO_OTYPE_PUSHPULL,
        .speed = GPIO_SPEED_HIGH,
        .pull = GPIO_NO_PULL,
    };

    gpio_config_t spi_mosi_cfg = {
        .pin = PIN('A', 7),
        .mode = GPIO_MODE_ALTFUNC,
        .otype = GPIO_OTYPE_PUSHPULL,
        .speed = GPIO_SPEED_HIGH,
        .pull = GPIO_NO_PULL,
    };

    gpio_config_t uart_cfg ={   //pa2 is uart2_tx 
        .pin = PIN('A', 2),
        .mode = GPIO_MODE_ALTFUNC,
        .otype = GPIO_OTYPE_PUSHPULL,
        .speed = GPIO_SPEED_HIGH,
        .pull = GPIO_NO_PULL
    };

    rcc_enable_gpio(GET_PORT(spi_sck_cfg.pin));
    rcc_enable_uart(USART2);
    rcc_enable_tim(TIM2);
    rcc_enable_spi(SPI1);
    systick_init(16000);
    spi_init(SPI1);
    gpio_init(spi_sck_cfg);
    gpio_init(spi_miso_cfg);
    gpio_init(spi_mosi_cfg);
    gpio_init(uart_cfg);
    uart_init(USART2, 16000000, UART_BAUD_115200);
    gpio_set_af(spi_sck_cfg.pin,  5);
    gpio_set_af(spi_miso_cfg.pin, 5);
    gpio_set_af(spi_mosi_cfg.pin, 5);
    gpio_set_af(uart_cfg.pin, 7);
    tim_1hz_init(TIM2, 16000000);
    

    uint8_t tx = 0xAB;
    uart_print(USART2, "UART INITIALIZED!\r\n");

    while(1){
        
        if(TIM2->SR & (1 << 0)){
            uart_print(USART2, "TIM2 ACTIVATED\r\n");
            TIM2->SR &= ~(1 << 0);
            uart_print(USART2, "b4 spi_transfer\r\n");
            uint8_t rx = spi_transfer(SPI1, tx);        // stuck here for some reason


            if(rx == tx){
                uart_print(USART2, "SPI loopback SUCCESS!!\r\n");
            }else{
                uart_print(USART2, "It Failed!!!");
            }

        }
    }
}