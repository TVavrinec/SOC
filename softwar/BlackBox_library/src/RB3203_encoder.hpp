#pragma once

#define _ESP32_ENCODER_

#include "driver/pcnt.h"

static const int16_t PCNT_H_LIM_VAL = 32767;
static const int16_t PCNT_L_LIM_VAL = -32768;
static const int16_t PCNT_THRESH1_VAL = 32766;
static const int16_t PCNT_THRESH0_VAL = -32767;
static const int16_t ESP_INTR_FLAG_DEFAULT = 0;

static const uint8_t pcntPins[16] = {4, 5, 13, 14, 15, 16, 17, 18, 19, 21, 25, 26, 27, 32, 33, 35};

struct CounterTimeData 
{
    volatile int64_t counterPrevTime;   //prev time of pulse interrupt call
    volatile int32_t counterTimeDiff;   //time difference of pulse interrupt calls
    uint8_t aCounterIndex;
    int16_t debounceUs;
};

class RB3203_encoder 
{
    static uint8_t nextCounterIndex;
    uint8_t counterIndex;   //0-7

    int16_t PCNT_internal_count = 0;   //variable to store PCNT coming data, PCNT is only int16_t
    int32_t PCNT_count = 0; //counter variable for external usage
    float frequency = 0.0;
    static uint64_t gpioInputPinSel;
    struct CounterTimeData counterTimeData;
    static void IRAM_ATTR gpio_isr_handler(void* arg);
    uint8_t gpioA;
    uint8_t gpioB;

public:
    bool risingSensitive = true;
    bool fallingSensitive = true;
    bool reverse = false;
    bool enableInterrupts = false;
    int16_t debounceUs = 20;
    int32_t maxPeriodUs = 100000;    //encoder period limit separating zero result [us]
    int32_t minPeriodUs = 1000;    //encoder period limit separating zero results [us]

    RB3203_encoder(uint8_t aGpioA, uint8_t aGpioB);
    void init();
    int32_t getCount(); //return number of MotorEncoder increments with resolution 2 increments per revolution
    int16_t getDiff();
    float getFrequency(); //return motor axis frequency in [Hz]
    void clearCount();
};