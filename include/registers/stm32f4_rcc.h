/**
 * @file stm32f4_rcc.h
 * @brief RCC (Reset and Clock Control) register map for STM32F4 series.
 *
 * Defines the base address and register layout of the RCC peripheral, used for configuring
 * clocks, enabling peripheral buses, and managing low-power/reset states.
 *
 * This is a low-level, direct-register header with no runtime logic.
 */

#ifndef STM32F4_RCC_H
#define STM32F4_RCC_H
#include <stdint.h>

/**
 * @brief RCC base address
 */
#define RCC ((RCC_TypeDef *) 0x40023800UL)

/**
 * @brief RCC register layout as defined in STM32F4 reference manual (RM0090).
 */
typedef struct {
    volatile uint32_t CR;             /**< Clock control register */
    volatile uint32_t PLLCFGR;        /**< PLL configuration register */
    volatile uint32_t CFGR;           /**< Clock configuration register */
    volatile uint32_t CIR;            /**< Clock interrupt register */
    volatile uint32_t AHB1RSTR;       /**< AHB1 peripheral reset register */
    volatile uint32_t AHB2RSTR;       /**< AHB2 peripheral reset register */
    volatile uint32_t AHB3RSTR;       /**< AHB3 peripheral reset register */
    uint32_t RESERVED0;               /**< Reserved (0x1C) */
    volatile uint32_t APB1RSTR;       /**< APB1 peripheral reset register */
    volatile uint32_t APB2RSTR;       /**< APB2 peripheral reset register */
    uint32_t RESERVED1[2];            /**< Reserved (0x28–0x2C) */
    volatile uint32_t AHB1ENR;        /**< AHB1 peripheral clock enable register */
    volatile uint32_t AHB2ENR;        /**< AHB2 peripheral clock enable register */
    volatile uint32_t AHB3ENR;        /**< AHB3 peripheral clock enable register */
    uint32_t RESERVED2;               /**< Reserved (0x3C) */
    volatile uint32_t APB1ENR;        /**< APB1 peripheral clock enable register */
    volatile uint32_t APB2ENR;        /**< APB2 peripheral clock enable register */
    uint32_t RESERVED3[2];            /**< Reserved (0x48–0x4C) */
    volatile uint32_t AHB1LPENR;      /**< AHB1 low power enable register */
    volatile uint32_t AHB2LPENR;      /**< AHB2 low power enable register */
    volatile uint32_t AHB3LPENR;      /**< AHB3 low power enable register */
    uint32_t RESERVED4;               /**< Reserved (0x5C) */
    volatile uint32_t APB1LPENR;      /**< APB1 low power enable register */
    volatile uint32_t APB2LPENR;      /**< APB2 low power enable register */
    uint32_t RESERVED5[2];            /**< Reserved (0x68–0x6C) */
    volatile uint32_t BDCR;           /**< Backup domain control register */
    volatile uint32_t CSR;            /**< Control/status register */
    uint32_t RESERVED6[2];            /**< Reserved (0x78–0x7C) */
    volatile uint32_t SSCGR;          /**< Spread spectrum clock generation register */
    volatile uint32_t PLLI2SCFGR;     /**< PLLI2S configuration register */
    volatile uint32_t PLLSAICFGR;     /**< PLLSAI configuration register */
    volatile uint32_t DCKCFGR;        /**< Dedicated clocks configuration register */
    volatile uint32_t CKGATENR;       /**< Clocks gated enable register */
    volatile uint32_t DCKCFGR2;       /**< Dedicated clocks configuration register 2 */
} RCC_TypeDef;

#endif // STM32F4_RCC_H