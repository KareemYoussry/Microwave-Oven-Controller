#include "tm4c123gh6pm.h"
#include "./LCD/LCD.h"
#include "./keypad/keypad.h"
#include "./Conditions_Functions/Conditions_Functions.h"
#include "./Microwave_Functions/Microwave_Functions.h"

extern volatile unsigned char falling_edges;
extern volatile unsigned char SW3_Flag;
extern volatile unsigned char SW1_to_clear; //flag for switch 1 to clear LCD on D-case
extern volatile unsigned char flag; //1: for stopping in the interrupt
																		//2: for D case to print error
																		//3: for D case for the SW1
extern volatile unsigned char SW1_f;

int main()
{
  char Keypad_Key;	// Variable to hold the user input
  portFinit();			// Initiallize PORT_F
  LCD_Init();				// Initiallize LCD 			(PORT_B)
  keypad_Init();		// Initiallize Keypad 	(PORT_C & PORT_E)
	portEinit();			// Initiallize PORT_E
  LCD_Cmd(clear_display);		// Clears the LCD display

	while (1)
  {
		falling_edges = 0;	// Resets falling_edges every time the program starts
		flag = 1;			// Sets the flag to 1
		leds_off();		// Turns off LEDs in the case of restarting the program
		LCD_Cmd(clear_display);		// Clears the LCD Display
		LCD_String("Enter:");			// Prompts the user to enter a key
    Keypad_Key = keypad_getkey();	// Calls keypad_getkey until an input is entered
    if(!(Keypad_Key == 'A'|| Keypad_Key == 'B'|| Keypad_Key == 'C'|| Keypad_Key == 'D'))
		{	// Prompts the user to retry when an invalid input is entered
			LCD_Cmd(clear_display);
			LCD_String("Invlaid Input!");
			Systick_Wait_ms(1000);
      continue;		// Restarts the program for another input
		}
		
    LCD_Write_Char(Keypad_Key);	// Echoes the character that the user entered
    Systick_Wait_ms(250);
    switch(Keypad_Key){		// Switch case statement for each key functionality
													// Enters the Cooking Configuration state
      case 'A':
			 popCorn();
			 break;

      case 'B':
				Beef();
        break;

      case 'C':
				Chicken();
        break;

      case 'D':		// Enters the D_Key state
				
				SW1_f = 2;	// SW1_f is set to 2 indicating that the program entered case 'D'
				do{ // do while loop to re-enter D_Key after pressing SW1
					SW1_to_clear = 2;
					D_Key();
				}while(SW1_to_clear != 2);
				SW1_f = 0;
    }
		
		LCD_Cmd(clear_display);		// Clears the LCD Display
		SW3_Flag = 0;			// Resets SW3_Flag to 0
		if(falling_edges == 2){		// Checks when SW1 is pressed twice
			LCD_String("Stopped!");
			buzzer_on();		// Activates the buzzer
			leds_blink();		// Makes the LEDs blink for 3 seconds
			buzzer_off();		// Deactivates the buzzer
			LCD_Cmd(clear_display);		// Clears the LCD Display
			continue;		// Returns to the Initial state
		}
		
		if(flag == 2)		// When an invalid weight is entered in 'B' or 'C'
			LCD_String("Err");
		else
			LCD_String("Done!");
		
		buzzer_on();	// Activates the buzzer 
		leds_blink();	// Makes the LEDs blink for 3 seconds
		buzzer_off();	// Deactivates the buzzer
		LCD_Cmd(clear_display);	// Clears the LCD Display

  }
	
	
}