#include "LCD.h"
#include "../timer/timer.h"

void LCD_Write_Hb(unsigned char data, unsigned char control)
{
	data		&=	0xF0;	/* Extract upper nibble for data */
	control	&=	0x0F;	/* Extract lower nibble for control */
	GPIO_PORTB_DATA_R = data | control;	/* Set RS and R/W bits to zero for write operation */
	GPIO_PORTB_DATA_R = data | control | EN;	/* Provide Pulse to Enable pin to perform wite operation */
	
	Systick_Wait_1us();
	
	GPIO_PORTB_DATA_R = data;	/* Send data */
	GPIO_PORTB_DATA_R = 0;		/* Stop writing data to LCD */
}

void LCD_Cmd(unsigned char command)
{
	LCD_Write_Hb(command & 0xF0, 0);   /* Write upper nibble to LCD */
	LCD_Write_Hb(command << 4, 0);     /* Write lower nibble to LCD */
	
	if (command < 4)
		Systick_Wait_ms(2);         /* 2ms delay for commands 1 and 2 */
	else
		Systick_Wait_us(40);        /* 40us delay for other commands */
}

void LCD_Init(void)
{
	SYSCTL_RCGCGPIO_R	|= (1<<1);	/* Enable Clock to GPIOB */
	GPIO_PORTB_DIR_R	|=	0xFF;		/* Set GPIOB all pins a digital output pins */
	GPIO_PORTB_DEN_R	|=	0xFF;		/* Declare GPIOB pins as digital pins */
	
	// The following commands are defined in the header file
	LCD_Cmd(Set5x7FontSize);		/* select 5x7 font size and 2 rows of LCD */
	LCD_Cmd(Function_set_4bit);	/* Select 4-bit Mode of LCD */
	LCD_Cmd(moveCursorRight);		/* shift cursor right */
	LCD_Cmd(clear_display);			/* clear whatever is written on display */
	LCD_Cmd(cursorBlink);				/* Enable Display and cursor blinking */
}

void LCD_Write_Char(unsigned char data)
{
	LCD_Write_Hb(data & 0xF0, RS);    /* Write upper nibble to LCD and RS = 1 to write data */
	LCD_Write_Hb(data << 4, RS);      /* Write lower nibble to LCD and RS = 1 to write data */
	Systick_Wait_us(40);		/* Delay for the LCD to write the character */
}

void LCD_String (char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)	/* Send each char of string till it reaches NULL */
	{
		LCD_Write_Char(str[i]);	/* Call LCD data write for each character */
	}
}