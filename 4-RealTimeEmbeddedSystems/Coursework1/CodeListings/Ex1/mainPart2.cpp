#include "mbed.h" //include the mbed header file as part of this program
// program variable myled is created, and linked with mbed LED2

DigitalOut myledr(LED1); // Creates a DigitalOut obejct for LED4 and allows for control over the LED4 Device
DigitalOut myledg(LED2);
DigitalOut myledb(LED3);

int main() { //the function starts here
     while (1) { //a continuous loop is created
        myledr = 1; //switch the led off, by setting the output to logic 1
        myledg = 1;
        myledb = 1;
        wait_ms(250); //wait 1/4 seconds
        myledr = 0; //switch the led on
        myledg = 0; 
        myledb = 0; 
        wait_ms(250); //wait 1/4 seconds
     } //end of while loop
} //end of main function

