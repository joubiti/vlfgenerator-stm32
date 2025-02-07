#include "log.h"
#include <cstdarg>

namespace{
    constexpr std::size_t MAX_BUFFER_SIZE{255};
}

void logging::send_string_uart(std::string msg){
    logging::uart_instance.write(reinterpret_cast<const std::uint8_t*>(msg.data()), static_cast<std::uint8_t>(msg.size()));
}


void logging::info(const char* message, ...) {
    char msg_buffer[MAX_BUFFER_SIZE]; 
    char log_buffer[MAX_BUFFER_SIZE + 10]; 
    
    va_list args;
    va_start(args, message);
    int msg_length = std::vsnprintf(msg_buffer, sizeof(msg_buffer), message, args);
    va_end(args);
    
    if (msg_length < 0 || msg_length >= static_cast<int>(sizeof(msg_buffer))) return;
    int final_length = std::snprintf(log_buffer, sizeof(log_buffer), "INFO: %s\r\n", msg_buffer);
    if (final_length < 0 || final_length >= static_cast<int>(sizeof(log_buffer))) return;
    
    send_string_uart(std::string(log_buffer, final_length));
}


void logging::warning(const char* message, ...){
    char msg_buffer[MAX_BUFFER_SIZE]; 
    char log_buffer[MAX_BUFFER_SIZE + 10]; 
    
    va_list args;
    va_start(args, message);
    int msg_length = std::vsnprintf(msg_buffer, sizeof(msg_buffer), message, args);
    va_end(args);
    
    if (msg_length < 0 || msg_length >= static_cast<int>(sizeof(msg_buffer))) return;
    int final_length = std::snprintf(log_buffer, sizeof(log_buffer), "WARNING: %s\r\n", msg_buffer);
    if (final_length < 0 || final_length >= static_cast<int>(sizeof(log_buffer))) return;
    
    send_string_uart(std::string(log_buffer, final_length));
}

void logging::error(const char* message, ...){
    char msg_buffer[MAX_BUFFER_SIZE]; 
    char log_buffer[MAX_BUFFER_SIZE + 10]; 
    
    va_list args;
    va_start(args, message);
    int msg_length = std::vsnprintf(msg_buffer, sizeof(msg_buffer), message, args);
    va_end(args);
    
    if (msg_length < 0 || msg_length >= static_cast<int>(sizeof(msg_buffer))) return;
    int final_length = std::snprintf(log_buffer, sizeof(log_buffer), "ERROR: %s\r\n", msg_buffer);
    if (final_length < 0 || final_length >= static_cast<int>(sizeof(log_buffer))) return;
    
    send_string_uart(std::string(log_buffer, final_length));
}