#include "log.h"
#include <cstdarg>

namespace{
    constexpr std::size_t MAX_BUFFER_SIZE{255};
}

void logging::send_string_uart(std::string msg){
    logging::uart_instance.write(reinterpret_cast<const std::uint8_t*>(msg.data()), static_cast<std::uint8_t>(msg.size()));
}

void logging::info(const char* message, ...)
{
    char buffer[MAX_BUFFER_SIZE];
    va_list args;
    va_start(args, message);
    std::vsnprintf(buffer, sizeof(buffer), message, args);
    va_end(args);

    char log_buffer[MAX_BUFFER_SIZE + 20];

    std::snprintf(log_buffer, sizeof(log_buffer), "INFO: %s\n", buffer);
    send_string_uart(log_buffer);
}

void logging::warning(const char* message, ...){
    char buffer[MAX_BUFFER_SIZE];
    va_list args;
    va_start(args, message);
    std::vsnprintf(buffer, sizeof(buffer), message, args);
    va_end(args);

    char log_buffer[MAX_BUFFER_SIZE + 20];

    std::snprintf(log_buffer, sizeof(log_buffer), "WARNING: %s\n", buffer);
    send_string_uart(log_buffer);
}

void logging::error(const char* message, ...){
    char buffer[MAX_BUFFER_SIZE];
    va_list args;
    va_start(args, message);
    std::vsnprintf(buffer, sizeof(buffer), message, args);
    va_end(args);

    char log_buffer[MAX_BUFFER_SIZE + 20]; 

    std::snprintf(log_buffer, sizeof(log_buffer), "ERROR: %s\n", buffer);
    send_string_uart(log_buffer);
}