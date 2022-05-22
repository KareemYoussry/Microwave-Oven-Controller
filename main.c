#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "./CONDITIONS_FUNCTIONS/CONDITION_FUNCTIONS.h"
#include "./Microwave_Functions/Microwave_Functions.h"
extern volatile unsigned char falling_edges;
extern volatile unsigned char flag;
//unsigned char button_in2;
//unsigned char button_in1;
 

	
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
			 popCorn();
			 break;

      case 'B':
        break;

      case 'C':
        break;

      case 'D':
        break;
    }
		if(falling_edges == 2){
			LCD_String("Stopped!");
			buzzer_on();
			leds_blink();
			buzzer_off();			
			LCD_Cmd(clear_display);
		}
		else{
			LCD_String("Done!");
			buzzer_on();
			leds_blink();
			buzzer_off();			
			LCD_Cmd(clear_display);
		}
  }
	
	
}