#pragma once

#include <Arduino.h>

class RB3202_driver
{
private:
    void set_motor_pwm_pin(gpio_num_t pin, uint8_t channel);
    void set_all_motor_pins();
    
    void go_forward(bool motor, float pwm);
    void go_back(bool motor, float pwm);
    void set_pwm(bool motor, bool direction, float pwm);
    
    int percent_to_pwm(float percent);

public:
    RB3202_driver();
    RB3202_driver(bool);

    void motor_start_working();
    void stop();
    void set_motor();
    void power(float power_0, float power_1);
    void solo_power(float power, bool motor);
    void rotate(int rotate_0, int rotate_1);
    void stop(bool motor);
    
    ~RB3202_driver();
};