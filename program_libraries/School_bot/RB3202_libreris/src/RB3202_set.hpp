#include "RB3202_pinout.hpp"

namespace rb_periphery
{
    bool sed_periphery();
    bool LED_on_off(bool state);

    bool next_thread( bool (*function)(), int repeat, bool micros = false);
};