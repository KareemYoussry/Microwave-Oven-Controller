#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "./Conditions_Functions/Conditions_Functions.h"
#include "./Microwave_Functions/Microwave_Functions.h"

extern volatile unsigned char falling_edges;
extern volatile unsigned char flag; //1: for stopping in the interrupt
																		//2: for D case to print error
extern volatile unsigned char SW3_Flag;

enum States{
	start,
} states;

int main()
{
  char c;	
  portFinit();
  LCD_Init();
  keypad_Init();
	portEinit();
	falling_edges=0;
  LCD_Cmd(clear_display);

	while (1)
  {
		falling_edges = 0;
		flag = 1;
		leds_off();
		LCD_Cmd(clear_display);
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
				Beef();
        break;

      case 'C':
				Chicken();
        break;

      case 'D':
				D_Key();
        break;
    }
		LCD_Cmd(clear_display);
		SW3_Flag = 0;
		if(falling_edges == 2){
			LCD_String("Stopped!");
			buzzer_on();
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