#include <thread>
#include "RB3202_encoder.hpp"
#include "RB3202_PID.hpp"
#include "RB3202_driver.hpp"

RB3202_driver set;
RB3202_PID pid;

RB3202_PID::RB3202_PID(/* args */)
{
    pid.motor_power[0] = 0;
    pid.motor_power[1] = 0;
    pid.wheel_rps[0] = 0;
    pid.wheel_rps[1] = 0;
    pid.virtual_vheel[0] = 0;
    pid.virtual_vheel[1] = 0;
    pid.driver[0] = 0;
    pid.driver[1] = 0;

    

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

void RB3202_PID::PID()
{
    float change_power;
    float distanc_position;
    float p_member;
    float d_member;

    for(int wheel = 0; wheel < 2; wheel++)
    {   
        pid.virtual_vheel[wheel] += (pid.wheel_rps[wheel] * COUNT_STEP);
    
        distanc_position = pid.virtual_vheel[wheel] - RB3202_encoder::enc[wheel];

        p_member = distanc_position *(p/1000);
        d_member = (distanc_position-pid.dp_memori[wheel])*d;

        change_power = p_member + d_member;

        pid.dp_memori[0] = distanc_position;
        if(abs(pid.motor_power[wheel] + change_power)<100)
        {
            switch(driver[wheel])
            {
            case 2:
                pid.motor_power[wheel] += change_power;
                set.solo_power(pid.motor_power[wheel], wheel);
                break;
            case 1:
                if(plan_position[wheel]>encoder.read_encoder(wheel))
                {
                    pid.motor_power[wheel] += change_power;
                    set.solo_power(pid.motor_power[wheel], wheel);
                }
                else
                {
                    set.solo_power(0, wheel);
                    pid.driver[wheel] = 0;
                }
                break;
            default:
                break;
            }
            pid.motor_power[wheel] += change_power;
        }
    }
}





void RB3202_PID::set_rotate(float wheel0, float wheel1)
{
    pid.wheel_rps[0] = wheel0;
    pid.wheel_rps[1] = wheel1;
}

void RB3202_PID::wheel_rotate(float rotate, int wheel)
{
    pid.wheel_rps[wheel] = rotate;
}

float RB3202_PID::read_PID_power(int wheel)
{
    return pid.motor_power[wheel];
}

void RB3202_PID::motor_go_position(int motor, int distance, int rotate, int wheel_diametr = 69, int encoder_puls = COUNT_STEP)
{
    RB3202_encoder encoder;
    float circuit = wheel_diametr * PI;
    pid.motor_power[motor] = rotate;
    pid.plan_position[motor] = encoder.read_encoder(motor)+int((distance/circuit) * encoder_puls);
    pid.driver[motor] = 2;
}

RB3202_PID::~RB3202_PID()
{
}