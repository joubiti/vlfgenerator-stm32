#include "stm32g0xx.h"
#include "led.h"
#include "mcal.h"
#include "uart.h"
#include <cstdint>


constexpr std::uint32_t MAIN_LOOP_FREQUENCY = UINT32_C(500);
const std::uint8_t arr[4] = {0x3f, 0x4e, 0x11, 0x93};

heartbeatLed led;
UART uart2;

int main(){
    mcal::init();
    led.initialize();
    uart2.initialize(UART_2, 115200);
    
    while(1){
        led.toggle();
        uart2.write(arr, sizeof(arr));
        mcal::clock::delay(MAIN_LOOP_FREQUENCY);
    }
    
    return 0;
}