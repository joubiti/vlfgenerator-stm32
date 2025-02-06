#pragma once
#include <cstdint>
#include "stm32g0xx.h"

typedef enum{
    UART_1,
    UART_2,
    UART_3
}uart_periph_nbr;

typedef enum{
    UART_OK,
    UART_TIMEOUT,
    UART_ERR
}uart_periph_status;

class UART{
    public:
    void initialize(uart_periph_nbr uart_id, std::uint32_t uart_bdrate);
    uart_periph_status write(const std::uint8_t* data, std::uint16_t nb_of_bytes) const;
    uart_periph_status read(std::uint8_t* buf, std::uint16_t nb_of_bytes, std::uint32_t timeout_ms) const;
    uart_periph_nbr id;
    std::uint32_t baudrate;
    uart_periph_status status;

    private:
    USART_TypeDef* LL_UART;

};

