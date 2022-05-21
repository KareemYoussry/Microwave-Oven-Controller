#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "./CONDITIONS_FUNCTIONS/CONDITION_FUNCTIONS.h"
#include "./Microwave_Functions/Microwave_Functions.h"

//unsigned char button_in2;
//unsigned char button_in1;
 
unsigned char button_in2;
unsigned char button_in1;
 volatile unsigned char falling_edges;
 volatile unsigned char Flag_A=0;
 volatile unsigned char Flag_B=0;
 volatile unsigned char Flag_C=0;
 volatile unsigned char Flag_D=0;

void popCorn(void){
	unsigned char mins[2] = {0, 1},sec[2]={0,0};
	Flag_A=1;
	
	LCD_Cmd(clear_display);
	LCD_StringPos("Popcorn", 1, 0);
	do
        {
            button_in2 = sw2_input();
        }while(button_in2);
				leds_on();
	LCD_StringPos("Time: ", 2, 0);
	Flag_A=0;
	LCD_CountDown(sec,mins);
	Flag_A=1;			
	LCD_Cmd(clear_display);
	LCD_String("Done!");
	leds_blink();
	buzzer_on();
	Systick_Wait_ms(3000);
	
	LCD_Cmd(clear_display);
	
  Flag_A=0;
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
		
		if (falling_edges == 3)
			return;

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
	unsigned char secs [2]; // declaring array for seconds
	unsigned char mins [2]; // declaring array for minutes
			unsigned char values[4];
			int ite; // declaring array to use as time
	    falling_edges=1;
		LCD_StringPos("Cooking Time?", 1, 0); // Displaying Cooking Time on LCD
		for (ite = 0 ; ite <4 ; ite++){  // Iterating to get values and print them on LCD
			do{
				values[ite] = keypad_getkey(); // Get value
			}
			while (values[ite] >= '0' && values[ite] <= '9');
				checknum(&values[ite],ite);
		}
	//	if ((GPIO_PORTF_DATA_R&0x01) != 0x01) 
		//	LCD_Cmd(clear_display);
	//	if ((GPIO_PORTF_DATA_R&0x10) != 0x10) {
		//	unsigned char secs [2]; // declaring array for seconds
			//unsigned char mins [2]; // declaring array for minutes
			secs [0] = values[2];
			secs [1] = values[3];
			mins [0] = values[0];
			mins [1] = values[1];
      falling_edges=0;
			LCD_CountDown (secs,mins);
		  LCD_Cmd(clear_display);
	  
	   leds_blink();
	   buzzer_on();
	   LCD_String("Done!");
		
		 Systick_Wait_ms(3000);
	
	   LCD_Cmd(clear_display);
	
	//}
}


void portEinit(){
SYSCTL_RCGCGPIO_R |=0x10;
while((SYSCTL_RCGCGPIO_R & 0x10)==0);
GPIO_PORTE_CR_R |=0X30;
GPIO_PORTE_AMSEL_R &= ~0X30;
GPIO_PORTE_PCTL_R &= ~0XFF0000;
GPIO_PORTE_AFSEL_R &= ~0X30;
GPIO_PORTE_DIR_R |=0X20;// 
GPIO_PORTE_DEN_R |=0X30;
GPIO_PORTE_PUR_R 	|=0X10;
GPIO_PORTE_DATA_R |= 0X10;//DOOR CLOSED INITIALLY
GPIO_PORTE_IS_R &= ~0X10;
GPIO_PORTE_IBE_R &= ~0X10;
GPIO_PORTE_IEV_R &= ~0X10;
GPIO_PORTE_ICR_R =0X10;
GPIO_PORTE_IM_R |=0X10;
NVIC_PRI1_R =((NVIC_PRI1_R) & (0XFFFFFF00))|0X00000020;
NVIC_EN0_R=0X10;
}


void GPIOE_Handler()
{
	GPIO_PORTE_ICR_R =0X10;
	while((GPIO_PORTE_DATA_R &0X10)==0)
	{
		GPIO_PORTF_DATA_R ^= 0X0C;
		Systick_Wait_ms(500);
	}
}


