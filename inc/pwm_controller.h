#pragma once

#include <cstdint>

class PWM_Controller{
    public:
    static void init(void);
    static void setFrequency(std::uint32_t frequency);
    static void setDutyCycle(float dutyCycle);
    static void stop();
    static void start();
};