#include "led.h"
#include "stm32g0xx.h"

void heartbeatLed::initialize(){
    // turn on peripheral clock
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    // set output mode for PA5
    GPIOA->MODER &= ~GPIO_MODER_MODE5;
    GPIOA->MODER |= 1 << GPIO_MODER_MODE5_Pos;
    // set initial state to LOW
    GPIOA->ODR |= GPIO_ODR_OD5;
}

void heartbeatLed::toggle(){
    GPIOA->ODR ^= GPIO_ODR_OD5;
}

void heartbeatLed::set(){
    GPIOA->ODR |= GPIO_ODR_OD5;
}

void heartbeatLed::clear(){
    GPIOA->ODR &= ~GPIO_ODR_OD5;
}