#include <Arduino.h>
#include "RB3202_lbr.hpp"

RB3202_PID pid;
RB3202_driver motor;

bool fc()
{
}

void setup() 
{
  rb_periphery::sed_periphery();
  rb_periphery::next_thread(fc,100);
}

void loop()
{
  
}