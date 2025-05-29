#include <stdint.h>
#include "../hal_tim.h"
#include "../hal_rcc.h"

void tim_1hz_init(TIM_TypeDef *timx, uint32_t clk_hz){
    // do a check on bus enable?
    rcc_enable_tim(timx);
    // bus check depending on tim being used.
    //set prescaler value
    timx->PSC = 1600 - 1;

    // set auto reload value
    timx->ARR = (clk_hz / (timx->PSC + 1));

    // clear the counter
    timx->CNT = 0;

    timx->CR1 |= (1U << 0); 
}


