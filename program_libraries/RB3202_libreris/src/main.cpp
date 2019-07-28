#include <Arduino.h>
#include "RB3202_lbr.hpp"
#include "lorris_send.hpp"
#include "ESP32_encoder.hpp" 

int switch_time;
int send_time;

ESP32_encoder encoder1 (RB3202::ENC_A1, RB3202::ENC_B1);
Parser<0xff,10> lorris;

RB3202_PID motor;

void setup() 
{ 
  Serial.begin(115200);

  pinMode(GPIO_NUM_39, INPUT_PULLUP);
  
  rb_periphery::sed_periphery();

  motor.set_rotate(1,1);
}

void loop()
{
    Serial.println(encoder1.getCount());
    delay(100);
}