#include "mbed.h"

PwmOut PWM1(PTC10); //create a PWM output called PWM1 on pin PTC10

int main()
{
    PWM1.period(0.010); // set PWM period to 10 ms
    PWM1=0.8; // set duty cycle to 80%
}
