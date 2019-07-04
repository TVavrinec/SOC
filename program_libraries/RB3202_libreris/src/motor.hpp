#include <Arduino.h>

class driver
{
private:
    void sed_motor_pin(gpio_num_t pin, uint8_t channel);
    void sed_all_motor_pins();
    
    void go_forward(bool motor, int pwm);
    void go_back(bool motor, int pwm);
    void sed_pwm(bool motor, bool direction, int pwm);

    int percent_to_pwm(float percent);

public:
    void motor_start_working();
    void stop();
    void sed_motor();
    void power(int power_0, int power_1);
    void stop(bool motor);
    ~driver();
};