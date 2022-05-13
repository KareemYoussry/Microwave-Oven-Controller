#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"


int main(void)
{
	char string[20];
	int count = 0;
	
	LCD_Init();
	keypad_Init();

	LCD_Write_Char('X');
	LCD_String("Hello!");

	Systick_Wait_ms(10000);

	while (1)
	{
		string[count] = keypad_getkey();
		LCD_Write_Char(string[count]);
		count++;
	}

}

