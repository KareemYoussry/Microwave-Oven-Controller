#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"


int main(void)
{
	char string;
	int i = 0, j = 0;
	LCD_Init();
	keypad_Init();

	LCD_Write_Char('X');
	LCD_String("Hello!");

	Systick_Wait_ms(1000);
	LCD_Cmd(clear_display);
	
	while (1)
	{
		i++;
		string = keypad_getkey();
		LCD_Write_Char(string);
		
		Systick_Wait_ms(250);
		if(i > 15)
		{
			for(j = 0; j<24;j++)
				LCD_Write_Char(' ');
			i = 0;
		}
		string = 0;
	}

}

