#include <thread>
#include "RB3202_PID.hpp"
#include "ESP32_encoder.hpp"
#include "RB3202_driver.hpp"
#include "RB3202_pinout.hpp"

ESP32_encoder encoder (RB3202::ENC_A1, RB3202::ENC_B1);

RB3202_PID::RB3202_PID(/* args */)
{
    set_PID_timer();
}

void RB3202_PID::set_PID_timer() 
{
    new std::thread([&]()
    {
        while(1) 
        {
        PID();
        usleep(10000);
        }
    });
}

void RB3202_PID::rotate_virtual_wheels(float wheel_rpm, int wheel)
{
    virtual_vheel[wheel] += (wheel_rpm * COUNT_STEP);
}

float RB3202_PID::calcalate_PID(int wheel)
{
    float change_power;
    float distanc_position;
    float p_member;
    float d_member;

    rotate_virtual_wheels(wheel_rps[wheel], wheel);
    
    distanc_position = virtual_vheel[wheel] - encoder.getCount();

    p_member = distanc_position *(p/1000);
    d_member = (distanc_position-dp_memori[wheel])*d;
    
    change_power = p_member + d_member;
    
    dp_memori[0] = distanc_position;
    
    return change_power;
}

void RB3202_PID::set_wheel_power(int wheel)
{
    RB3202_driver sed;
    if(abs(motor_power[wheel] + calcalate_PID(wheel))<100)
    {
        switch (driver[wheel])
        {
        case 2:
            motor_power[wheel] += calcalate_PID(wheel);
            sed.solo_power(motor_power[wheel], wheel);
            break;
        case 1:
            if(plan_position[wheel]>encoder.getCount())
            {
                motor_power[wheel] += calcalate_PID(wheel);
                sed.solo_power(motor_power[wheel], wheel);
            }
            else
            {
                sed.solo_power(0, wheel);
                driver[wheel] = 0;
            }
            break;
        default:
            break;
        }
        motor_power[wheel] += calcalate_PID(wheel);
        sed.solo_power(motor_power[wheel], wheel);
    }
}

void IRAM_ATTR RB3202_PID::PID()
{
    set_wheel_power(0);
    set_wheel_power(1);
}





void RB3202_PID::set_rotate(float wheel0, float wheel1)
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

void RB3202_PID::motor_go_position(int motor, int distance, int rotate, int wheel_diametr = 69, int encoder_puls = COUNT_STEP)
{
    float circuit = wheel_diametr * PI;
    motor_power[motor] = rotate;
    plan_position[motor] = encoder.getCount()+int((distance/circuit) * encoder_puls);
    driver[motor] = 2;
}

RB3202_PID::~RB3202_PID()
{
}