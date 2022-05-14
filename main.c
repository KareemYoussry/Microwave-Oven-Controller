#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "./Microwave Functions/Microwave Functions.h"


int main(void)
{
	char c;
	int i = 0, j = 0;
	LCD_Init();
	keypad_Init();
	LCD_String("Enter a Key");

	Systick_Wait_ms(3000);
	LCD_Cmd(clear_display);

	while (1)
	{
		i++;
		c = keypad_getkey();
		LCD_Write_Char(c);
		Systick_Wait_ms(250);
			if(c == 65 )
				popCorn();
	}

}
