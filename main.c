#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "./CONDITIONS_FUNCTIONS/CONDITION_FUNCTIONS.h"
#include "./Microwave_Functions/Microwave_Functions.h"

unsigned char button_in2;
unsigned char button_in1;


int main(void)
{
    char c;
    portFinit();
    LCD_Init();
    keypad_Init();

    LCD_String("Enter ");
    Systick_Wait_ms(3000);
    LCD_Cmd(clear_display);

    while (1)
    {
        c = keypad_getkey();
        if(!(c == 'A'|| c == 'B'||c == 'C'||c == 'D'))
            continue;
        LCD_Write_Char(c);
        Systick_Wait_ms(250);
        do
        {
            button_in2 = sw2_input();
        }while(button_in2);
 	if(button_in2==0)
		{
				//if((button_in2==0)&&(button_in1==0)){
				leds_on();
        switch(c){
            case 'A':
                popCorn();
                leds_blink();
            break;

            case 'B':
                leds_blink();
                break;

            case 'C':
                leds_blink();
                break;

            case 'D':
                leds_blink();
                break;
        }
        leds_off();
    }
	}
}
//}
