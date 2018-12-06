/* Emulating a USB mouse */
#include "mbed.h"           // include mbed library
#include "USBMouse.h"       // include USB Mouse library
USBMouse mouse;             // define USBMouse interface

int main()
{
    while (1)
    {
        mouse.scroll(1); // scroll page by parameter
        wait(0.2);
    }
}
