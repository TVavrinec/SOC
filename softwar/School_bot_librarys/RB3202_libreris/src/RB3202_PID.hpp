#pragma once

#include <mutex>
#include <Arduino.h>
#include <functional>
#include <thread>


#define COUNT_STEP 0.8

class RB3202_PID
{
private:
    volatile int32_t encoder[2];

    volatile float wheel_rps[2] = {0,0};
    volatile float virtual_vheel[2] = {0,0};

    volatile float dp_memori[2] = {0,0};
    volatile float motor_power[2] = {0,0};

    volatile int plan_position[2];
    volatile int driver[2] = {0, 0};

    volatile const float p = 0.001;
    volatile const float d = 5;

    hw_timer_t * timer = NULL;

    bool set_PID_timer();
    bool PID();

    void (*call_back)();

    float rotate_virtual_wheels(float wheel_rpm, int wheel);
    float calcalate_PID(int wheel);
    float set_wheel_power(int wheel);

public:
    RB3202_PID();

    void off();

    void set_rotate(float wheel0, float wheel1);
    void wheel_rotate(float rotate, bool wheel);

    void motor_go_position(int motor, int distance, float cm_per_s, void (*callBack)() = nullptr, int wheel_diametr = 69, int puls_per_rotate = 480);
    bool motor_go_angle_position(int motor, int angle, float rotate_per_second, int encoder_puls = 480);

    bool driver_state(int wheel);

    int32_t get_motor_position(int wheel);

    float read_PID_power(int wheel);

    ~RB3202_PID();
};