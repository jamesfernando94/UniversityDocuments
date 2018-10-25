#include "mbed.h"

DigitalOut myled(LED1);
DigitalOut yourled(LED2);

int main() {
  char i=0; //declare variable i, and set to 0
  while(1){ //start endless loop
  while(i<5) { //start first conditional while loop
     myled.write(1);
     wait(0.2);
     myled.write(0);
     wait(0.2);
     i++; //increment i
  } //end of first conditional while loop
  while(i>0) { //start second conditional loop
     yourled.write(1);
     wait(0.2);
     yourled.write(0);
     wait(0.2);
     i--;
  }
  break;
     } //end infinite loop block
} //end of main


