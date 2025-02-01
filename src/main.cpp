#include "stm32g0xx.h"
#include "clock.h"
#include "led.h"
#include "uart.h"
#include <cstdint>

volatile std::int32_t j = 0;
const std::uint8_t arr[4] = {0x3f, 0x4e, 0x11, 0x93};
heartbeatLed led;
UART uart1;

int main(){
    Clock::initialize();
    led.initialize();
    uart1.initialize(UART_1, BAUDRATE_115200);
    
    while(1){
        led.toggle();
        uart1.write(arr, sizeof(arr));
        Clock::delay_ms(1000);
    }
    
    return 0;
}