#pragma once

#include <thread>
#include <mutex>
#include <Arduino.h>

#define COUNT_STEP 0.8

class RB3202_PID
{
private:
    int32_t encoder[2];

    float wheel_rps[2] = {0,0};
    float virtual_vheel[2] = {0,0};

    float dp_memori[2] = {0,0};
    float motor_power[2] = {0,0};

    int plan_position[2];
    int driver[2] = {0, 0};

    const float p = 0;//0.001;
    const float d = 5;

    hw_timer_t * timer = NULL;

    void set_PID_timer();
    void PID();

    void rotate_virtual_wheels(float wheel_rpm, int wheel);
    float calcalate_PID(int wheel);
    void set_wheel_power(int wheel);

public:
    RB3202_PID(/* args */);

    void off();

    void set_rotate(float wheel0, float wheel1);
    void wheel_rotate(float rotate, bool wheel);

    void motor_go_position(int , int, float, int, int);

    bool driver_state(int wheel);

    float read_PID_power(int wheel);

    ~RB3202_PID();
};