#include "tm4c123gh6pm.h"
#include "../timer/timer.h"
#include "keypad.h"
extern volatile unsigned char SW1_to_clear; //flag for switch 1 to clear LCD on D-case: 5 to indicate SW1 clicked

unsigned char keypad_symbols[ROW_NO][COL_NO] =	{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

void keypad_Init()
{
	SYSCTL_RCGCGPIO_R |= 0x14;					//Enable clock to PORTC and PORTE  
	while ((SYSCTL->RCGCGPIO&0x14)==0);	//wait for clock to be setted
	GPIO_PORTC_CR_R  |= 0xF0;			//Allow settings for all pins of PORTC
	GPIO_PORTE_CR_R  |= 0x0F;			//Allow settings for all pins of PORTD
	GPIO_PORTE_DIR_R |= 0x00;			//PE0-PE3 are used with row and set them as digital input pins
	GPIO_PORTC_DIR_R |= 0xF0;			//Set PORTC as digital output
	GPIO_PORTE_PDR_R |= 0x0F;			//Enable pull down resistor on PORTE
	GPIO_PORTC_DEN_R |= 0xF0;			//Set PORTC as digital pins
	GPIO_PORTE_DEN_R |= 0x0F;			//Set PORTE as digital pins
}

char keypad_getkey(void)
{
	int i, j;
	while(1)
	{
		if(SW1_to_clear == 5)
			return '0';
		for(i = 0; i < COL_NO; i++)
		{
			GPIO_PORTC_DATA_R = (1U << (i+4));
			Systick_Wait_us(2);
			
			for(j = 0; j < ROW_NO; j++)
			{
				if ((GPIO_PORTE_DATA_R & 0x0F) & (1U << (j)))
					return keypad_symbols[j][i];
			}
		}
	}
}
