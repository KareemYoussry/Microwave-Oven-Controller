#include "Conditions_Functions.h"
#include "../timer/timer.h"
#include "../LCD/LCD.h"

volatile unsigned char falling_edges;
volatile unsigned char flag; //a flag to exit the interrupt in the begginning
volatile unsigned char SW3_Flag;

void portEinit(){
	SYSCTL_RCGCGPIO_R |=0x10;
	while((SYSCTL_RCGCGPIO_R & 0x10)==0);
	GPIO_PORTE_CR_R |=0X30;
	GPIO_PORTE_AMSEL_R &= ~0X30;
	GPIO_PORTE_PCTL_R &= ~0XFF0000;
	GPIO_PORTE_AFSEL_R &= ~0X30;
	GPIO_PORTE_DIR_R |= 0X20;// 
	GPIO_PORTE_DEN_R |= 0X30;
	GPIO_PORTE_PUR_R 	|= 0X10;
	GPIO_PORTE_DATA_R |= 0X10;//DOOR CLOSED INITIALLY
	GPIO_PORTE_IS_R &= ~0X10;
	GPIO_PORTE_IBE_R &= ~0X10;
	GPIO_PORTE_IEV_R &= ~0X10;
	GPIO_PORTE_ICR_R = 0X10;
	GPIO_PORTE_IM_R |= 0X10;
	NVIC_PRI1_R =((NVIC_PRI1_R) & (0XFFFFFF00))|0X00000010;
	NVIC_EN0_R=0X10;
}



void GPIOE_Handler()
{
	GPIO_PORTE_ICR_R =0X10;
	if(SW3_Flag == 0)
		return;
	while((GPIO_PORTE_DATA_R &0X10)==0){
		GPIO_PORTF_DATA_R ^= 0X0E;
		Systick_Wait_ms(500);
	}
	GPIO_PORTF_DATA_R &= ~0X0E;
	

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
	GPIO_PORTF_DATA_R |= 0X10;//SW1 AND SW2 UNPRESSED SW3 PRESSED (OPEN DOOR)
	GPIO_PORTF_IS_R &= ~0X10;
	GPIO_PORTF_IBE_R &= ~0X10;
	GPIO_PORTF_IEV_R &= ~0X10;
	GPIO_PORTF_ICR_R =0X10;
	GPIO_PORTF_IM_R |=0X10;
	NVIC_PRI7_R=((NVIC_PRI7_R) & (0XFF00FFFF))|0X00A00000;
	NVIC_EN0_R=0X40000000;
	//GPIO_PORTF_MIS_R |=0X10;
}

void  GPIOF_Handler() 
{
	if((GPIO_PORTF_MIS_R & 0X10)==0X10){	
		int z = 0;
		GPIO_PORTF_ICR_R |= 0X10;
		if(flag >= 1)
			return;
		if(falling_edges >= 2){
			GPIO_PORTF_DATA_R &= ~0X0E;
			return;
		}
		GPIO_PORTF_DATA_R ^= 0X0E;
		falling_edges = 1;
		Systick_Wait_ms(200);
		do{
			z++;
			Systick_Wait_1ms();
			if(z>=500){
				GPIO_PORTF_DATA_R ^= 0X0E;
				z = 0;
			}
		}while((GPIO_PORTF_DATA_R &0X1)!=0 && (GPIO_PORTF_DATA_R &0X10) != 0);
		if((GPIO_PORTF_DATA_R &0X10)==0){
			falling_edges++;
			GPIO_PORTF_DATA_R &= ~0X0E;
		}
		else if((GPIO_PORTF_DATA_R &0X1) == 0)
			
			GPIO_PORTF_DATA_R &= ~0X0E;
	}
}



void stop_cooking(){
	LCD_Cmd(clear_display);
}


void leds_on(){
	GPIO_PORTF_DATA_R |= 0X0E;
}


void leds_off(){
		GPIO_PORTF_DATA_R &= ~0X0E;
}

	
void leds_blink(){
	int i;
	for(i=0;i<6;i++){		
		GPIO_PORTF_DATA_R ^= 0X0E;
		Systick_Wait_ms(500);
	}
}


void buzzer_on(){
	GPIO_PORTE_DATA_R |= 0X20;
}

void buzzer_off(){
	GPIO_PORTE_DATA_R &= ~0X20;
}
unsigned char sw1_input(){
	return GPIO_PORTF_DATA_R &0X10;
}

unsigned char sw2_input(){
	return GPIO_PORTF_DATA_R &0X1;
}