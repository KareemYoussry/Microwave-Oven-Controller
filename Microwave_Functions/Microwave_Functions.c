#include "tm4c123gh6pm.h"
#include "../LCD/LCD.h"
#include "../keypad/keypad.h"
#include "Microwave_Functions.h"
#include "../CONDITIONS_FUNCTIONS/CONDITION_FUNCTIONS.h"
extern volatile unsigned char flag;
extern volatile unsigned char falling_edges;
unsigned char button_in2;
unsigned char button_in1;
extern volatile unsigned char Dflag; 


//Counter in minutes and seconds (making the count down appear in the LCD)
//sec[]: 2d-array:{tens of seconds, ones of seconds} as this {5,9} = 59 second
//min[]: 2d-array:{tens of minutes, ones of minutes} as this {1,5} = 15 min
// send the numbers as integers not ascii


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


void popCorn(void){
	unsigned char mins[2] = {0, 0},sec[2]={5,0};
	
	LCD_Cmd(clear_display);
	LCD_StringPos("Popcorn", 1, 0);
	do{
		button_in2 = sw2_input();
  }while(button_in2);
	flag = 0;
	LCD_StringPos("Time: ", 2, 0);
	leds_on();

	LCD_CountDown(sec,mins);
	
	LCD_Cmd(clear_display);
}

void Beef(void){
	unsigned char secs [2],mins [2]; // declaring array for seconds and minutes;
	unsigned char weight = 0;
	int time = 0;
	unsigned char input;
	LCD_StringPos("Beef weight?",1,0); 
	while(1){
		input = keypad_getkey(); 
		if (input>'0'&&input<='9'){
			input = keypad_getkey(); 
			Systick_Wait_ms(250);
			break; 
		}
		else {
			LCD_StringPos("Err", 2, 0);
			Systick_Wait_ms(2000); 
			LCD_Cmd(clear_display);
		}
	}
	
	LCD_Cmd(SecondRow);
	LCD_Write_Char(input);
	Systick_Wait_ms(2000);
	flag = 0;
	time = 30 * (input - '0');
	mins[0] = 0;
	mins[1] = time /60;
	secs[0] = (time%60) / 10 ;
	secs[1] = time - mins[1] * 60 - secs[0] * 10;
	
	LCD_CountDown (secs,mins);

}

void Chicken(void){
	unsigned char input=0;
	unsigned char mins[2];
	unsigned char secs[2];
	int time;
	
	LCD_StringPos("Chicken weight?",1,0); 
	
	do {
	input =keypad_getkey(); 
		if (input>'0'&&input<='9')
			break;
		else { 
			LCD_StringPos("Err", 2, 0);
			Systick_Wait_ms(2000); 
		}
	}while(1);
	LCD_Cmd(SecondRow);
	LCD_Write_Char(input);
	Systick_Wait_ms(2000);
	flag = 0;
	
	input -= 48 ;
	time = input*12; 

	
	mins[0]	=	0;							// calculate tens of minutes
	mins[1]	=	(time/60)%10 ;	// calculate units of minutes
	secs[0]	=	(time%60)/10;		// calculate tens of seconds 
	secs[1]	=	(time%60)%10 ;	// calculate units of seconds 
	LCD_CountDown(secs,mins);
}

void D_Key (void){
	unsigned char secs [2]; // declaring array for seconds
	unsigned char mins [2]; // declaring array for minutes
	unsigned char f30 = 0;		//flag to indicate over 30 minutes input
	unsigned char values[4]; // declaring array to use for input values
	int ite; // declaring iteration variable
	LCD_StringPos("Cooking Time?", 1, 0); // Displaying Cooking Time on LCD
	for (ite = 0 ; ite <4 ; ite++){  // Iterating to get values and print them on LCD
		if(Dflag == 0)
			ite = 0;
		do{
			values[ite] = keypad_getkey(); // Get value
		}while (values[ite] < '0' && values[ite] > '9');
		Systick_Wait_ms(250);
		f30 = checknum(values,ite);
		if(f30){
			flag = 2;
			return;
		}
	}	
	mins [0] = values[0]-48;
	mins [1] = values[1]-48;
	secs [0] = values[2]-48;
	secs [1] = values[3]-48;
	flag = 0;
	do{
		button_in2 = sw2_input();
	}while(button_in2);

	Dflag = 0;
	LCD_CountDown (secs,mins);
}

char checknum(unsigned char values [], int n){
	char word[5] = "00:00";
			switch (n){
				case 0: // first case: first digit is entered
					word[4] = values[0];
					LCD_StringPos(word,2,0);
					break;	
				case 1: // Second case: second digit is entered
					word[4] = values[1];
					word[3] = values[0];
					LCD_StringPos(word,2,0);
					break;
				case 2: // Third case: third digit is entered
					word[4] = values[2];
					word[3] = values[1];
					word[1] = values[0];
					LCD_StringPos(word,2,0);
					break;
				case 3: // Fourth case: fourth digit is entered
					if ((values[0] >='3') && (values[1] > '0')&&(values[2] > '0')&&(values[3] > '0'))
						return 1;
					word[4] = values[3];
					word[3] = values[2];
					word[1] = values[1];
					word[0] = values[0];
					LCD_StringPos(word,2,0);
					break;
		}
			return 0;
}