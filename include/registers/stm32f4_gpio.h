#ifndef STM32F4_GPIO_H
#define STM32F4_GPIO_H

#include <stdint.h>

#define GPIOA ((GPIO_TypeDef *) 0x40020000UL)
#define GPIOB ((GPIO_TypeDef *) 0x40020400UL)
#define GPIOC ((GPIO_TypeDef *) 0x40020800UL)
#define GPIOD ((GPIO_TypeDef *) 0x40020C00UL)
#define GPIOE ((GPIO_TypeDef *) 0x40021000UL)
#define GPIOF ((GPIO_TypeDef *) 0x40021400UL)
#define GPIOG ((GPIO_TypeDef *) 0x40021800UL)
#define GPIOH ((GPIO_TypeDef *) 0x40021C00UL)

#define PIN(port, pin) (((port - 'A') << 8) | (pin))
#define GET_PORT(p) (((p) >> 8) & 0xFF)
#define GET_PIN(p) ((p) & 0xFF)

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
} GPIO_TypeDef;

typedef enum{
    GPIO_MODE_INPUT       = 0x00,
    GPIO_MODE_OUTPUT      = 0x01,
    GPIO_MODE_ALTFUNC     = 0x02,
    GPIO_MODE_ANALOG      = 0x03,
} gpio_mode_t;

typedef enum{
    GPIO_OTYPE_PUSHPULL   = 0x00,
    GPIO_OTYPE_OPENDRAIN  = 0x01,
} gpio_type_t;

typedef enum{
    GPIO_SPEED_LOW        = 0x00,
    GPIO_SPEED_MEDIUM     = 0x01,
    GPIO_SPEED_FAST       = 0x02,
    GPIO_SPEED_HIGH       = 0x03,
} gpio_speed_t;

typedef enum{
    GPIO_NO_PULL          = 0x00,
    GPIO_PULL_UP          = 0x01,
    GPIO_PULL_DOWN        = 0x02,
} gpio_pupdr_t;


typedef struct{
    uint16_t pin;
    gpio_mode_t mode;
    gpio_type_t otype;
    gpio_speed_t speed;
    gpio_pupdr_t pull;
    
} gpio_config_t;

typedef enum {
    GPIO_PORT_A  = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G,
    GPIO_PORT_H
} gpio_port_t;

#endif //STM32F4_GPIO_H