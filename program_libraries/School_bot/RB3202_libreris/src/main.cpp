#include <Arduino.h>
#include "RB3202_lbr.hpp"
//#include "lorris_send.hpp"

// Parser<0xff,10> lorris;
int switch_time = 0;
float motor0_rps = 0;

RB3202_PID pid;
//RB3202_driver motor;
//RB3202_driver encoder;

void setup() 
{
  Serial.begin(115200);

  rb_periphery::sed_periphery();
  
  pid.set_rotate(1,1);
}

void loop()
{
    if(switch_time+100<millis())
    {
        switch_time = millis();
        
        if(!digitalRead(RB3202::SW0))
            motor0_rps -= 0.1;
        else if(!digitalRead(RB3202::SW1))
            motor0_rps += 0.1;
        else if(!digitalRead(RB3202::SW2))
            motor0_rps -= 1;
        else if(!digitalRead(RB3202::SW3))
            motor0_rps += 1;

        Serial.println(motor0_rps);
    }
    pid.set_rotate(motor0_rps,motor0_rps);
}