#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"

int main(void)
{
	char c;
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
		c = keypad_getkey();
		LCD_Write_Char(c);
		
		Systick_Wait_ms(250);

		c = 0;
	}

}
