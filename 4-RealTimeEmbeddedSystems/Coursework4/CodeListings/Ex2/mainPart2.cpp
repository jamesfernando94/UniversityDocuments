/*2 PWM values generated in turn, with full on and off included for comparison. */
#include "mbed.h"
PwmOut motor(PTD3);

int main()
{
    while(1) {
        motor.period_us(1000);
        motor = 0; //motor switched off for 3 secs
        wait (3);
        motor = 0.6; // 60% duty cycle
        wait(3);
        motor = 0.95; // 95% duty cycle
        wait(3);
        motor = 1; //motor switched fully on for 3 secs
        wait (3);
    }
}