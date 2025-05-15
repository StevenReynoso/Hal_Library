#include "../hal_types.h"
#include "../hal_gpio.h"
#include "../hal_rcc.h"


#define LED_OUT PIN('A', 5)
#define LED_IN PIN('A', 6)

int main(void){
    rcc_enable_gpio(GET_PORT(LED_OUT));
    gpio_mode(LED_OUT, GPIO_MODE_OUTPUT);
    gpio_mode(LED_IN, GPIO_MODE_INPUT);

    while(1){
        gpio_write(LED_OUT, 1);

        for (volatile uint32_t i = 0; i < 800000; i++)
        {
            __asm__ volatile ("NOP");
        }

        if(!gpio_read(LED_IN)){
            while(1); // trap
        }
        
        gpio_write(LED_OUT, 0);

        for (volatile uint32_t i = 0; i < 800000; i++)
        {
            __asm__ volatile ("NOP");
        }


        if(gpio_read(LED_IN)){
            while(1); // trap
        }
        

    }


    return 0;
}