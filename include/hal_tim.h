#ifndef HAL_TIM_H
#define HAL_TIM_H
#include <stdint.h>
#include "stm32f4_tim.h"

void tim_1hz_init(TIM_TypeDef *timx, uint32_t clk_hz);

#endif //HAL_TIM_H