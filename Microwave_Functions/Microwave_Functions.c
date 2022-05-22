#include "tm4c123gh6pm.h"
#include "../LCD/LCD.h"
#include "../keypad/keypad.h"
#include "Microwave_Functions.h"
#include "../CONDITIONS_FUNCTIONS/CONDITION_FUNCTIONS.h"

extern volatile unsigned char falling_edges;
unsigned char button_in2;
unsigned char button_in1;

void popCorn(void){
	unsigned char mins[2] = {0, 0},sec[2]={5,0};
	
	LCD_Cmd(clear_display);
	LCD_StringPos("Popcorn", 1, 0);
	do{
		button_in2 = sw2_input();
  }while(button_in2);
	LCD_StringPos("Time: ", 2, 0);
	LCD_CountDown(sec,mins);
	
	LCD_Cmd(clear_display);
}


//Counter in minutes and seconds (making the count down appear in the LCD)
//sec[]: 2d-array:{tens of seconds, ones of seconds} as this {5,9} = 59 second
//min[]: 2d-array:{tens of minutes, ones of minutes} as this {1,5} = 15 min


void LCD_CountDown(unsigned char sec[],unsigned char min[])
{
	unsigned char Mins = min[0];
	for(Mins = min[0]; min[0] <= Mins && falling_edges!=2;sec[1]--)
	{
		LCD_Cmd(SecondRow + 6);

		//displaying time in this format XX:XX
		LCD_Write_Char(min[0]+48);	//Writes the ASCII form of the minute tens
		LCD_Write_Char(min[1]+48);	//Writes the ASCII form of the minute ones
		LCD_Write_Char(':');
		LCD_Write_Char(sec[0]+48);	//Writes the ASCII form of the second tens
		LCD_Write_Char(sec[1]+48);	//Writes the ASCII form of the second ones
		
		Systick_Wait_ms(300);  //counting down time each sec

		//to be a timer
		if(sec[1] < 1 || sec[1] > 9)
		{
			sec[1] = 10;
			sec[0]--;
		}
		if(sec[0] > 5)
		{
			sec[0] = 5;
			min[1]--;
		}
		if(min[1] > 9)
		{
			min[1] = 9;
			min[0]--;
		}
	}
}