void portFinit(){
SYSCTL_RCGCGPIO_R |=0x20;
while((SYSCTL_RCGCGPIO_R & 0x20)==0);
GPIO_PORTF_LOCK_R=0x4C4F434B;
GPIO_PORTF_CR_R |=0X01F;
GPIO_PORTF_AMSEL_R &= ~0X01F;
GPIO_PORTF_PCTL_R &= ~0X000FFFFF;
GPIO_PORTF_AFSEL_R &= ~0X01F;
GPIO_PORTF_DIR_R |=0X0E;// possible edit
GPIO_PORTF_DEN_R |=0X1F;
GPIO_PORTF_PUR_R 	|=0X11;
GPIO_PORTF_DATA_R |= 0X11;//SW1 AND SW2 UNPRESSED SW3 PRESSED (OPEN DOOR)
GPIO_PORTF_IS_R &= ~0X10;
GPIO_PORTF_IBE_R &= ~0X10;
GPIO_PORTF_IEV_R &= ~0X10;
GPIO_PORTF_ICR_R =0X10;
GPIO_PORTF_IM_R |=0X10;
NVIC_PRI7_R=((NVIC_PRI7_R) & (0XFF00FFFF))|0X00A00000;
NVIC_EN0_R=0X40000000;
}

/*void portDinit(){
SYSCTL_RCGCGPIO_R |=0x8;
while((SYSCTL_RCGCGPIO_R & 0x8)==0);
GPIO_PORTD_LOCK_R=0x4C4F434B;
GPIO_PORTE_CR_R |=0X03;
GPIO_PORTE_AMSEL_R &= ~0X03;
GPIO_PORTE_PCTL_R &= ~0X0FF;
GPIO_PORTE_AFSEL_R &= ~0X3;
GPIO_PORTE_DIR_R |=0X02;// 
GPIO_PORTE_DEN_R |=0X3;
GPIO_PORTE_PUR_R 	|=0X1;
GPIO_PORTE_DATA_R |= 0X01;//DOOR CLOSED INITIALLY
GPIO_PORTE_IS_R &= ~0X01;
GPIO_PORTE_IBE_R &= ~0X01;
GPIO_PORTE_IEV_R &= ~0X01;
GPIO_PORTE_ICR_R =0X01;
GPIO_PORTE_IM_R |=0X01;
NVIC_PRI0_R=((NVIC_PRI0_R) & (0X00FFFFFF))|0X00A00000;
NVIC_EN0_R=0X10;
}*/


void  GPIOF_Handler(void) 
{
	GPIO_PORTF_ICR_R |=0X10;
	
	falling_edges=falling_edges+1;
	
	if(Flag_A==1)
	{
		falling_edges=0;
	}
	
	
	
if(falling_edges==1)
	{
	pause();
	if(falling_edges ==1)
		{falling_edges=0;}
  }
	
	/*if(falling_edges==2)
	{
	LCD_Cmd(clear_display);
	}*/
	
	
}
	

void pause(){
	
do{
		GPIO_PORTF_DATA_R ^= 0X0E;
		 Systick_Wait_ms(500);
	if(sw1_input()==0)
		{  
			falling_edges = 2;
	     break;
	   
		}
	
	}while((sw2_input())!=0);
    
}


void stop_cooking()
{
LCD_Cmd(clear_display);
	
}


void leds_on(){
	
	GPIO_PORTF_DATA_R |= 0X0C;

}


void leds_off(){
	
	GPIO_PORTF_DATA_R &= ~0X0C;
	}

	
void leds_blink(){
	int i;
	for( i=0;i<6;i++){
		
	GPIO_PORTF_DATA_R ^= 0X0E;
		 Systick_Wait_ms(500);
		}
}


void buzzer_on(){
	GPIO_PORTE_DATA_R |=0X2;
	Systick_Wait_ms(3000);
	GPIO_PORTE_DATA_R &=~0X2;
}

void buzzer_off(){
	GPIO_PORTE_DATA_R &=~0X2;
}

unsigned char sw1_input(){
return GPIO_PORTF_DATA_R &0X10;

}

unsigned char sw2_input(){
return GPIO_PORTF_DATA_R &0X1;
}







	
int main(void)
{
    char c;
	
	
    portFinit();
    LCD_Init();
    keypad_Init();
	portEinit();

    LCD_String("Enter ");
    Systick_Wait_ms(3000);
    LCD_Cmd(clear_display);

    while (1)
    {
        c = keypad_getkey();
        if(!(c == 'A'|| c == 'B'||c == 'C'||c == 'D'))
            continue;
        LCD_Write_Char(c);
        Systick_Wait_ms(250);
       /* do
        {
            button_in2 = sw2_input();
        }while(button_in2);*/
 	
				//if((button_in2==0)&&(button_in1==0)){
				//leds_on();
        switch(c){
            case 'A':
                popCorn();
                
            break;

            case 'B':
               
                break;

            case 'C':
                
                break;

            case 'D':
							         D_Key();
               
                       break;
        }
        leds_off();
						 
			falling_edges=0;

    }
		
	}

//}
