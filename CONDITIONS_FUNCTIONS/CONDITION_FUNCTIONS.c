#include "CONDITION_FUNCTIONS.h"
#include "../timer/timer.h"
#include "../LCD/LCD.h"

void SystemInitf(){
SYSCTL_RCGCGPIO_R |=0x20;
while((SYSCTL_RCGCGPIO_R & 0x20)==0);
GPIO_PORTF_LOCK_R=0x4C4F434B;
GPIO_PORTF_CR_R |=0X0E;
GPIO_PORTF_AMSEL_R &= ~0X0E;
GPIO_PORTF_PCTL_R &= ~0X000FFFFF;
GPIO_PORTF_AFSEL_R &= ~0X01F;
GPIO_PORTF_DIR_R =0X0C;
GPIO_PORTF_DEN_R =0X1F;
GPIO_PORTF_PUR_R 	=0X11;
GPIO_PORTF_DATA_R = 0X11;//SW1 AND SW2 UNPRESSED SW3 PRESSED (OPEN DOOR)
}

void pause(){
	int j;
while(((GPIO_PORTF_DATA_R & 0X10)==0)||((GPIO_PORTF_DATA_R & 0X02)==0)){
	if(((GPIO_PORTF_DATA_R & 0X01)==0)&&((GPIO_PORTF_DATA_R & 0X02)==1))break;
	
	
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

unsigned char sw1_input(){
return GPIO_PORTF_DATA_R &0X10;

}

unsigned char sw2_input(){
return GPIO_PORTF_DATA_R &0X1;
}






