#include "../hal_gpio.h"
#include <stdint.h>

static inline GPIO_TypeDef *get_gpio_port(uint8_t port_index){
    return (GPIO_TypeDef *)(GPIOA + (0x400 * port_index));
}

void gpio_mode(uint16_t gpio_pin, gpio_mode_t mode){
    uint8_t port_index = GET_PORT(gpio_pin);
    uint8_t pin_num = GET_PIN(gpio_pin);

    GPIO_TypeDef *port = get_gpio_port(port_index);

    port->MODER &= ~(1 << (2 * pin_num));
    port->MODER |=  ((mode & 0x3U) << (2 * pin_num));

}

void gpio_write(uint16_t gpio_pin, uint8_t state){
    uint8_t port_index = GET_PORT(gpio_pin);
    uint8_t pin_num = GET_PIN(gpio_pin);

    GPIO_TypeDef *port = get_gpio_port(port_index);

    if(state){
        port->BSRR = (1 << pin_num);            // bsrr state = 1, is set
    }else{
        port->BSRR = (1 << (pin_num + 16));        // bsrr state = 0, is reset
    }
    
}

int gpio_read(uint16_t gpio_pin){
    uint8_t port_index = GET_PORT(gpio_pin);
    uint8_t pin_num = GET_PIN(gpio_pin);

    GPIO_TypeDef *port = get_gpio_port(port_index);

    return (port->IDR & (1 << pin_num));

}