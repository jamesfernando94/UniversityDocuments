#include "mbed.h"
#include "USBMouse.h"
#include "FXOS8700Q.h"

//I2C lines for FXOS8700Q accelerometer/magnetometer
FXOS8700Q_acc acc( PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1);

USBMouse mouse;
 
int main() 
{
    acc.enable();
    float faX, faY;
    int16_t x = 0;
    int16_t y = 0;
    
    while (1) 
    {
        acc.getX(&faX);
        acc.getY(&faY);
        x = 3*faX;
        y = 3*faY;
        
        mouse.move(x, y);
        wait(0.001);
    }
}