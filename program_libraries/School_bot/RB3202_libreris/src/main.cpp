#include <Arduino.h>
#include "RB3202_lbr.hpp"
//#include "lorris_send.hpp"

// Parser<0xff,10> lorris;
int switch_time = 0;
float motor0_rps = 0;

//RB3202_PID pid;
RB3202_driver motor;

void setup() 
{
  Serial.begin(115200);

  rb_periphery::sed_periphery();
  motor.set_motor();
  //pid.set_rotate(1,1);//motor_go_position(0,200,1,&fce, 69, 80);
}

void loop()
{
    motor.solo_power(40, 0);
}