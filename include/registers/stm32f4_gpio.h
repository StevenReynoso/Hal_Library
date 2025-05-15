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
    GPIO_MODE_INPUT     = 0x00,
    GPIO_MODE_OUTPUT    = 0x01,
    GPIO_MODE_ALTFUNC   = 0x02,
    GPIO_MODE_ANALOG    = 0x03,
} gpio_mode_t;



#endif //STM32F4_GPIO_H