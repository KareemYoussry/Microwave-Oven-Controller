#ifndef __LCD_H__
#define __LCD_H__

#include "../tm4c123gh6pm.h"
#include "../timer/timer.h"

#define	LCD	GPIOB	/* Define "LCD" as a symbolic name for GPIOB */
#define	RS	0x01	/* PORTB BIT0 mask for Register Select Bit */
#define	RW	0x02	/* PORTB BIT1 mask for Read/Write Bit */
#define	EN	0x04	/* PORTB BIT2 mask for Enable Bit */

/* Define useful symbolic names for LCD commands */
#define clear_display			0x01
#define returnHome				0x02
#define Entry_mode				0x06
#define	displayOn					0x0F
#define moveCursorRight		0x14
#define moveCursorLeft		0x10
#define shiftDisplayRight	0x1F
#define shiftDisplayLeft	0x18
#define Function_set_4bit	0x28
#define Function_set_8bit	0x33
#define Set5x11FontSize		0x20
#define FirstRow					0x80
#define SecondRow					0xC0


/* LCD Function Prototypes */
void LCD_Write_Hb(unsigned char data, unsigned char control);	/* Writes 4-bits */
void LCD_Cmd(unsigned char command);	/*Used to send commands to LCD */
void LCD_Init(void);	/* LCD initialization function */
void LCD_Write_Char(unsigned char data);	/* Writes ASCII character */
void LCD_String (char *str);	/* Send string to LCD function */
void LCD_StringPos(char *str, unsigned char Line, unsigned char Pos);	/* Send string to LCD at the specified line and position */

#endif
