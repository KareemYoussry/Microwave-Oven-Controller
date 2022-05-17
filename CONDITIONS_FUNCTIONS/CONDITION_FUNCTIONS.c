#include "CONDITION_FUNCTIONS.h"
#include "../timer/timer.h"
#include "../LCD/LCD.h"

//volatile extern unsigned char falling_edges=0;
volatile unsigned char falling_edges;

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


void  GPIOF_Handler(void) 
{
	
	GPIO_PORTF_ICR_R =0X10;
	falling_edges=falling_edges+1;
if(falling_edges<=2){
if(falling_edges%2==1){
	do{
		GPIO_PORTF_DATA_R ^= 0X0C;
		 Systick_Wait_ms(500);
	}while((GPIO_PORTF_DATA_R &0X1)!=0);
}
	if(falling_edges%2==0)
{
LCD_Cmd(clear_display);
	

}
	
}}


/*void pause(){
	int j;
while(((GPIO_PORTF_DATA_R & 0X10)==0)||((GPIO_PORTF_DATA_R & 0X02)==0)){
	if(((GPIO_PORTF_DATA_R & 0X01)==0)&&((GPIO_PORTF_DATA_R & 0X02)==1))break;
	
	
	for( j=0;j<6;j++){
		
	GPIO_PORTF_DATA_R ^= 0X0C;
		 Systick_Wait_ms(500);
		}
	
}
	}*/

void stop_cooking()
{
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






