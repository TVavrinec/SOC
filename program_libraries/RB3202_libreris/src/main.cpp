#include <Arduino.h>
#include "RB3202_sed.h"
#include "motor.hpp"

driver motor;

void setup() 
{
  Serial.begin(115200);
  rb_periphery::sed_periphery();
  motor.motor_start_working();
  motor.sed_motor();
}

void loop() 
{
  digitalWrite(GPIO_NUM_21, false);
  digitalWrite(GPIO_NUM_22, false);
  digitalWrite(GPIO_NUM_23, false);
  motor.power(0, 0);

  if(!digitalRead(RB3202::SW1))
  {
    motor.power(50, 50);
    digitalWrite(GPIO_NUM_21, true);
  }
  else if(!digitalRead(RB3202::SW2))
  {
    Serial.println("SW2");
    motor.power(-50, -50);
    digitalWrite(GPIO_NUM_22, true);
  }
  else if(!digitalRead(RB3202::SW3))
  {
    Serial.println("SW3");
    digitalWrite(GPIO_NUM_23, true);
  }
  delay(100);
}