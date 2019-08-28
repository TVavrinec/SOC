#pragma once

#include <driver/adc.h>
#include <driver/gpio.h>

namespace RB3202
{  
    static const gpio_num_t BOARD_OFF = GPIO_NUM_12;

    static const gpio_num_t PWM_M0 = GPIO_NUM_0;
    static const gpio_num_t PWM_M1 = GPIO_NUM_17;
    static const gpio_num_t PWM_M2 = GPIO_NUM_5;
    static const gpio_num_t PWM_M3 = GPIO_NUM_16;
    static const gpio_num_t SLEEP_PIN = GPIO_NUM_2;

    static const gpio_num_t ENC_A1 = GPIO_NUM_4;
    static const gpio_num_t ENC_B1 = GPIO_NUM_15;
    static const gpio_num_t ENC_A2 = GPIO_NUM_14;
    static const gpio_num_t ENC_B2 = GPIO_NUM_13;


    static const gpio_num_t SW0 = GPIO_NUM_25;
    static const gpio_num_t SW1 = GPIO_NUM_13;
    static const gpio_num_t SW2 = GPIO_NUM_27;
    static const gpio_num_t SW3 = GPIO_NUM_26;

    static const gpio_num_t LED_R = GPIO_NUM_21;
    static const gpio_num_t LED_G = GPIO_NUM_22;
    static const gpio_num_t LED_B = GPIO_NUM_23;

    static const gpio_num_t SMART_LED = GPIO_NUM_14;

    static const gpio_num_t SMART_SERVO = GPIO_NUM_23;

    static const gpio_num_t BATERI = GPIO_NUM_33;
};