#include "stm32g0xx.h"
#include "clock.h"
#include <cstdint>

volatile std::int32_t j = 0;


int main(){
    clock_initialize();

    while(1){
        j++;
        delay_ms(1000);
    }
    
    return 0;
}