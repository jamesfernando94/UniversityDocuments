/* External input causes interrupt, while led flashes*/
#include "mbed.h"
InterruptIn button(SW2); //define and name the interrupt input
DigitalOut led(LED1); //red
DigitalOut flash(LED2); //green

void ISR1()   //this is the response to interrupt, i.e. the ISR
{
    led = !led;
}

void ISR2()
{
    flash = !flash;
}

int main()
{
    button.rise(&ISR1); // attach the address of the ISR function to the interrupt falling edge
    button.fall(&ISR2);
    while(1) { // continuous loop, ready to be interrupted
        wait(10);
    }
}
