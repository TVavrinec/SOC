#include "RB3202_lbr.hpp"

bool vreteno = 0;

using namespace RB3202;
using namespace rb_periphery;

void setup()
{
  sed_periphery();
}

void loop()
{
  if(vreteno)
  {
    if(read_button(SW0))
    {
      led_state(1, LED_R);
    }
    if(read_button(SW1))
    {
      led_state(0, LED_R);
    }
  }

  delay(100);
}