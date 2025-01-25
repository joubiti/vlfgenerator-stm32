#include "stm32g0xx.h"
#include "clock.h"
#include <cstdint>

volatile std::int16_t i = 0;


int main(){
    clock_initialize();

    for(volatile uint32_t j = 0; j < 3256023; j++){
        i += 3;
    }
    while(1);
    
    return 0;
}