#include "mbed.h"
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
DigitalIn switchinput(SW2);


int main() {
	int onesec = 1000;
    while(1) {
        if (switchinput==1) { //test value of switchinput
//execute following block if switchinput is 1
          redLED = 1; // flash red led
          wait_ms(onesec);
          redLED = 0;
          wait_ms(onesec);
     } //end of if
   else { //here if switchinput is 0
      greenLED = 1; // flash green led
      wait_ms(onesec);
      greenLED = 0;
      wait_ms(onesec);
     } //end of else
    } //end of while(1)
   } //end of main


