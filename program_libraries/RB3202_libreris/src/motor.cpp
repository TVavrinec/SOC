#include "RB3202_pinout.h"
#include "motor.hpp"

#define FREGUENCY 1000
#define MAX_PWM 2047

void motor::sed_motor_pin(gpio_num_t pin, uint8_t channel)
{
    ledcSetup(channel,FREGUENCY,10);
    ledcAttachPin(pin,channel);
    ledcWrite(channel,MAX_PWM);
}

void motor::sed_all_motor_pins()
{
    sed_motor_pin(RB3202::PWM_M0, 0);
    sed_motor_pin(RB3202::PWM_M1, 1);
    sed_motor_pin(RB3202::PWM_M2, 2);
    sed_motor_pin(RB3202::PWM_M3, 3);
}

void motor::motor_start_working()
{
    digitalWrite(RB3202::SLEEP_PIN,HIGH);
}

int motor::percent_to_pwm(float percent)
{
    return int((percent*0.01)*MAX_PWM);
}

void motor::go_forward(bool motor, int pwm)
{
    if(motor)
    {
        ledcWrite(0,MAX_PWM);
        ledcWrite(1,motor::percent_to_pwm(pwm));  
    }
    else
    {
        ledcWrite(2,MAX_PWM);
        ledcWrite(3,motor::percent_to_pwm(pwm));
    }
}

void motor::go_back(bool motor, int pwm)
{
    if(motor)
    {
        ledcWrite(0,motor::percent_to_pwm(pwm));
        ledcWrite(1,MAX_PWM);
    }
    else
    {
        ledcWrite(2,motor::percent_to_pwm(pwm));
        ledcWrite(3,MAX_PWM);
    }
}

void motor::sed_pwm(bool motor, bool direction, int pwm)
{
    if(direction)
        go_forward(motor,pwm);
    else
        go_back(motor, pwm);
}









void motor::sed_motor()
{
    sed_all_motor_pins();
    motor_start_working();
}

void motor::motors_power(int power_r, int power_l)
{
    if(power_l > 0)
        sed_pwm(1, 1, power_l);
    else
        sed_pwm(1, 0, power_l);

    if(power_r > 0)
        sed_pwm(1, 1, power_r);
    else
        sed_pwm(1, 0, power_r);
}

void motor::stop()
{
    digitalWrite(RB3202::SLEEP_PIN, LOW);
}
motor::~motor()
{
}
