#pragma once

#include "uart.h"
#include <cstdint>
#include <string>

class logging{
    public:
    logging(UART& uart_periph) : uart_instance(uart_periph) {}
    void info(const char* message, ...);
    void warning(const char* message, ...);
    void error(const char* message, ...);

    private:
    UART& uart_instance;
    void send_string_uart(std::string msg);
};
