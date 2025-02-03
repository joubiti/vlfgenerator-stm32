#include "stm32g0xx.h"
#include "led.h"
#include "mcal.h"
#include "uart.h"
#include <cstdint>


constexpr std::uint32_t MAIN_LOOP_FREQUENCY = UINT32_C(10);
const std::uint8_t arr[4] = {0x3f, 0x4e, 0x11, 0x93};
std::uint8_t buf[4] = {};

heartbeatLed led;
UART uart1;

int main(){
    mcal::init();
    led.initialize();
    uart1.initialize(UART_1, 115200);
    
    while(1){
        led.toggle();
        // uart1.write(arr, sizeof(arr));
        uart1.read(buf, sizeof(buf));
        mcal::clock::delay(MAIN_LOOP_FREQUENCY);
    }
    
    return 0;
}