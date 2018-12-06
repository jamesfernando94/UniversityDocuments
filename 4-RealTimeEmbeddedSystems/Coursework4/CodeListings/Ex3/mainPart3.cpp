/* Emulating a USB mouse */
#include "mbed.h"           // include mbed library
#include "USBMouse.h"       // include USB Mouse library
USBMouse mouse;             // define USBMouse interface
InterruptIn leftButton(SW2);
InterruptIn rightButton(SW3);

void LeftDown();
void LeftUp();
void RightDown();
void RightUp();

int main()
{
    leftButton.fall(&LeftDown);
    leftButton.rise(&LeftUp);
    rightButton.fall(&RightDown);
    rightButton.rise(&RightUp);
    
    while(1){wait(1);}
}

void LeftDown(){
    mouse.press(MOUSE_LEFT);
}

void LeftUp(){
    mouse.release(MOUSE_LEFT);
}

void RightDown(){
    mouse.press(MOUSE_RIGHT);
}

void RightUp(){
    mouse.release(MOUSE_RIGHT);    
}