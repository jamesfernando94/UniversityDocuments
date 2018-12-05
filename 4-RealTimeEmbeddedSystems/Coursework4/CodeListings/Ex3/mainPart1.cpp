/* Emulating a USB mouse */
#include "mbed.h"			// include mbed library
#include "USBMouse.h"		// include USB Mouse library
USBMouse mouse;				// define USBMouse interface
int dx[] = {40, 0, -40, 0}; // relative x position coordinates
int dy[] = {0, 40, 0, -40}; // relative y position coordinates

int main()
{
	while (1)
	{
		for (int i = 0; i < 4; i++)
		{							  // scroll through position coordinates
			mouse.move(dx[i], dy[i]); // move mouse to coordinate
			wait(0.2);
		}
	}
}
