#include "mbed.h" //include the mbed header file as part of this program
// program variable myled is created, and linked with mbed LED2

DigitalOut myled(LED4); // Creates a DigitalOut obejct for LED4 and allows for control over the LED4 Device

int main() { //the function starts here
     while (1) { //a continuous loop is created
        myled = 1; //switch the led off, by setting the output to logic 1
        wait_ms(250); //wait 1/4 seconds
        myled = 0; //switch the led on
        wait_ms(250); //wait 1/4 seconds
     } //end of while loop
} //end of main function