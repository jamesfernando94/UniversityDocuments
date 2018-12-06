/*2 PWM values generated in turn, with full on and off included for 
comparison. for not using PWM function directly */
#include "mbed.h"
DigitalOut motor(PTD3);
int i;
int main() {
   while(1) {
      motor = 0; //motor switched off for 3 secs
      wait (3);
      for (i=0;i<3000;i=i+1) { //3000 PWM cycles, medium-high duty cycle
        motor = 1;
        wait_us(600); //output high for 600us
        motor = 0;
        wait_us(400); //output low for 400us
      }
      for (i=0;i<3000;i=i+1) { //3000 PWM cycles, high duty cycle
        motor = 1;
        wait_us(950); //output high for 950us
        motor = 0;
        wait_us(50); //output low for 50us
      }
     motor = 1; //motor switched fully on for 3 secs
     wait (3);
  }
}