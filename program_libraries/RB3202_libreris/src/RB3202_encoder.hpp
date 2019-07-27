#pragma once

class RB3202_encoder
{
    friend class RB3202_PID;
protected:
    static int enc[2];
    
private:
    
    static int plan_position[2];
    static int motor_power[2];
    static bool driver[2];

    static void enc0_calculate();
    static void enc1_calculate();

    void set_pins_encoder0();
    void set_pins_encoder1();

    void set_encoder();

public:
    RB3202_encoder();

    int read_encoder(bool);
    void motor_go_position(int, int, int, int, int);

    ~RB3202_encoder();
};