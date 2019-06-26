#include "RB3202_pinout.h"
#include "motor.hpp"

#define 

void sed_motor_pin(gpio_num_t pin, uint8_t channel)
{
    ledcSetup(channel,1000,10);
    ledcAttachPin(pin,channel);
    ledcWrite(channel,1000);
}

void sed_motor_pins()
{
    sed_motor_pin(RB3202::PWM_M0, 0);
    sed_motor_pin(RB3202::PWM_M1, 1);
    sed_motor_pin(RB3202::PWM_M2, 2);
    sed_motor_pin(RB3202::PWM_M3, 3);
}

void motor_start_working()
{
    digitalWrite(RB3202::SLEEP_PIN,HIGH);
}

void motor::sed_motor()
{
    sed_motor_pins();
}

void motor::motors_power(int power_r, int power_l)
{

}

motor::~motor()
{
}
