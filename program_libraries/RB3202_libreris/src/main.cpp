#include <Arduino.h>
#include "RB3202_lbr.hpp"
#include "RB3202_encoder.hpp"
#include "lorris_send.hpp"

#define TURN_EDGES 80
#define COUNT_STEP 0.8

Parser <0xff,22> lorris1;


driver motor;

int switch_time;
int send_time;









int right_encoder = 0;

void enc0_calculate()
{
   if(digitalRead(RB3202::ENC_A1))
     {
         if(digitalRead(RB3202::ENC_B1))
             right_encoder++;
         else
             right_encoder--;
     }
     else
     {
         if(digitalRead(RB3202::ENC_B1))
             right_encoder--;
         else
             right_encoder++;
    }

}

void sed_encoder()
{
    pinMode(RB3202::ENC_A1, INPUT_PULLUP);
    pinMode(RB3202::ENC_B1, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(RB3202::ENC_A1), enc0_calculate, CHANGE);
    //attachInterrupt(digitalPinToInterrupt(RB3202::ENC_A2), enc1_calculate, FALLING);
}


hw_timer_t * timer = NULL;

float motor0_rps = 0;
float virtual_vheel = 0;

float dp_memori = 0;
float motor0_power = 0;

float p = 1.1;
float d = 1.7;

void IRAM_ATTR PID();

void sed_PID_timer()
{
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &PID, true);
    timerAlarmWrite(timer, 10000, true);
    timerAlarmEnable(timer);
}

void IRAM_ATTR PID()
{
    float change_power;
    float distanc_position;
    float p_member;
    float d_member;

        virtual_vheel = virtual_vheel + (motor0_rps * COUNT_STEP);

    distanc_position = virtual_vheel - right_encoder;

    p_member = distanc_position*(p/1000);
    d_member = (distanc_position-dp_memori)*d;

    change_power = p_member + d_member;

    if(abs(motor0_power + change_power)<100)
    {
        motor0_power += change_power;
    }

    dp_memori = distanc_position;
}


void setup() 
{ 
  Serial.begin(115200);
  sed_encoder();
  sed_PID_timer();

  //pinMode(RB3202::SMART_SERVO,INPUT_PULLUP);
  pinMode(GPIO_NUM_14,INPUT_PULLUP);
  
  rb_periphery::sed_periphery();

  motor.sed_motor();
}
byte m0p;
byte sp;
byte sd;
byte m0_rps;
byte m0_rps_real;
int l_position=0;
void loop()
{
    if(switch_time+100<millis())
    {
        switch_time = millis();
        if(!digitalRead(GPIO_NUM_14))
        {
            if(!digitalRead(RB3202::SW0))
                p -= 0.1;
            else if(!digitalRead(RB3202::SW1))
                p += 0.1;
            else if(!digitalRead(RB3202::SW2))
                d -= 0.1;
            else if(!digitalRead(RB3202::SW3))
                d += 0.1;
        }
        else
        {
            if(!digitalRead(RB3202::SW0))
                motor0_rps -= 0.1;
            else if(!digitalRead(RB3202::SW1))
                motor0_rps += 0.1;
            else if(!digitalRead(RB3202::SW2))
                d -= 0.1;
            else if(!digitalRead(RB3202::SW3))
                d += 0.1;
        }
        
    }
    if(send_time+100<millis())
    {
        m0p = motor0_power;
        sp = p*10;
        sd = d*10;
        m0_rps = motor0_rps*10;
        m0_rps_real = (right_encoder-l_position)/0.1;
        l_position = right_encoder;
        lorris1.send(Serial,0,m0p,sp,sd,m0_rps,m0_rps_real);
    }
    // Serial.print(motor0_power);
    // Serial.print("   ");
    // Serial.print(p);
    // Serial.print("   ");
    // Serial.print(d);
    // Serial.print("   ");
    Serial.println(motor0_rps);
    motor.power(0,motor0_power);
}