#include <Arduino.h>
#include "RB3202_lbr.hpp"
#include "lorris_send.hpp"

Parser <0xff,22> lorris1;

RB3202_PID motor_pid;

int switch_time;
int send_time;

void setup() 
{ 
  Serial.begin(115200);

  //pinMode(RB3202::SMART_SERVO,INPUT_PULLUP);
  pinMode(GPIO_NUM_14,INPUT_PULLUP);
  
  rb_periphery::sed_periphery();

  motor.sed_motor();
}

void loop()
{
    
}