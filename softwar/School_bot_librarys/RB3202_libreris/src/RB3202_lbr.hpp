#pragma once

#include <Arduino.h>

#include "RB3202_pinout.hpp"
#include "RB3202_set.hpp"
#include "RB3202_driver.hpp"
#include "RB3202_encoder.hpp"
#include "RB3202_PID.hpp"

rb_periphery ui;
RB3202_driver drive;
RB3202_PID pid;

using namespace RB3202;