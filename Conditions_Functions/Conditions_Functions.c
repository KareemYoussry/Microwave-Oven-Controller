#include "Conditions_Functions.h"
#include "../timer/timer.h"
#include "../LCD/LCD.h"

volatile unsigned char falling_edges;
volatile unsigned char flag; // a flag to exit the interrupt in the begginning
volatile unsigned char SW3_Flag;
volatile unsigned char SW1_to_clear; // flag for switch 1 to clear LCD on D-case
volatile unsigned char SW1_f; // flag to tell the interrupt we're coming from D: 2 to indicate we're coming from D case
														  //                															 : 0 to indicate nothing happened

void portEinit(){
	SYSCTL_RCGCGPIO_R		|=	0x10;
	while((SYSCTL_RCGCGPIO_R & 0x10)==0);
	GPIO_PORTE_CR_R			|=	0X30;
	GPIO_PORTE_AMSEL_R	&= ~0X30;
	GPIO_PORTE_PCTL_R		&= ~0XFF0000;
	GPIO_PORTE_AFSEL_R	&= ~0X30;
	GPIO_PORTE_DIR_R		|=	0X20;
	GPIO_PORTE_DEN_R		|=	0X30;
	GPIO_PORTE_PUR_R 		|=	0X10;
	GPIO_PORTE_DATA_R		|=	0X10;	//DOOR CLOSED INITIALLY
	GPIO_PORTE_IS_R			&= ~0X10;
	GPIO_PORTE_IBE_R		&= ~0X10;
	GPIO_PORTE_IEV_R		&= ~0X10;
	GPIO_PORTE_ICR_R		 =	0X10;
	GPIO_PORTE_IM_R			|=	0X10;
	NVIC_PRI1_R = ((NVIC_PRI1_R) & (0XFFFFFF00))|0X00000010;
	NVIC_EN0_R=0X10;
}



void GPIOE_Handler()
{
	// Interrupt for the Door whose priority is higher than the F handler
	// Pauses the counting down (Cooking) when it is held down with the LEDs blinking every 0.5 secs
	GPIO_PORTE_ICR_R =0X10;
	if(SW3_Flag == 0)
		return;
	while((GPIO_PORTE_DATA_R &0X10)==0){
		GPIO_PORTF_DATA_R ^= 0X0E;
		Systick_Wait_ms(500);
	}
	GPIO_PORTF_DATA_R &= ~0X0E;	// Deactivates the LEDs after blinking
}

// Initiallizes PORT_E
void portFinit(){
	SYSCTL_RCGCGPIO_R		|=	0x20;
	while((SYSCTL_RCGCGPIO_R & 0x20)==0);
	GPIO_PORTF_LOCK_R		 =	0x4C4F434B;
	GPIO_PORTF_CR_R			|=	0X01F;
	GPIO_PORTF_AMSEL_R	&= ~0X01F;
	GPIO_PORTF_PCTL_R		&= ~0X000FFFFF;
	GPIO_PORTF_AFSEL_R	&= ~0X01F;
	GPIO_PORTF_DIR_R		|=	0X0E;
	GPIO_PORTF_DEN_R		|=	0X1F;
	GPIO_PORTF_PUR_R		|=	0X11;
	GPIO_PORTF_DATA_R		|=	0X10;		//SW1 AND SW2 UNPRESSED SW3 PRESSED (OPEN DOOR)
	GPIO_PORTF_IS_R			&= ~0X10;
	GPIO_PORTF_IBE_R		&= ~0X10;
	GPIO_PORTF_IEV_R		&= ~0X10;
	GPIO_PORTF_ICR_R		 =	0X10;
	GPIO_PORTF_IM_R			|=	0X10;
	NVIC_PRI7_R = ((NVIC_PRI7_R) & (0XFF00FFFF))|0X00A00000;
	NVIC_EN0_R = 0X40000000;
	//GPIO_PORTF_MIS_R |=0X10;
}

// PORT_F Handler for switch 1
void  GPIOF_Handler() 
{
	if((GPIO_PORTF_MIS_R & 0X10)==0X10){	
		int ticks = 0;
		GPIO_PORTF_ICR_R |= 0X10;
		
		if(SW1_f == 2 && SW1_to_clear == 2){ // Checks when the handler is called from D_Key() and when SW1 is pressed to clear LCD
			SW1_to_clear = 5;
			return;
		}
		
		if(flag >= 1)		// In case of 'D' key pressed
			return;
		if(falling_edges >= 2){
			GPIO_PORTF_DATA_R &= ~0X0E;	// Deactivates LEDs after blinking during the pause
			return;
		}
		GPIO_PORTF_DATA_R ^= 0X0E;		// Toggles the LEDs
		falling_edges = 1;						// Sets falling_edges = 1
		Systick_Wait_ms(200);
		do{		// Toggles the LEDs every 500ms (0.5 secs) while checking for any switch pressed each 1ms
			ticks++;
			Systick_Wait_1ms();
			if(ticks>=500){
				GPIO_PORTF_DATA_R ^= 0X0E;
				ticks = 0;
			}
		}while((GPIO_PORTF_DATA_R & 0X1)!=0 && (GPIO_PORTF_DATA_R &0X10) != 0);
		
		if((GPIO_PORTF_DATA_R & 0X10) == 0){	// Checks when SW2 is pressed
			falling_edges++;		// Increases falling_edges by 1
			GPIO_PORTF_DATA_R &= ~0X0E;		// Deactivates the LEDs after blinking
		}
		else if((GPIO_PORTF_DATA_R & 0X1) == 0)	// Checks when SW1 is pressed
			GPIO_PORTF_DATA_R &= ~0X0E;		// Deactivates the LEDs after blinking
	}
}

// Activates LEDs
void leds_on(){
	GPIO_PORTF_DATA_R |= 0X0E;
}

// Deactivate LEDs
void leds_off(){
	GPIO_PORTF_DATA_R &= ~0X0E;
}

// Blinks the LEDs every 500ms (0.5 sec)
void leds_blink(){
	int i;
	for(i=0;i<6;i++){		
		GPIO_PORTF_DATA_R ^= 0X0E;
		Systick_Wait_ms(500);
	}
}

// Activates the buzzer
void buzzer_on(){
	GPIO_PORTE_DATA_R |= 0X20;
}

// Deactivates the buzzer
void buzzer_off(){
	GPIO_PORTE_DATA_R &= ~0X20;
}

unsigned char sw1_input(){
	return GPIO_PORTF_DATA_R &0X10;
}

unsigned char sw2_input(){
	return GPIO_PORTF_DATA_R &0X1;
}