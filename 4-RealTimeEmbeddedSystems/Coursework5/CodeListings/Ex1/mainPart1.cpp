/* Sets up the mbed as SPI master, and continuously sends a single byte*/
#include "mbed.h"
SPI ser_port(PTD2, PTD3, PTD1); // mosi, miso, sclk
char switch_word ; //word we will send

int main()
{
    ser_port.format(8,0); // Setup the SPI for 8 bit data, Mode 0 operation
    ser_port.frequency(1000000); // Clock frequency is 1MHz
    while (1) {
        switch_word=0b10100001; // 0b means that the following number is in binary
        ser_port.write(switch_word); //send switch_word
        wait_us(50);
    }
}
