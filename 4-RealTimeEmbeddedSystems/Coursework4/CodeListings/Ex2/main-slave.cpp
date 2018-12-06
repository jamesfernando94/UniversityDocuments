/* Sets the mbed up as Slave, and exchanges data with a Master,
sending its own switch positions, and displaying those of the Master. as SPI 
slave.*/
#include "mbed.h"
SPISlave ser_port(PTD2, PTD3, PTD1, PTD0);         // mosi, miso, sclk, ssel (fill by your own)
DigitalOut red_led(LED1);   //red led
DigitalOut green_led(LED2); //green led
DigitalIn switch_ip1(SW2);
DigitalIn switch_ip2(SW3);
char switch_word; //word we will send
char recd_val;    //value received from master

int main()
{
    //default formatting applied
    while (1)
    {
        //set up switch_word from switches that are pressed
        switch_word = 0xa0; //set up a recognizable output pattern
        if (switch_ip1 == 1)
            switch_word = switch_word | 0x01;
        if (switch_ip2 == 1)
            switch_word = switch_word | 0x02;
        if (ser_port.receive())
        {                                //test if data transfer has occurred
            recd_val = ser_port.read();  // Read byte from master
            ser_port.reply(switch_word); // Make this the next reply
        }
        // set leds according to incoming word from slave
        red_led = 0; //preset both to 0
        green_led = 0;
        recd_val = recd_val & 0x03; //AND out unwanted bits
        if (recd_val == 1)
        {
            red_led = 1;
            green_led = 0;
        }
        if (recd_val == 2)
        {
            red_led = 0;
            green_led = 1;
        }
        if (recd_val == 3)
        {
            red_led = 1;
            green_led = 1;
        }
    }
}