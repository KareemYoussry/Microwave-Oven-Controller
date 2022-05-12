/*#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))
#include "tm4c123gh6pm.h"


void Sstick_wait(unsigned long delay){
  NVIC_ST_CTRL_R=0x00;
	NVIC_ST_RELOAD_R=delay-1;
	NVIC_ST_CURRENT_R =0;
	NVIC_ST_CTRL_R=0x05;
	while(( NVIC_ST_CTRL_R&0x00010000)==0){}
}



void genericdelay(unsigned long time){
int i;
	for(i=0;i<time;i++){
	Sstick_wait(16000);
	}
}*/