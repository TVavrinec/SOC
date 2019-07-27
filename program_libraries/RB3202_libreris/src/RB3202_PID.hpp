#pragma once

#include <iostream>
#include <Arduino.h>

#define COUNT_STEP 0.8

class RB3202_PID
{
private:
    static float wheel_rps[2];
    static float virtual_vheel[2];

    static float dp_memori[2];
    static float motor_power[2];

    static int plan_position[2];
    static int driver[2];

    static float p;
    static float d;

    hw_timer_t * timer = NULL;

    void set_PID_timer();
    static void PID();

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