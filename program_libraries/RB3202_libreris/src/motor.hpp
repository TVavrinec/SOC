#include <Arduino.h>

class motor
{
private:
    void sed_motor_pin();
    void sed_motor_pins();
    void motor_start_working();
public:
    void sed_motor();
    void motors_power(int power_0, int power_1);
    void motor_power(bool motor, int power);
    void stop();
    void stop(bool motor);
    ~motor();
};