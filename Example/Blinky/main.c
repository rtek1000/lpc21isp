#include "lpc812.h"
void ConfigPins()
{
	// Disable SWDIO on pin 4 (PIO0_2)
	PINENABLE0 |= BIT3;
	// Make bit 2 an output
	GPIO_DIRP0 |= BIT2; 
}
void delay(int len)
{
	while(len--);
}
void main()
{
	ConfigPins();
	while(1)	
	{
		GPIO_B2 = 1;
		delay(500000);
		GPIO_B2 = 0; 
		delay(500000);
	}
}
