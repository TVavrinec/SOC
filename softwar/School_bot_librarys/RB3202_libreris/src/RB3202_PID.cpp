/*
#include "RB3202_PID.hpp"
#include "RB3202_encoder.hpp"
#include "RB3202_driver.hpp"
#include "RB3202_pinout.hpp"

std::mutex mx;

RB3202_driver sed;

RB3202_PID::RB3202_PID()
{
    set_PID_timer();    
}

void RB3202_PID::set_PID_timer() 
{
    new std::thread([&]()
    {
        RB3202_encoder encoder0 (RB3202::ENC_A1, RB3202::ENC_B1);
        RB3202_encoder encoder1 (RB3202::ENC_A2, RB3202::ENC_B2);
        encoder0.init();
        encoder1.init();
        while(1) 
        {
            for(int a = 0; a<10; a++)
            {
                encoder[0] = encoder0.getCount();
                encoder[1] = encoder1.getCount();
                rotate_virtual_wheels(wheel_rps[0], 0);
                rotate_virtual_wheels(wheel_rps[1], 1);
                PID();
                usleep(10000);
            }
        }
    });
}

void RB3202_PID::rotate_virtual_wheels(float wheel_rps, int wheel)
{
    virtual_vheel[wheel] += (wheel_rps * COUNT_STEP);
}

float RB3202_PID::calcalate_PID(int wheel)
{
    float change_power;
    float distanc_position;
    //float p_member;
    float d_member;
    
    distanc_position = virtual_vheel[wheel] - encoder[wheel];
    //p_member = distanc_position * p;
    d_member = (distanc_position-dp_memori[wheel])*d;
    
    change_power = d_member;// + p_member;
    dp_memori[wheel] = distanc_position;
    
    return change_power;
}

void RB3202_PID::set_wheel_power(int wheel)
{
    float change_power = calcalate_PID(wheel);
    if(abs(motor_power[wheel] + change_power) <= 120)
    {
        switch (driver[wheel])
        {
        case 1:
            motor_power[wheel] += change_power;
            sed.solo_power(motor_power[wheel], wheel);
            break;
        case 2:
            if(plan_position[wheel]>encoder[wheel])
            {
                motor_power[wheel] += change_power;
                sed.solo_power(motor_power[wheel], wheel);
            }
            else
            {
                wheel_rps[wheel] = 0;
                sed.solo_power(0, wheel);
                //call_back;
                mx.lock();
                driver[wheel] = 1;
                mx.unlock();
                
            }
            break;
        default:
            break;
        }
    }
}

void RB3202_PID::PID()
{
    set_wheel_power(0);
    set_wheel_power(1);
}





void RB3202_PID::off()
{
    mx.lock();
    driver[0] = 0;
    driver[1] = 0;
    mx.unlock();
}

void RB3202_PID::set_rotate(float wheel0, float wheel1)
{
    wheel_rps[0] = wheel0;
    wheel_rps[1] = wheel1;
    mx.lock();
    driver[0] = 1;
    driver[1] = 1;
    mx.unlock();
}

void RB3202_PID::wheel_rotate(float rotate, bool wheel)
{
    mx.lock();
    driver[wheel] = 1;
    mx.unlock();

    wheel_rps[wheel] = rotate;
}

float RB3202_PID::read_PID_power(int wheel)
{
    return motor_power[wheel];
}

void RB3202_PID::motor_go_position(int motor, int distance, float cm_per_s, void (*fc)(), int wheel_diametr, int puls_per_rotate)
{
    float circuit = wheel_diametr * PI;

    wheel_rps[motor] = cm_per_s/circuit;
    plan_position[motor] = encoder[motor]+int((distance/circuit) * puls_per_rotate);
    mx.lock();
    driver[motor] = 2;
    mx.unlock();
    call_back = fc;
}

bool RB3202_PID::motor_go_angle_position(int motor, int angle, float speed, int encoder_puls)
{
    wheel_rps[motor] = speed;
    plan_position[motor] = encoder[motor]+int((angle/360) * encoder_puls);
    mx.lock();
    driver[motor] = 2;
    mx.unlock();
    return true;
}

bool RB3202_PID::driver_state(int wheel)
{
    return driver[wheel];
}

RB3202_PID::~RB3202_PID()
{
}
*/