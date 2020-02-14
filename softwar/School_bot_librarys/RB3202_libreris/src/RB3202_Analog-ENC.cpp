#include "RB3202_Analog-ENC.hpp"

/*
AnalogEncoder::AnalogEncoder(gpio_num_t pin0, gpio_num_t pin1)
{
    new std::thread([&]()
    {
        pinA = pin0;
        pinB = pin1;
        sedPins(pinA, pinB);
        while(true)
        {
            int HallA = (analogRead(pinA)-korekceA1)*korekceB1;
            int HallB = (analogRead(pinB)-korekceA2)*korekceB2;
            if(asin(abs(HallA))<45)
            {
                if(HallA<HallB)
                {

                }
            }
        }
    });
}

esp_err_t AnalogEncoder::sedPins(gpio_num_t pin0, gpio_nou_t pin1)
{

}*/