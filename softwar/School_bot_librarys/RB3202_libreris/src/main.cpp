#include "RB3202_lbr.hpp"

void setup()
{
  ui.sed_periphery();
  ui.led_state(HIGH, LED_R); // rozsvitime cervenou jako vychozi stav semaforu
}

void loop()
{
  if(ui.read_button(SW0)) // pokud stiskneme tlacitko SW0 zacneme prepinat semafor
  {
    ui.led_state(LOW,  LED_R); // zhasneme cervenou
    ui.led_state(HIGH, LED_B); // rozsvitime oranzovou (ja rozsvesim modrou protoze mem starou desku kde oranzova neni)
    delay(1000); // pockame 1 sekundu (1000 milisekund) nez budeme pokracovat
    ui.led_state(LOW,  LED_B); // zhasneme oranzovou
    ui.led_state(HIGH, LED_G); // rozsvitime zelenou
  }
  else if(ui.read_button(SW1)) // pokud stiskneme tlacitko SW1 zacneme prepinat semafor
  {
    ui.led_state(HIGH, LED_B); // rozsvitime oranzovou (ja rozsvesim modrou protoze mem starou desku kde oranzova neni)
    delay(1000); // pockame 1 sekundu (1000 milisekund) nez budeme pokracovat
    ui.led_state(LOW,  LED_G); // zhasneme zelenou
    ui.led_state(LOW,  LED_B); // zhasneme oranzovou
    ui.led_state(HIGH, LED_R); // rozsvitime cervenou
  }
  delay(100); // protoze nemusime cist tlacitka a nastoavoval ledky az tak casto chvili pockame
}