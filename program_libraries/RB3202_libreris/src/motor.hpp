#include <Arduino.h>

class driver
{
private:
    void sed_motor_pwm_pin(gpio_num_t pin, uint8_t channel);
    void sed_all_motor_pins();
    
    void go_forward(bool motor, float pwm);
    void go_back(bool motor, float pwm);
    void sed_pwm(bool motor, bool direction, float pwm);
    void IRAM_ATTR onTimer();
    
    int percent_to_pwm(float percent);

public:
    void motor_start_working();
    void stop();
    void sed_motor();
    void power(float power_0, float power_1);
    void rotate(int rotate_0, int rotate_1);   
    void stop(bool motor);
    void sed_PID_timer();
    
    ~driver();
};