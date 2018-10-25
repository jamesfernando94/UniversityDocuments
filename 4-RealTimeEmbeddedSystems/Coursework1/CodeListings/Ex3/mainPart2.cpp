#include "mbed.h"
DigitalOut d0PowerOut(PTC16);
DigitalIn switchinput(SW2);


int main() {
    int OneHundredHzWait = 10;
    int TwoHundredHzWait = 5;
    while(1) {
        if (switchinput==1) { //test value of switchinput
//execute following block if switchinput is 1
          d0PowerOut = 1; // flash red led
          wait_ms(TwoHundredHzWait);
          d0PowerOut = 0;
          wait_ms(TwoHundredHzWait);
     } //end of if
   else { //here if switchinput is 0
      d0PowerOut = 1; // flash green led
      wait_ms(OneHundredHzWait);
      d0PowerOut = 0;
      wait_ms(OneHundredHzWait);
     } //end of else
    } //end of while(1)
   } //end of main


