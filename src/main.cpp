#include "stm32g0xx.h"
#include "clock.h"
#include <cstdint>

volatile std::int32_t j = 0;


int main(){
    Clock::initialize();

    while(1){
        j++;
        Clock::delay_ms(1000);
    }
    
    return 0;
}