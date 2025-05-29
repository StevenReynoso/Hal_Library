#ifndef HAL_TYPES_H
#define HAL_TYPES_H

#include <stdint.h>
#include "hal_gpio.h"
#include "hal_rcc.h"
#include "hal_systick.h"
#include "hal_tim.h"
#include "hal_uart.h"
#include "hal_spi.h"

// booleans
typedef enum{
    FALSE = 0,
    TRUE = 1
} BOOL;


#endif // HAL_TYPES_H