#include <Arduino.h>
#include "RB3202_lbr.hpp"
#include "lorris_send.hpp"

int switch_time;
int send_time;

Parser<0xff,10> lorris;
RB3202_PID motor;

void setup() 
{ 
  Serial.begin(115200);

  pinMode(GPIO_NUM_39, INPUT_PULLUP);
  
  rb_periphery::sed_periphery();

  motor.set_rotate(0.3,0.3);
}

void loop()
{
    lorris.send(Serial, 0,analogRead(GPIO_NUM_39));    
}