#include <Arduino.h>
#include "RB3202_lbr.hpp"

int switch_time = 0;
float motor0_rps = 0;

RB3202_PID pid;
RB3202_driver motor;
using namespace RB3202;

void setup() 
{
  rb_periphery::sed_periphery();
  motor.power(50,50);
}

void loop()
{
  Serial.println(digitalRead(SW2));
  if(digitalRead(SW2))
  {
    rb_periphery::LED_on_off(0);
  }
  else
  {
    rb_periphery::LED_on_off(1);
  }
}