#include <Arduino.h>
#include "RB3202_set.hpp"

bool rb_periphery::sed_periphery()
{
    Serial.begin(115200);

    pinMode(RB3202::LED_R, OUTPUT);
    pinMode(RB3202::LED_G, OUTPUT);
    pinMode(RB3202::LED_B, OUTPUT);

    pinMode(RB3202::SW0, INPUT_PULLUP);
    pinMode(RB3202::SW1, INPUT_PULLUP);
    pinMode(RB3202::SW2, INPUT_PULLUP);
    pinMode(RB3202::SW3, INPUT_PULLUP);
};

bool rb_periphery::LED_on_off(bool state)
{
    digitalWrite(RB3202::LED_R,state);
    digitalWrite(RB3202::LED_G,state);
    digitalWrite(RB3202::LED_B,state);
};