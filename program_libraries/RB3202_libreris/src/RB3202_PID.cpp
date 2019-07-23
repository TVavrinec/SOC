#pragma once

#include "RB3202_PID.hpp"
#include "RB3202_encoder.hpp"
#include "RB3202_driver.hpp"

RB3202_PID::RB3202_PID(/* args */)
{
    sed_PID_timer();
}

void RB3202_PID::sed_PID_timer()
{
    RB3202_PID regulator;
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &regulator.PID, true);
    timerAlarmWrite(timer, 10000, true);
    timerAlarmEnable(timer);
}

void RB3202_PID::rotate_virtual_wheels(float wheel_rpm, int wheel)
{
    virtual_vheel[wheel] += (wheel_rpm * COUNT_STEP);
}

float RB3202_PID::calcalate_PID(int wheel)
{
    RB3202_encoder encoder;
    float change_power;
    float distanc_position;
    float p_member;
    float d_member;

    rotate_virtual_wheels(wheel_rps[wheel], wheel);
    
    distanc_position = virtual_vheel[wheel] - encoder.read_encoder(wheel);

    p_member = distanc_position *(p/1000);
    d_member = (distanc_position-dp_memori[wheel])*d;
    
    change_power = p_member + d_member;
    
    dp_memori[0] = distanc_position;
    
    return change_power;
}

void RB3202_PID::sed_wheel_power(int wheel)
{
    RB3202_driver sed;
    if(abs(motor_power[wheel] + calcalate_PID(wheel))<100)
    {
        motor_power[wheel] += calcalate_PID(wheel);
        sed.solo_power(motor_power[wheel], wheel);
    }
}

void IRAM_ATTR RB3202_PID::PID()
{
    sed_wheel_power(0);
    sed_wheel_power(1);
}





void RB3202_PID::sed_rotate(float wheel0, float wheel1)
{
    wheel_rps[0] = wheel0;
    wheel_rps[1] = wheel1;
}

void RB3202_PID::wheel_rotate(float rotate, int wheel)
{
    wheel_rps[wheel] = rotate;
}

float RB3202_PID::read_PID_power(int wheel)
{
    return motor_power[wheel];
}

RB3202_PID::~RB3202_PID()
{
}