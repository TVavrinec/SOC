#pragma once

#include "RB3202_pinout.hpp"

#define LED_R 0
#define LED_G 1
#define LED_B 2

class rb_periphery
{
    private:
    volatile bool ledState[3][2] = {{0,0}, {0,0}, {0,0}};
    
    public:
    bool sed_periphery();

    bool LEDS(bool state);
    bool led_state(bool state, int led);
    bool led_change(int led);

    bool read_button(gpio_num_t sw);

    bool next_thread(bool(*function)(), int repeat, bool micros = false);
};