#include "uart.h"


namespace
{
constexpr std::uint32_t CPU_FREQUENCY{UINT32_C(64'000'000)};
constexpr std::uint32_t GET_BRR_VALUE(std::uint32_t bdrate){return (CPU_FREQUENCY/bdrate);};
}

void UART::initialize(uart_periph_nbr uart_id, std::uint32_t uart_bdrate){
    id = uart_id;
    baudrate = uart_bdrate;
    // enable peripheral clock
    switch(id){
        case UART_1: // PC4, PC5 (TX,RX)
            RCC->APBENR2 |= (RCC_APBENR2_USART1EN);
            LL_UART = USART1;
            RCC->IOPENR |= (RCC_IOPENR_GPIOCEN);

            // configure PC4, PC5 (AF)
            GPIOC->AFR[0] |= (GPIO_AFRL_AFSEL4_0);
            GPIOC->AFR[0] |= (GPIO_AFRL_AFSEL5_0);

            GPIOC->MODER &= ~(GPIO_MODER_MODE4);
            GPIOC->MODER |= GPIO_MODER_MODE4_1;
            GPIOC->MODER &= ~(GPIO_MODER_MODE5);
            GPIOC->MODER |= GPIO_MODER_MODE5_1;
            break;
        case UART_2: // PD5, PD6 (TX,RX)
            RCC->APBENR1 |= (RCC_APBENR1_USART2EN);
            LL_UART = USART2;
            RCC->IOPENR |= (RCC_IOPENR_GPIODEN);

            // configure PD5, PD6 (AF)
            GPIOD->AFR[0] &= ~(GPIO_AFRL_AFSEL5);
            GPIOD->AFR[0] &= ~(GPIO_AFRL_AFSEL6);

            GPIOD->MODER &= ~(GPIO_MODER_MODE5);
            GPIOD->MODER |= GPIO_MODER_MODE5_1;
            GPIOD->MODER &= ~(GPIO_MODER_MODE6);
            GPIOD->MODER |= GPIO_MODER_MODE6_1;
            break;
        default:
            break;
    }
    // uart configuration
    LL_UART->CR1 &= ~(USART_CR1_UE);
    LL_UART->CR1 &= ~(USART_CR1_M0);
    LL_UART->CR1 &= ~(USART_CR1_M1);
    // configure baudrate (BRR)
    // USART_DIV = USART_CLK/desired baudrate (64MHz/115200bps)
    LL_UART->BRR = GET_BRR_VALUE(baudrate);
    // configure stop bits (USART_CR2)
    LL_UART->CR2 &= ~(USART_CR2_STOP);
    // enable UART
    LL_UART->CR1 |= (USART_CR1_UE);
}

uart_periph_status UART::write(const std::uint8_t* data, std::uint8_t nb_of_bytes) const{
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
