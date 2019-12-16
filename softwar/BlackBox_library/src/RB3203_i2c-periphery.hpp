#pragma once

#include <driver/i2c.h>
#include "RB3203_Pinout.hpp"

class i2cPeriphery
{
public:
    i2cPeriphery(gpio_num_t sda,gpio_num_t scl);

    int readAcceleration(int8_t axis, int adres = 0b1101000);
};