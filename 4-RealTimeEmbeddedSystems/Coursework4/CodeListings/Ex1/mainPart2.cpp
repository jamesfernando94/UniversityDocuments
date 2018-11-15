#include "mbed.h"

PwmOut PWM1(PTC10); //create a PWM output called PWM1 on pin PTC10

int main()
{
    PWM1.pulsewidth_ms(5); // set PWM period to 10 ms
    PWM1=0.5; // set duty cycle to 50%
}
