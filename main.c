#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "./Microwave_Functions/Microwave_Functions.h"


void checknum(int values [4], int n){
	char word[5];
	strcpy(word, "00:00"); 
		if (!((isdigit (values[0]))  // checking if values entered are a number or not
			&& 	(isdigit (values[1]))
			&&	(isdigit (values[2]))
			&&	(isdigit (values[3]))  ))
				return;

			switch (n){
				case 0: // first case: first digit is entered
					word[4] = values[0] + '0';
					LCD_StringPos(word,2,0);
					break;	
				case 1: // Second case: second digit is entered
					word[4] = values[1] + '0';
					word[3] = values[0] + '0';
					LCD_StringPos(word,2,0);
					break;
				case 2: // Third case: third digit is entered
					word[4] = values[2] + '0';
					word[3] = values[1] + '0';
					word[1] = values[0] + '0';
					LCD_StringPos(word,2,0);
					break;
				case 3: // Fourth case: fourth digit is entered
					if (values[0] >=3 && values[1] > 0)
						LCD_StringPos("Error",2,0);  // checking if the minutes are less than or equal 30 minutes
					
					word[4] = values[3] + '0';
					word[3] = values[2] + '0';
					word[1] = values[1] + '0';
					word[0] = values[0] + '0';
					LCD_StringPos(word,2,0);
					break;
		}
	}

void D_Key (char D){
			int values[5],ite; // declaring array to use as time
//		if (!strcmp(D , "D")){  // checking if the key entered is D
//			return;
//		}
		LCD_StringPos("Cooking Time?", 1, 0); // Displaying Cooking Time on LCD
		for (ite = 0 ; ite <4 ; ite++){  // Iterating to get values and print them on LCD
			values[ite] = keypad_getkey() - '0'; // Get value
			checknum(&values[ite],ite);
		}
		if ((GPIO_PORTF_DATA_R&0x01) != 0x01) 
			LCD_Cmd(clear_display);
		if ((GPIO_PORTF_DATA_R&0x10) != 0x10) {
			unsigned char secs [2] = {values[2] + '0', values[3] + '0'}; // declaring array for seconds
			unsigned char mins [2] = {values[0] + '0', values[1] + '0'}; // declaring array for minutes
			LCD_CountDown (secs,mins);
	}
}

int main(void)
{	
	LCD_Init();
	keypad_Init();

	LCD_Write_Char('X');
	LCD_String("Hello!");

	Systick_Wait_ms(1000);
	LCD_Cmd(clear_display);
	
	while (1)
	{
		D_Key (keypad_getkey());
		Systick_Wait_ms(250);
	}

}

