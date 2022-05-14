#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "Cooking.h"

void popCorn(void){
	unsigned char mins[2] = {0, 2},sec[2]={0,5};
	LCD_Cmd(clear_display);
	LCD_Cmd(FirstRow);
	LCD_String("Popcorn");
	LCD_Cmd(SecondRow);
	LCD_String("time: ");
	LCD_CountDown(sec,mins);
	LCD_Cmd(clear_display);
	LCD_String("Done!");
	Systick_Wait_ms(3000);
	LCD_Cmd(clear_display);
}


//Counter in minutes and seconds (making the count down appear in the LCD)
//sec[]: 2d-array:{tens of seconds, ones of seconds} as this {5,9} = 59 second
//min[]: 2d-array:{tens of minutes, ones of minutes} as this {1,5} = 15 min


void LCD_CountDown(unsigned char sec[],unsigned char min[])
{
	unsigned char Mins = min[0];
	for(Mins = min[0]; min[0] <= Mins;sec[1]--)
	{
		LCD_Cmd(SecondRow+6);				
		
		//displaying time in this format XX:XX
		LCD_Write_Char(min[0]+48);	
		LCD_Write_Char(min[1]+48);
		LCD_Write_Char(':');
		LCD_Write_Char(sec[0]+48);
		LCD_Write_Char(sec[1]+48);
		
		Systick_Wait_ms(300);  //counting time down each sec
		
		//to be a timer
		if(sec[1]<1 ||sec[1] >9)
		{
			sec[1] = 10;
			sec[0]--;
		}
		if(sec[0] >5)
		{
			sec[0] = 5;
			min[1]--;
		}
		if(min[1] >9)
		{
			min[1] = 9;
			min[0]--;
		}
	}
}
	