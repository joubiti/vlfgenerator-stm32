#include "stm32g0xx.h"
#include "led.h"
#include "mcal.h"
#include "uart.h"
#include "log.h"
#include <cstdint>


constexpr std::uint32_t MAIN_LOOP_FREQUENCY = UINT32_C(500);
heartbeatLed led;
UART uart1;
logging log_module(uart1);
std::uint32_t counter(0);

int main(){
    mcal::init();
    led.initialize();
    uart1.initialize(UART_1, 115200);
    
    while(1){
        counter ++;
        led.toggle();
        log_module.warning("Counter value: %d", counter);
        mcal::clock::delay(MAIN_LOOP_FREQUENCY);
    }
    
    return 0;
}