#include "Arduino.h"
#include "RB3202_sed.hpp"

void rb_periphery::sed_periphery()
{
    pinMode(RB3202::LED_R, OUTPUT);
    pinMode(RB3202::LED_G, OUTPUT);
    pinMode(RB3202::LED_B, OUTPUT);

    pinMode(RB3202::SW0, INPUT_PULLUP);
    pinMode(RB3202::SW1, INPUT_PULLUP);
    pinMode(RB3202::SW2, INPUT_PULLUP);
    pinMode(RB3202::SW3, INPUT_PULLUP);
};