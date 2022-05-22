#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "./CONDITIONS_FUNCTIONS/CONDITION_FUNCTIONS.h"
#include "./Microwave_Functions/Microwave_Functions.h"
extern volatile unsigned char falling_edges;
volatile unsigned char Dflag; //for the interrupt of the D_Flag

extern volatile unsigned char flag; //1: for stopping in the interrupt
																		//2: for D case to print error
																		//3: 
																		//4: 
																		//5: to continue
	
int main(void)
{
	
  char c;	
  portFinit();
  LCD_Init();
  keypad_Init();
	portEinit();
	falling_edges=0;
  while (1)
  {
		falling_edges = 0;
		flag = 1;
		leds_off();
		LCD_String("Enter:");
    c = keypad_getkey();
    if(!(c == 'A'|| c == 'B'||c == 'C'||c == 'D'))
      continue;
    LCD_Write_Char(c);
    Systick_Wait_ms(250);
    switch(c){
      case 'A':
			 LCD_Cmd(clear_display);
			 popCorn();
			 break;

      case 'B':
        break;

      case 'C':
        break;

      case 'D':
				Dflag = 1;
				LCD_Cmd(clear_display);
				D_Key();
        break;
    }
		LCD_Cmd(clear_display);
		if(falling_edges == 2){
			LCD_String("Stopped!");
			leds_blink();
			buzzer_off();			
			LCD_Cmd(clear_display);
			continue;
		}
		
		
		if(flag == 2)
			LCD_String("Err");
		else
			LCD_String("Done!");
		
		buzzer_on();
		leds_blink();
		buzzer_off();			
		LCD_Cmd(clear_display);

  }
	
	
}