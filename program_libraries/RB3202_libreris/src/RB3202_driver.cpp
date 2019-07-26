#include "RB3202_pinout.hpp"
#include "RB3202_driver.hpp"

#define FREGUENCY 1000
#define MAX_PWM 1024

RB3202_driver::RB3202_driver()
{
    sed_all_motor_pins();
    motor_start_working();
}

RB3202_driver::RB3202_driver(bool)
{

}

void RB3202_driver::sed_motor_pwm_pin(gpio_num_t pin, uint8_t channel)
{
    ledcSetup(channel,FREGUENCY,10);
    ledcWrite(channel,MAX_PWM);
    ledcAttachPin(pin,channel);
}

void RB3202_driver::sed_all_motor_pins()
{
    pinMode(RB3202::SLEEP_PIN,OUTPUT);
    sed_motor_pwm_pin(RB3202::PWM_M0, 0);
    sed_motor_pwm_pin(RB3202::PWM_M1, 1);
    sed_motor_pwm_pin(RB3202::PWM_M2, 2);
    sed_motor_pwm_pin(RB3202::PWM_M3, 3);
}

int RB3202_driver::percent_to_pwm(float percent)
{
    return MAX_PWM - int((percent*0.01)*MAX_PWM);
}

void RB3202_driver::go_forward(bool motor, float pwm)
{
    if(motor)
    {
        ledcWrite(0,MAX_PWM);
        ledcWrite(1,percent_to_pwm(pwm));  
    }
    else
    {
        ledcWrite(2,MAX_PWM);
        ledcWrite(3,percent_to_pwm(pwm));
    }
}

void RB3202_driver::go_back(bool motor, float pwm)
{
    if(motor)
    {
        ledcWrite(0,percent_to_pwm(pwm));
        ledcWrite(1,MAX_PWM);
    }
    else
    {
        ledcWrite(2,percent_to_pwm(pwm));
        ledcWrite(3,MAX_PWM);
    } 
}

void RB3202_driver::sed_pwm(bool motor, bool direction, float pwm)
{
    if(direction)
        go_forward(motor,pwm);
    else
        go_back(motor, pwm);
}





void RB3202_driver::motor_start_working()
{
    digitalWrite(RB3202::SLEEP_PIN,HIGH);
}

void RB3202_driver::solo_power(float power, bool motor)
{
    if(power > 0)
        sed_pwm(motor, 1, abs(power));
    else
        sed_pwm(motor, 0, abs(power));
}

void RB3202_driver::power(float power_0, float power_1)
{
    if(power_1 > 0)
        sed_pwm(1, 1, abs(power_1));
    else
        sed_pwm(1, 0, abs(power_1));

    if(power_0 > 0)
        sed_pwm(0, 1, abs(power_0));
    else
        sed_pwm(0, 0, abs(power_0));
}

void RB3202_driver::stop()
{
    digitalWrite(RB3202::SLEEP_PIN, LOW);
}

RB3202_driver::~RB3202_driver()
{
}
