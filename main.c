#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

void checkswitch () {
	
}
void checknum(int *value1, int *value2, int *value3, int *value4, int n){
	int i;
	char word[5];
	strcpy(word, "00:00");
	for (i=0;i<10;i++){
		if (*value1 == i){
			switch (n){
				case 1:
					LCD_Cmd(clear_display);
					word[4] = *value1 + '0';
					LCD_String(word);
					break;	
				case 2:
					LCD_Cmd(clear_display);
					word[4] = *value2 + '0';
					word[3] = *value1 + '0';
					LCD_String(word);
					break;
				case 3:
					LCD_Cmd(clear_display);
					word[4] = *value3 + '0';
					word[3] = *value2 + '0';
					word[1] = *value1 + '0';
					LCD_String(word);
					break;
				case 4:
					LCD_Cmd(clear_display);
					word[4] = *value4 + '0';
					word[3] = *value3 + '0';
					word[1] = *value2 + '0';
					word[0] = *value1 + '0';
					LCD_String(word);
					break;
		}
	}
}
	}

void D_Key (const char D){
		int value1 = 0,value2 = 0,value3 = 0,value4 = 0,i;
		if (!strcmp(D, "D")){
			return;
		}
		LCD_String("Cooking Time?");
		value1 = keypad_getkey() - '0';
		checknum(&value1,&value2,&value3,&value4,1);
		
		
}

int main(void)
{
	char string;
	
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
		string = 0;
	}

}

