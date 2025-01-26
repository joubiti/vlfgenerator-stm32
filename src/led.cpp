#include "led.h"
#include "stm32g0xx.h"

OnboardLED::OnboardLED(){
    // turn on peripheral clock
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    // set output mode for PA5
    GPIOA->MODER &= ~GPIO_MODER_MODE5;
    GPIOA->MODER |= 1 << GPIO_MODER_MODE5_Pos;
    // set initial state to LOW
    GPIOA->ODR |= GPIO_ODR_OD5;
}

void OnboardLED::toggle(){
    GPIOA->ODR ^= GPIO_ODR_OD5;
}

void OnboardLED::set(){
    GPIOA->ODR |= GPIO_ODR_OD5;
}

void OnboardLED::clear(){
    GPIOA->ODR &= ~GPIO_ODR_OD5;
}