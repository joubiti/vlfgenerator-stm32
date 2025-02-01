#include "stm32g0xx.h"
#include "clock.h"
#include "led.h"
#include "uart.h"
#include <cstdint>

volatile std::int32_t j = 0;
heartbeatLed led;

int main(){
    Clock::initialize();
    led.initialize();
    
    while(1){
        led.toggle();
        Clock::delay_ms(1000);
    }
    
    return 0;
}