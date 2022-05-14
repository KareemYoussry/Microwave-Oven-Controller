#include "timer.h"

#define		CLK_FREQ		16000000
#define		MILLI_SEC		1*(CLK_FREQ/1000)
#define		MICRO_SEC		1*(CLK_FREQ/1000000)

void SysTick_Wait(uint32_t delay)
{
	NVIC_ST_CTRL_R			= 0;				// (1) disable SysTick during setup
	NVIC_ST_RELOAD_R		=	delay-1;	// (2) number of counts to wait
	NVIC_ST_CURRENT_R		= 0;				// (3) any value written to CURRENT clears
	NVIC_ST_CTRL_R	   |= 0x5;			// (4) enable SysTick with core clock

	while((NVIC_ST_CTRL_R & 0x00010000) == 0);// wait for COUNT flag
}

void Systick_Wait_1ms(void)
{
	SysTick_Wait(MILLI_SEC);
}

void Systick_Wait_1us(void)
{
    SysTick_Wait(MICRO_SEC);
}

void Systick_Wait_ms(unsigned int time)
{
	int i;
	for(i = 0; i < time; i++)
	{
		Systick_Wait_1ms();
	}
}

void Systick_Wait_us(unsigned int time)
{
	int i = 0;
	for(i = 0; i < time; i++)
	{
		Systick_Wait_1us();
	}
}
