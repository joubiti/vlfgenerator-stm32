#ifndef LOGGING_H
#define LOGGING_H

#include "uart.h"
#include <cstdint>
#include <string>

namespace log{
    void init(UART uart_periph);
    void info(std::string message);
    void warning(std::string message);
}


#endif