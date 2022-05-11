#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"

int main(void)
{
	LCD_Init();
	
	
	while (1)
	{
		LCD_String("Hello, Someone!");
	}
	
}

