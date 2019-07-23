#pragma once

#include <Arduino.h>
#include "RB3202_pinout.hpp"
#include "RB3202_encoder.hpp"

RB3202_encoder::RB3202_encoder()
{
    sed_encoder();
}

void RB3202_encoder::sed_pins_encoder0()
{
    pinMode(RB3202::ENC_A1, INPUT_PULLUP);
    pinMode(RB3202::ENC_B1, INPUT_PULLUP);
}

void RB3202_encoder::sed_pins_encoder1()
{
    pinMode(RB3202::ENC_A2, INPUT_PULLUP);
    pinMode(RB3202::ENC_B2, INPUT_PULLUP);
}

void RB3202_encoder::enc0_calculate()
{
   if(digitalRead(RB3202::ENC_A1))
    {
        if(digitalRead(RB3202::ENC_B1))
           enc[0]++;
        else
           enc[0]--;
    }
    else
    {
         if(digitalRead(RB3202::ENC_B1))
            enc[0]--;
         else
            enc[0]++;
    }
}
void RB3202_encoder::enc1_calculate()
{
   if(digitalRead(RB3202::ENC_A2))
    {
        if(digitalRead(RB3202::ENC_B2))
           enc[1]++;
        else
           enc[1]--;
    }
    else
    {
         if(digitalRead(RB3202::ENC_B2))
            enc[1]--;
         else
            enc[1]++;
    }
}





int RB3202_encoder::read_encoder(bool number_encoder)
{
    return enc[number_encoder];
}

void RB3202_encoder::sed_encoder()
{
    RB3202_encoder encoder;

    sed_pins_encoder0();
    sed_pins_encoder1();    

    attachInterrupt(digitalPinToInterrupt(RB3202::ENC_A1), encoder.enc0_calculate, CHANGE);
    attachInterrupt(digitalPinToInterrupt(RB3202::ENC_A2), encoder.enc1_calculate, CHANGE);
}

RB3202_encoder::~RB3202_encoder()
{
}