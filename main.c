#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "./Microwave_Functions/Microwave_Functions.h"

int main(void)
{
	char c;
	int i = 0, j = 0;
	LCD_Init();
	keypad_Init();
	LCD_String("Enter a Key");

<<<<<<< Updated upstream
	Systick_Wait_ms(3000);
=======
	Systick_Wait_ms(1000);
>>>>>>> Stashed changes
	LCD_Cmd(clear_display);

	while (1)
	{
		i++;
		c = keypad_getkey();
		LCD_Write_Char(c);
		Systick_Wait_ms(250);
<<<<<<< Updated upstream
			if(c == 65)
				popCorn();
=======
		if(c == 65)
			popCorn();
>>>>>>> Stashed changes
	}
}
