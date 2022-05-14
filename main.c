#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"


//		pf1 (red led)	connected to external swich sw3


void SystemInit(){
	
SYSCTL_RCGCGPIO_R |=0x20;
while((SYSCTL_RCGCGPIO_R & 0x20)==0);
GPIO_PORTF_LOCK_R=0x4C4F434B;
GPIO_PORTF_CR_R   |=0X01F;
GPIO_PORTF_AMSEL_R &= ~0X01F;
GPIO_PORTF_PCTL_R &= ~0X000FFFFF;
GPIO_PORTF_AFSEL_R   &= ~0X01F;
GPIO_PORTF_DIR_R |=0X06;
GPIO_PORTF_DEN_R  |=0X01F;
GPIO_PORTF_DATA_R &= ~0X01F;

}


void pause(){
	int j;
while(((GPIO_PORTF_DATA_R & 0X10)==0)||((GPIO_PORTF_DATA_R & 0X02)==0)){
	if(((GPIO_PORTF_DATA_R & 0X01)==0)&&((GPIO_PORTF_DATA_R & 0X02)==1))break;
	//Systick_Wait_1ms();
	
	for( j=0;j<6;j++){
		
	GPIO_PORTF_DATA_R ^= 0X0C;
		 Systick_Wait_ms(500);
		}
	
}
	}

	
void stop_cooking(){
	
LCD_Cmd(clear_display);
	
}


void leds_on(){
	//green and blue leds on
	GPIO_PORTF_DATA_R |= 0X0C;

}


void leds_off(){
	//green and blue leds off
	GPIO_PORTF_DATA_R &= ~0X0C;
	}

	
void leds_blink(){
	int i;
	for( i=0;i<6;i++){
		
	GPIO_PORTF_DATA_R ^= 0X0C;
		 Systick_Wait_ms(500);
		}
}


void buzzer_on(){
}






int main(void)
{
	char string;
	SystemInit();
	LCD_Init();
	keypad_Init();

	


				
	while (1)
	{
		string = keypad_getkey();
		LCD_Write_Char(string);
		Systick_Wait_ms(250);
		Systick_Wait_ms(1000);
	
		
		if(((GPIO_PORTF_DATA_R & 0X01)==0)){
	
	
		if(((GPIO_PORTF_DATA_R & 0X01)==0)&&((GPIO_PORTF_DATA_R & 0X02)==1)){
			
			switch(string){
				case 'A':{leds_on();
				
			leds_blink();}
					break;
				case 'B':{leds_on();
					
				
				
		leds_blink();}
					break;
			  case 'C':{leds_on();
				
		leds_blink();} 
					break;
				case 'D':{leds_on();
				
		 leds_blink();}
					break;}
			
			

    }
	
	
	}
}
	
	
	
}




