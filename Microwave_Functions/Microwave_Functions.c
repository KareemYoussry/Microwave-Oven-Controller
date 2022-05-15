#include "tm4c123gh6pm.h"
#include "../LCD/LCD.h"
#include "../keypad/keypad.h"
#include "Microwave_Functions.h"

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

void checknum(unsigned char values [4], int n){
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
					if (values[0] >=3 && values[1] > 0)
						LCD_StringPos("Error",2,0);  // checking if the minutes are less than or equal 30 minutes
					
					word[4] = values[3];
					word[3] = values[2];
					word[1] = values[1];
					word[0] = values[0];
					LCD_StringPos(word,2,0);
					break;
		}
	}

void D_Key (void){
			unsigned char values[4];
			int ite; // declaring array to use as time
		LCD_StringPos("Cooking Time?", 1, 0); // Displaying Cooking Time on LCD
		for (ite = 0 ; ite <4 ; ite++){  // Iterating to get values and print them on LCD
			do{
				values[ite] = keypad_getkey(); // Get value
			}
			while (values[ite] >= '0' && values[ite] <= '9');
				checknum(&values[ite],ite);
		}
		if ((GPIO_PORTF_DATA_R&0x01) != 0x01) 
			LCD_Cmd(clear_display);
		if ((GPIO_PORTF_DATA_R&0x10) != 0x10) {
			unsigned char secs [2]; // declaring array for seconds
			unsigned char mins [2]; // declaring array for minutes
			secs [0] = values[2];
			secs [1] = values[3];
			mins [0] = values[0];
			mins [1] = values[1];
			LCD_CountDown (secs,mins);
	}
}

	