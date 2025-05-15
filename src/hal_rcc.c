
#include <stdint.h>
#include "../hal_rcc.h"


void rcc_enable_gpio(uint16_t port_index){
    RCC->AHB1ENR |= (1 << port_index);
}