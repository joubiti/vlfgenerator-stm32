#include "uart.h"

void UART::initialize(uart_periph_nbr uart_id, uart_baudrate_opts){
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
    GPIOC->AFR[0] |= (GPIO_AFRL_AFSEL4_0);
    GPIOC->AFR[0] |= (GPIO_AFRL_AFSEL5_0);

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
    // USART_DIV = USART_CLK/desired baudrate (64MHz/115200bps)
    LL_UART->BRR = 0x22B;
    // configure stop bits (USART_CR2)
    LL_UART->CR2 &= ~(USART_CR2_STOP);
    // enable UART
    LL_UART->CR1 |= (USART_CR1_UE);
}

uart_periph_status UART::write(const std::uint8_t* data, std::uint8_t nb_of_bytes){
    // send idle frame as first transmission
    LL_UART->CR1 |= (USART_CR1_TE);
    for(std::uint8_t i = 0; i < nb_of_bytes; i++){
        // busy-wait until data register not full
        while(!(LL_UART->ISR & (USART_ISR_TXE_TXFNF)));
        // write data
        LL_UART->TDR = data[i];
    }
    while(!(LL_UART->ISR & (USART_ISR_TC)));
    LL_UART->CR1 &= ~(USART_CR1_TE);
    // for now, always return OK
    return UART_OK;
}
