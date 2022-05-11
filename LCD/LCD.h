#ifndef __LCD_H__
#define __LCD_H__

#include "../tm4c123gh6pm.h"
#include "../timer/timer.h"

#define	LCD	GPIOB	/* Define "LCD" as a symbolic name for GPIOB */
#define	RS	0x20	/* PORTB BIT5 mask for Register Select Bit */
#define	RW	0x40	/* PORTB BIT6 mask for Read/Write Bit */
#define	EN	0x80	/* PORTB BIT7 mask for Enable Bit */

/* Define useful symbolic names for LCD commands */
#define clear_display     0x01
#define returnHome        0x02
#define moveCursorRight   0x06
#define moveCursorLeft    0x08
#define shiftDisplayRight 0x1C
#define shiftDisplayLeft  0x18
#define cursorBlink       0x0F
#define cursorOff         0x0C
#define cursorOn          0x0E
#define Function_set_4bit 0x28
#define Function_set_8bit 0x38
#define Entry_mode        0x06
#define Function_8_bit    0x32
#define Set5x7FontSize    0x20
#define FirstRow          0x80

/* LCD Function Prototypes */
void LCD_Write_Hb(unsigned char data, unsigned char control);	/* Writes 4-bits */
void LCD_Cmd(unsigned char command);	/*Used to send commands to LCD */
void LCD_Init(void);	/* LCD initialization function */
void LCD_Write_Char(unsigned char data);	/* Writes ASCII character */
void LCD_String (char *str);	/* Send string to LCD function */

#endif
