#ifndef UART_H

#include <cstdint>
#include "stm32g0xx.h"

typedef enum{
    UART_1,
    UART_2,
    UART_3
}uart_periph_nbr;

typedef enum{
    BAUDRATE_9600,
    BAUDRATE_115200
}uart_baudrate_opts;

typedef enum{
    UART_OK,
    UART_ERR
}uart_periph_status;

class UART{
    public:
    void initialize(uart_periph_nbr uart_id, uart_baudrate_opts uart_bdrate);
    uart_periph_status write(const std::uint8_t* data, std::uint8_t nb_of_bytes) const;
    uart_periph_status read(std::uint8_t* buf, std::uint8_t nb_of_bytes) const;
    uart_periph_nbr uart_periph_id;
    uart_baudrate_opts uart_bdrate;
    uart_periph_status uart_status;

    private:
    USART_TypeDef* LL_UART;

};


#endif