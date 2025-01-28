#include "uart.h"

UART::UART(uart_periph_nbr uart_id, uart_baudrate_opts){
    uart_periph_id = uart_id;
    // enable peripheral clock
    switch(uart_periph_id){
        case UART_1:
            RCC->APBENR2 |= (RCC_APBENR2_USART1EN);
            LL_UART = USART1;
            break;
        case UART_2:
            RCC->APBENR1 |= (RCC_APBENR1_USART2EN);
            LL_UART = USART2;
            break;
        default:
            break;
    }
    // enable port C clock
    RCC->IOPENR |= (RCC_IOPENR_GPIOCEN);
    // configure PC4, PC5 (AF)
    GPIOC->MODER &= ~(GPIO_MODER_MODE4);
    GPIOC->MODER |= GPIO_MODER_MODE4_1;
    GPIOC->MODER &= ~(GPIO_MODER_MODE5);
    GPIOC->MODER |= GPIO_MODER_MODE5_1;
    // uart configuration
    // 8 bits
    LL_UART->CR1 &= ~(USART_CR1_UE);
    LL_UART->CR1 &= ~(USART_CR1_M0);
    LL_UART->CR1 &= ~(USART_CR1_M1);
    // configure baudrate (BRR)
    // configure stop bits (USART_CR2)
    // enable UART
}