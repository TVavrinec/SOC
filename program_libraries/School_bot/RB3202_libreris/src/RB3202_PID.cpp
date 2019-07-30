#include "RB3202_PID.hpp"
#include "RB3202_encoder.hpp"
#include "RB3202_driver.hpp"
#include "RB3202_pinout.hpp"



RB3202_driver sed;

RB3202_PID::RB3202_PID(/* args */)
{
    set_PID_timer();
    virtual_vheel[0] = 0;
    virtual_vheel[1] = 0;
    
}

void RB3202_PID::set_PID_timer() 
{
    
    new std::thread([&]()
    {
        RB3202_encoder encoder0 (RB3202::ENC_B1, RB3202::ENC_A1);
        RB3202_encoder encoder1 (RB3202::ENC_B2, RB3202::ENC_A2);
        encoder0.init();
        encoder1.init();
        while(1) 
        {
            encoder[0] = encoder0.getCount();
            encoder[1] = encoder1.getCount();
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
    
    distanc_position = virtual_vheel[wheel] - encoder[wheel];
  

    p_member = distanc_position * p;
    d_member = (distanc_position-dp_memori[wheel])*d;
    
    change_power = p_member + d_member;
    Serial.print(virtual_vheel[wheel]);
    Serial.print("    ");
    Serial.print(encoder[wheel]);
    Serial.print("    ");
    Serial.print(distanc_position);
    Serial.print("    ");
    Serial.print(p_member);
    Serial.print("    ");
    Serial.print(dp_memori[wheel]);
    Serial.print("    ");
    Serial.print(d_member);

    dp_memori[wheel] = distanc_position;
    Serial.println(change_power);
    
    return change_power;
}

void RB3202_PID::set_wheel_power(int wheel)
{
    switch (driver[wheel])
    {
    case 1:
        motor_power[wheel] += calcalate_PID(wheel);
        sed.solo_power(motor_power[wheel], wheel);
        break;
    case 2:
        if(plan_position[wheel]>encoder[wheel])
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
}

void RB3202_PID::PID()
{
    set_wheel_power(0);
    set_wheel_power(1);
}





void RB3202_PID::off()
{
    driver[0];
    driver[1];
}

void RB3202_PID::set_rotate(float wheel0, float wheel1)
{
    wheel_rps[0] = wheel0;
    wheel_rps[1] = wheel1;
    driver[0] = 1;
    driver[1] = 1;
}

void RB3202_PID::wheel_rotate(float rotate, bool wheel)
{
    wheel_rps[wheel] = rotate;
    driver[wheel] = 1;
}

float RB3202_PID::read_PID_power(int wheel)
{
    return motor_power[wheel];
}

void RB3202_PID::motor_go_position(int motor, int distance, int rotate, int wheel_diametr = 69, int encoder_puls = COUNT_STEP)
{
    float circuit = wheel_diametr * PI;

    motor_power[motor] = rotate;
    plan_position[motor] = encoder[motor]+int((distance/circuit) * encoder_puls);
    driver[motor] = 2;
}

RB3202_PID::~RB3202_PID()
{
}