#include <Arduino.h>
#include "RB3202_lbr.hpp"

int switch_time = 0;
float motor0_rps = 0;

RB3202_PID pid;
RB3202_driver motor;
using namespace RB3202;

int x = 0;

void setup() 
{
  rb_periphery::sed_periphery();
  new std::thread([&]()
  {
    while(true)
    {
      Serial.println(pid.read_PID_power(0));
      usleep(500000);
    }
  });
}

void loop()
{
  delay(50);
}