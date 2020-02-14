#include <Arduino.h>
#include "RB3202_lbr.hpp"

RB3202_PID pid;

float speed = 0;
void fc()
{
  digitalWrite(RB3202::LED_G, HIGH);
}

void setup() 
{
  Serial.begin(115200);
  rb_periphery::sed_periphery();
  //pid.motor_go_position(0,1000,100,*fc,70,480);
  //delay(10000);
}

void loop()
{
  if(!digitalRead(RB3202::SW0))
  {
    speed += 0.1;
    Serial.println(speed);
  }
  else if(!digitalRead(RB3202::SW1))
  {
    speed ++;
    Serial.println(speed);
  }
  else if(!digitalRead(RB3202::SW2))
  {
    speed -= 0.1;
    Serial.println(speed);
  }
  else if(!digitalRead(RB3202::SW3))
  {
    speed --;
    Serial.println(speed);
  }
  pid.set_rotate(speed,speed);
  Serial.print("motor power");
  Serial.println(pid.read_PID_power(0));
  delay(100);
}