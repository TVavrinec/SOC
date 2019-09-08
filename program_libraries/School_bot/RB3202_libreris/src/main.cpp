#include <Arduino.h>
#include "RB3202_lbr.hpp"

int switch_time = 0;
float motor0_rps = 0;

RB3202_PID pid;
RB3202_driver motor;

void setup() 
{
  Serial.begin(115200);

  rb_periphery::sed_periphery();
  pid.set_rotate(1,1);
}

void loop()
{
   
   //pid.motor_go_position(0, 1000, 2, 69, 576);
   //pid.motor_go_position(1, 1000, 2, 69, 576);
   //while((pid.driver_state(0)!=0)||(pid.driver_state(1)!=0)){}

   //pid.motor_go_position(1, 100, 2, 69, 576);
   //while(pid.driver_state(1)!=0){}

   //delay(3000);
}