#pragma once

class RB3202_encoder
{
private:
    int enc[2];
    int plan_position[2];
    int motor_power[2];
    bool driver[2] = {false, false};

    void enc0_calculate();
    void enc1_calculate();

    void sed_pins_encoder0();
    void sed_pins_encoder1();

    void sed_encoder();

public:
    RB3202_encoder();

    int read_encoder(bool);
    void motor_go_position(int, int, int, int, int);

    ~RB3202_encoder();
};