#pragma once

#include "esp_system.h"

namespace rb3203
{
    static const gpio_num_t Sda = GPIO_NUM_23;
    static const gpio_num_t Scl = GPIO_NUM_22;

    static const gpio_num_t intSqw = GPIO_NUM_21;
    static const gpio_num_t intQmc = GPIO_NUM_19;
    static const gpio_num_t intMpu = GPIO_NUM_25;

    static const gpio_num_t rstRtc = GPIO_NUM_15;

    static const gpio_num_t sw0 = GPIO_NUM_18;
    static const gpio_num_t encA = GPIO_NUM_5;
    static const gpio_num_t encB = GPIO_NUM_17;

    static const gpio_num_t RxGps = GPIO_NUM_16;
    static const gpio_num_t TxGps = GPIO_NUM_4;

    static const gpio_num_t espShutdown = GPIO_NUM_0;

    static const gpio_num_t TX485 = GPIO_NUM_2;
    static const gpio_num_t RX485 = GPIO_NUM_27;
    static const gpio_num_t mode485 = GPIO_NUM_13;

    static const gpio_num_t ledShutdown = GPIO_NUM_12;
    static const gpio_num_t ws2812 = GPIO_NUM_14;

    static const gpio_num_t lock = GPIO_NUM_26;
}
