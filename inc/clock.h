#ifndef CLOCK_H
#define CLOCK_H

#include <cstdint>


class Clock{
    public:
        static void initialize();
        static void delay_ms(std::uint32_t ms);
        static std::uint32_t get_ticks(void);
    private:
        static void enable_HSI();
        static void configure_flash_intf();
        static void configure_PLL();
        static void configure_prescalers();
        static void switch_system_clock();
        static void configure_systick();
};


#endif