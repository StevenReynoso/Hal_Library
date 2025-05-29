#include "../hal_gpio.h"
#include <stdint.h>

static inline GPIO_TypeDef *get_gpio_port(uint8_t port_index) {
    static GPIO_TypeDef *const ports[] = {
        GPIOA, GPIOB, GPIOC, GPIOD,
        GPIOE, GPIOF, GPIOG, GPIOH
    };

    if (port_index > 7) return 0; // Defensive programming
    return ports[port_index];
}

void gpio_init(gpio_config_t cfg){
    uint8_t port_index = GET_PORT(cfg.pin);
    uint8_t pin_num = GET_PIN(cfg.pin);
    
    GPIO_TypeDef *port = get_gpio_port(port_index);

    port->MODER   &= ~(0x03 << (pin_num * 2));
    port->OTYPER  &= ~(1 << pin_num);
    port->OSPEEDR &= ~(0x03 << (pin_num * 2));
    port->PUPDR   &= ~(0x03 << (pin_num * 2));
    
    port->MODER   |= ((cfg.mode & 0x03) << (pin_num * 2));
    port->OTYPER  |= ((cfg.otype & 0x01) << pin_num);
    port->OSPEEDR |= ((cfg.speed & 0x03) << (pin_num * 2));
    port->PUPDR   |= ((cfg.pull & 0x03) << (pin_num * 2));


}

void gpio_set_af(uint16_t pin, uint8_t af){
    uint8_t port_index = GET_PORT(pin);
    uint8_t pin_num = GET_PIN(pin);

    GPIO_TypeDef *port = get_gpio_port(port_index);

    if (pin_num <= 7){
        port->AFRL &= ~(0xF << (4 * pin_num));
        port->AFRL |= (af << (4 * pin_num));
    }else {
        port->AFRH &= ~(0xF << (4 * (pin_num - 8)));
        port->AFRH |= (af << (4 * (pin_num - 8)));
    }

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