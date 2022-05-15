#include "tm4c123gh6pm.h"
#include "../LCD/LCD.h"
#include "../keypad/keypad.h"
#include "Microwave_Functions.h"
#include "stdlib.h"

void popCorn(void){
	unsigned char mins[2] = {0, 1},sec[2]={0,0};
	
	LCD_Cmd(clear_display);
	LCD_StringPos("Popcorn", 1, 0);
	LCD_StringPos("Time: ", 2, 0);
	
	LCD_CountDown(sec,mins);
	LCD_Cmd(clear_display);
	LCD_String("Done!");
	Systick_Wait_ms(3000);
	
	LCD_Cmd(clear_display);
}
void chiken(void){
	char input=0;
	LCD_StringPos("chiken weight!",1,0); 
	
	do {
	input =keypad_getkey(); 
		if (input>'0'&&input<='9')
			break;  
		else { 
			LCD_StringPos("Err", 2, 0);
			Systick_Wait_ms(2000); 
		}
		
	}while(1);
		input -= 48 ;
	int time;
	time = input*12; 
	unsigned char mins[2]={0};
	unsigned char secs[2]={0}; 
	mins[0]=time/600 ; // calculate tens of minutes
	mins[1]=(time/60)%10 ; // calculate units of minutes
	secs[0]=(time%60)/10; // calculate tens of seconds 
	secs[1]=(time%60)%10 ; // calculate units of seconds 
	LCD_CountDown(mins,secs);
	
}

void Beef(void){
	char input=0;
	LCD_StringPos("Beef weight!",1,0); 
	
	do {
	input =keypad_getkey(); 
		if (input>'0'&&input<='9')
			break;  
		else { 
			LCD_StringPos("Err", 2, 0);
			Systick_Wait_ms(2000); 
		}
		
	}while(1);
		input -= 48 ;
	int time;
	time = input*30; 
	unsigned char mins[2]={0};
	unsigned char secs[2]={0}; 
	mins[0]=time/600 ; // calculate tens of minutes
	mins[1]=(time/60)%10 ; // calculate units of minutes
	secs[0]=(time%60)/10; // calculate tens of seconds 
	secs[1]=(time%60)%10 ; // calculate units of seconds 
	LCD_CountDown(mins,secs);


//Counter in minutes and seconds (making the count down appear in the LCD)
//sec[]: 2d-array:{tens of seconds, ones of seconds} as this {5,9} = 59 second
//min[]: 2d-array:{tens of minutes, ones of minutes} as this {1,5} = 15 min

void LCD_CountDown(unsigned char sec[],unsigned char min[])
{
	unsigned char Mins = min[0];
	for(Mins = min[0]; min[0] <= Mins;sec[1]--)
	{
		LCD_Cmd(SecondRow + 6);

		//displaying time in this format XX:XX
		LCD_Write_Char(min[0]+48);	//Writes the ASCII form of the minute tens
		LCD_Write_Char(min[1]+48);	//Writes the ASCII form of the minute ones
		LCD_Write_Char(':');
		LCD_Write_Char(sec[0]+48);	//Writes the ASCII form of the second tens
		LCD_Write_Char(sec[1]+48);	//Writes the ASCII form of the second ones

		Systick_Wait_ms(1000);  //counting down time each sec

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
	