#include "CONDITION_FUNCTIONS.h"
#include "../timer/timer.h"
#include "../LCD/LCD.h"

//volatile extern unsigned char falling_edges=0;
 unsigned char *falling_edges;

void portEinit(){
	SYSCTL_RCGCGPIO_R |=0x10;
	while((SYSCTL_RCGCGPIO_R & 0x10)==0);
	//GPIO_PORTE_LOCK_R=0x4C4F434B;
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
	while((GPIO_PORTE_DATA_R &0X10)==0){
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
	GPIO_PORTF_DATA_R |= 0X10;//SW1 AND SW2 UNPRESSED SW3 PRESSED (OPEN DOOR)
	GPIO_PORTF_IS_R &= ~0X12;
	GPIO_PORTF_IBE_R &= ~0X12;
	GPIO_PORTF_IEV_R &= ~0X12;
	GPIO_PORTF_ICR_R =0X12;
	GPIO_PORTF_IM_R |=0X12;
	NVIC_PRI7_R=((NVIC_PRI7_R) & (0XFF00FFFF))|0X00A00000;
	NVIC_EN0_R=0X40000000;
	//GPIO_PORTF_MIS_R |=0X10;
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
NVIC_EN0_R=0X10;*/

//}
/*void portEinit(){
SYSCTL_RCGCGPIO_R |=0x10;
while((SYSCTL_RCGCGPIO_R & 0x10)==0);
GPIO_PORTE_LOCK_R=0x4C4F434B;
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
NVIC_PRI1_R |=0X40;
NVIC_EN0_R=0X10;

}




void GPIOE_Handler()
{
	GPIO_PORTD_ICR_R =0X10;
	do{
		GPIO_PORTF_DATA_R ^= 0X0C;
		 Systick_Wait_ms(500);
	}while((GPIO_PORTE_DATA_R &0X10)!=1);



}*/
void  GPIOF_Handler(void) 
{
	int z = 0;
	if((GPIO_PORTF_MIS_R & 0X10)==0X10){	
		GPIO_PORTF_ICR_R |=0X10;
		GPIO_PORTF_DATA_R ^= 0X0C;
		Systick_Wait_ms(200);
		do{
			z++;
			Systick_Wait_ms(1);
			if(z>=500){
				GPIO_PORTF_DATA_R ^= 0X0C;
				z = 0;
			}
		}while((GPIO_PORTF_DATA_R &0X1)!=0 && (GPIO_PORTF_DATA_R &0X10) != 0);
		if((GPIO_PORTF_DATA_R &0X1)==0){
			*falling_edges = 2;
			return;
		}
		else if((GPIO_PORTF_DATA_R &0X10) == 0)
			*falling_edges = 0;
	}
	GPIO_PORTF_DATA_R &= ~0X0C;

/*		if(falling_edges%2==1){
			do{
				GPIO_PORTF_DATA_R ^= 0X0C;
				Systick_Wait_ms(500);
			}while((GPIO_PORTF_DATA_R &0X1)!=0 && (GPIO_PORTF_DATA_R &0X10) != 0);
		}
		if(falling_edges%2==0){
			LCD_Cmd(clear_display);
		}
	}
	if((GPIO_PORTF_MIS_R & 0X02)==0X02){
		GPIO_PORTF_ICR_R |=0X02;
		do{
			GPIO_PORTF_DATA_R ^= 0X0C;
			 Systick_Wait_ms(500);
		}while((GPIO_PORTF_DATA_R &0X02)!=1);
	}*/
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
	GPIO_PORTE_DATA_R |=0X20;
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