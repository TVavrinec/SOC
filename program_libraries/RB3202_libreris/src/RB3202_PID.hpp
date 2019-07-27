#pragma once

#include <iostream>
#include <Arduino.h>

#define COUNT_STEP 0.8

class RB3202_PID
{
private:
    float wheel_rps[2];
    float virtual_vheel[2];

    float dp_memori[2];
    float motor_power[2];

    int plan_position[2];
    int driver[2];

    float p = 1;
    float d = 2;

    hw_timer_t * timer = NULL;

    void set_PID_timer();
    void PID();

    void rotate_virtual_wheels(float wheel_rpm, int wheel);
    float calcalate_PID(int wheel);
    void set_wheel_power(int wheel);

public:
    RB3202_PID(/* args */);

    void set_rotate(float wheel0, float wheel1);
    void wheel_rotate(float rotate, int wheel);
    float read_PID_power(int wheel);
    void motor_go_position(int , int, int, int, int);

    ~RB3202_PID();
};