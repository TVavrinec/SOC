#include <Arduino.h>
#include "RB3202_lbr.hpp"
#include "RBControl_manager.hpp"

driver motor;

using namespace rb;

void setup() 
{
  Serial.begin(115200);
  rb_periphery::sed_periphery();

  motor.sed_motor();

  delay(1000);

  Manager::get().install();
  Manager::get().initSmartServoBus(4,GPIO_NUM_14);
  Manager::get().servoBus().limit(0,0_deg,100_deg);
  Manager::get().servoBus().limit(3,80_deg,180_deg);

  motor.motor_start_working();

  Manager::get().servoBus().set(3,100_deg,180.f,1.5f);
  delay(100);
  Manager::get().servoBus().set(0,0_deg,180.f,1.5f);
  delay(2000);

  //while (digitalRead(RB3202::SW1))
  //{
    delay(1);
  //}
  
  for(float a = 0; a<100;a++)
  {
    motor.power(a,a);
    delay(5);
  }
  delay(500);
  for(float a = 100; a>0;a--)
  {
    motor.power(a,a);
    delay(5);
  }
}

void loop()
{
  Manager::get().servoBus().set(3,100_deg,180.f,1.5f);
  delay(100);
  Manager::get().servoBus().set(0,0_deg,180.f,1.5f);
  delay(2000);

  Manager::get().servoBus().set(3,0_deg,180.f,1.5f);
  delay(100);
  Manager::get().servoBus().set(0,100_deg,180.f,1.5f);
  delay(10000);
}