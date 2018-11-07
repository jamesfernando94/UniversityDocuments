#include "mbed.h"
Timer timer_red; // define Timer with name "timer_red"
Timer timer_green;
Timer timer_blue;
Timer timer_red2;
DigitalOut red(LED1);
DigitalOut green(LED2);
DigitalOut blue(LED3);
DigitalOut red2(LED4);

void task_switch(DigitalOut led); //function prototypes

int main()
{
    timer_red.start(); //start the Timers
    timer_green.start();
    timer_blue.start();
    timer_red2.start();
    while (1) {
        if (timer_red.read()>0.2) { //test Timer value
            task_switch(red); //call the task if trigger time is reached
            timer_red.reset(); //and reset the Timer
        }
        if (timer_green.read()>0.3) {
            task_switch(green);
            timer_green.reset();
        }
        if (timer_blue.read()>0.4) {
            task_switch(blue);
            timer_blue.reset();
        }
        if (timer_red2.read()>0.5) {
            task_switch(red2);
            timer_red2.reset();
        }

    }
}

void task_switch(DigitalOut led)  //Switches the input led
{
    led = !led;
}