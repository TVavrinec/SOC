#include "RB3203_Pinout.hpp"
#include "esp_system.h"
#include "RB3203_i2c-periphery.hpp"
//#include "RB3203_encoder.hpp"
#include "driver/timer.h"
//#include <SmartLeds.h>
//#include <Arduino.h>

i2cPeriphery mpu(rb3203::Scl,rb3203::Sda);
//RB3203_encoder encoder (rb3203::encA, rb3203::encB);

bool unlock()
{
    while( gpio_get_level(GPIO_NUM_33))
    {
        gpio_set_level (rb3203::lock,true);
    }
    while( !gpio_get_level(GPIO_NUM_33))
    {
        gpio_set_level (rb3203::lock,true);
    }
    gpio_set_level ( rb3203::lock,false);

    //timer_get_counter_value();

    return true; 
}

bool lock()
{
    //if(!gpio_get_level(GPIO_NUM_33))
    //unlock();
    gpio_set_level ( rb3203::lock,true);
    vTaskDelay(100);
    gpio_set_level ( rb3203::lock,false);
    return true;
}

void setup()
{
    //Serial.begin(115200);
    gpio_set_direction ( GPIO_NUM_33 , GPIO_MODE_INPUT );
    gpio_set_pull_mode (GPIO_NUM_33, GPIO_PULLUP_ONLY);
    gpio_set_direction ( rb3203::lock, GPIO_MODE_OUTPUT );
    gpio_set_direction ( rb3203::sw0, GPIO_MODE_INPUT );
    gpio_set_pull_mode(rb3203::sw0, GPIO_PULLUP_ONLY);
    //encoder.init();
    lock();
}

void loop()
{
    //Serial.println(gpio_get_level(rb3203::sw0));
}