#pragma once

#include <Arduino.h>

#define TURN_EDGES 80
#define COUNT_STEP 0.8

class RB3202_PID
{
private:
    float wheel_rps[2] = {0,0};
    float virtual_vheel[2] = {0,0};

    float dp_memori[2] = {0,0};
    float motor_power[2] = {0,0};

    float p = 1.1;
    float d = 1.7;

    hw_timer_t * timer = NULL;

    void sed_PID_timer();
    void IRAM_ATTR PID();

    void rotate_virtual_wheels(float wheel_rpm, int wheel);
    float calcalate_PID(int wheel);
    void sed_wheel_power(int wheel);

public:
    RB3202_PID(/* args */);

    void sed_rotate(float wheel0, float wheel1);
    void wheel_rotate(float rotate, int wheel);
    float read_PID_power(int wheel);

    ~RB3202_PID();
};