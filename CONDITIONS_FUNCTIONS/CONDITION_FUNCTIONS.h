#ifndef __CONDITION_FUNCTIONS_H__
#define __CONDITION_FUNCTIONS_H__

#include "../tm4c123gh6pm.h"
#include "../timer/timer.h"
//#include "startup_TM4C123.s"

void portEinit(void);
void portFinit(void);
void pause(void);
void stop_cooking(void);
void leds_on(void);
void leds_off(void);
void leds_blink(void);
void buzzer_on(void);
void buzzer_off(void);
unsigned char sw1_input(void);
unsigned char sw2_input(void);
char check_Num(unsigned char values [], int n);
void D_Key(void);

#endif
