#include <Arduino.h>
#include <thread>
#include <mutex>
#include "RB3202_set.hpp"

bool rb_periphery::sed_periphery()
{
    Serial.begin(115200);

    pinMode(RB3202::LED_r, OUTPUT);
    pinMode(RB3202::LED_g, OUTPUT);
    pinMode(RB3202::LED_b, OUTPUT);

    pinMode(RB3202::SW0, INPUT_PULLUP);
    pinMode(RB3202::SW1, INPUT_PULLUP);
    pinMode(RB3202::SW2, INPUT_PULLUP);
    pinMode(RB3202::SW3, INPUT_PULLUP);

    new std::thread([&]()
    {
        while(true)
        {
            digitalWrite(RB3202::LED_r,ledState[0][0]);
            digitalWrite(RB3202::LED_g,ledState[1][0]);
            digitalWrite(RB3202::LED_b,ledState[2][0]);

            while((ledState[0][0]==ledState[0][1])
                &&(ledState[1][0]==ledState[1][1])
                &&(ledState[2][0]==ledState[2][1]))
            {
                usleep(1000);
            }

            ledState[0][1] = ledState[0][0];
            ledState[1][1] = ledState[1][0];
            ledState[2][1] = ledState[2][0];
        }
    });

    return true;
};

bool rb_periphery::LEDS(bool state)
{
    ledState[0][0] = state;
    ledState[1][0] = state;
    ledState[2][0] = state;

    return true;
};

bool rb_periphery::led_state(bool state, int led)
{
    ledState[led][0] = state;

    return true;
}

bool rb_periphery::led_change(int led)
{

    ledState[led][0] = !ledState[led][0];

    return true;
}


bool rb_periphery::read_button(gpio_num_t sw)
{
    return !digitalRead(sw);
}



// bool rb_periphery::next_thread( bool (*function)(), int repeat, bool micros)
// {
//     if(!micros)
//     {
//         repeat *= 1000;
//     }
//     new std::thread([&]()
//     {
//         while(function())
//         {
//             usleep(repeat);
//         }
//     });

//     return true;
// }
