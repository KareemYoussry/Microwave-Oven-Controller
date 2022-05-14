#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "Cooking.h"


int main(void)
{
	char c;
	int i = 0, j = 0;
	LCD_Init();
	keypad_Init();
	LCD_String("tetfa7y eh?");
		
	
	Systick_Wait_ms(1000);
	LCD_Cmd(clear_display);
	
	while (1)
	{
		i++;
		c = keypad_getkey();
		LCD_Write_Char(c);
		Systick_Wait_ms(250);
		if(c == 65)
			popCorn();
			
	}

}
