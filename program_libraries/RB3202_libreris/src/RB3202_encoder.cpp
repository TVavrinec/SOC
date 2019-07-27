#include <Arduino.h>
#include "RB3202_pinout.hpp"
#include "RB3202_encoder.hpp"
#include "RB3202_driver.hpp"

#define TURN_EDGES 80

RB3202_encoder encoder;

RB3202_encoder::RB3202_encoder()
{
    encoder.driver[0] = false;
    encoder.driver[1] = false;
    set_encoder();
}

void RB3202_encoder::set_pins_encoder0()
{
    pinMode(RB3202::ENC_A1, INPUT_PULLUP);
    pinMode(RB3202::ENC_B1, INPUT_PULLUP);
}

void RB3202_encoder::set_pins_encoder1()
{
    pinMode(RB3202::ENC_A2, INPUT_PULLUP);
    pinMode(RB3202::ENC_B2, INPUT_PULLUP);
}

void RB3202_encoder::enc0_calculate()
{
    RB3202_driver motor;
    if(digitalRead(RB3202::ENC_A1))
    {
        if(digitalRead(RB3202::ENC_B1))
           encoder.enc[0]++;
        else
           encoder.enc[0]--;
    }
    else
    {
         if(digitalRead(RB3202::ENC_B1))
            encoder.enc[0]--;
         else
            encoder.enc[0]++;
    }
    if(encoder.driver[0])
    {
        if(encoder.enc[0]<encoder.plan_position[0])
        {
            motor.solo_power(encoder.motor_power[0], 0);
        }
        else
        {
            motor.solo_power(0,0);
            encoder.driver[0] = false;
        }
    }
}

void RB3202_encoder::enc1_calculate()
{
    RB3202_driver motor;
    if(digitalRead(GPIO_NUM_18))
    {
        if(digitalRead(GPIO_NUM_19))
           encoder.enc[1]++;
        else
           encoder.enc[1]--;
    }
    else
    {
         if(digitalRead(GPIO_NUM_19))
            encoder.enc[1]--;
         else
            encoder.enc[1]++;
    }
    if(encoder.driver[1])
    {
        if(encoder.enc[1]<encoder.plan_position[1])
        {
            motor.solo_power(encoder.motor_power[1], 1);
        }
        else
        {
            motor.solo_power(0,1);
            encoder.driver[0] = false;
        }
    }
}

void RB3202_encoder::set_encoder()
{
    set_pins_encoder0();
    set_pins_encoder1();
    
    attachInterrupt(digitalPinToInterrupt(RB3202::ENC_A1), encoder.enc0_calculate, CHANGE);
    attachInterrupt(digitalPinToInterrupt(RB3202::ENC_A2), encoder.enc1_calculate, CHANGE);
}





int RB3202_encoder::read_encoder(bool number_encoder)
{
    return encoder.enc[number_encoder];
}

void RB3202_encoder::motor_go_position(int motor, int distance, int power, int wheel_diametr = 69, int encoder_puls = 80)
{
    float circuit = wheel_diametr * PI;
    encoder.motor_power[motor] = power;
    encoder.plan_position[motor] = encoder.enc[motor]+int((distance/circuit) * encoder_puls);
    encoder.driver[motor] = true;
}

RB3202_encoder::~RB3202_encoder()
{
}