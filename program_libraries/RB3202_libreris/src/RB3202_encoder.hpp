#pragma once

class RB3202_encoder
{
private:
    int enc[2];

    void enc0_calculate();
    void enc1_calculate();

    void sed_pins_encoder0();
    void sed_pins_encoder1();
    
public:
    RB3202_encoder();
    
    void sed_encoder();
    int read_encoder(bool);

    ~RB3202_encoder();
};
