#include "stm32g0xx.h"
#include <cstdint>



namespace mcal
{
    void init(); // initialize system clock and main CPU frequency (64 MHz)
    
    namespace clock
    {
        void delay(std::uint32_t ms);
        std::uint32_t get_ticks(void);
    }
}