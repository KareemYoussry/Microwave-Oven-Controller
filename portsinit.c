/*#include "tm4c123gh6pm.h"


void SystemInitAB(){
SYSCTL_RCGCGPIO_R |=0x01;
while((SYSCTL_RCGCGPIO_R & 0x01)==0)
{}
	
//GPIO_PORTB_LOCK_R=0x4C4F434B;
 GPIO_PORTA_AMSEL_R &= ~0xE0;      
 GPIO_PORTA_PCTL_R &= ~0xFFF00000;                    
    GPIO_PORTA_DIR_R |= 0xE0;         
    GPIO_PORTA_AFSEL_R &= ~0xE0;           
    GPIO_PORTA_DEN_R |= 0xE0;
    GPIO_PORTA_DR8R_R |= 0xE0;
	
	SYSCTL_RCGCGPIO_R |=0x02;

while((SYSCTL_RCGCGPIO_R & 0x02)==0)
{}
	GPIO_PORTB_AMSEL_R &= ~0xFF;      
    GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;                    
    GPIO_PORTB_DIR_R |= 0xFF;         
    GPIO_PORTB_AFSEL_R &= ~0xFF;           
    GPIO_PORTB_DEN_R |= 0xFF;
    GPIO_PORTB_DR8R_R |= 0xFF;
	

}*/
