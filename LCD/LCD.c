#include"LCD.h"
#include"../timer/timer.h"


void LCD_Write_Hb(unsigned char data, unsigned char control)
{
	data		&=	0xF0;	/* Extract upper nibble for data */
	control	&=	0x0F;	/* Extract lower nibble for control */
	GPIO_PORTB_DATA_R	 = data | control;	/* Set RS and R/W bits to zero for write operation */
	GPIO_PORTB_DATA_R	|= EN;	/* Provide Pulse to Enable pin to perform write operation */
	Systick_Wait_1us();
	GPIO_PORTB_DATA_R	&= ~EN;		/* Turns off the pulse from the Enable pin */
	GPIO_PORTB_DATA_R	 = 0;			/* Resets PORTB */
}

void LCD_Cmd(unsigned char command)
{
	LCD_Write_Hb(command & 0xF0, 0);   /* Write upper 4 bits to LCD */
	LCD_Write_Hb(command << 4, 0);     /* Write lower 4 bits to LCD */
	
	if (command < 4)
		Systick_Wait_ms(2);		/* 2ms delay for commands 1 and 2 */
	else
		Systick_Wait_us(40);	/* 40us delay for other commands */
}

void LCD_Init(void)
{
	SYSCTL_RCGCGPIO_R	|= (1<<1);	/* Enable Clock to GPIOB */
	Systick_Wait_ms(10);
	GPIO_PORTB_DIR_R	|=	0xFF;		/* Set GPIOB all pins a digital output pins */
	GPIO_PORTB_DEN_R	|=	0xFF;		/* Declare GPIOB pins as digital pins */
	
	// The following commands are defined in the header file	
	LCD_Cmd(Function_set_4bit);	/* Select 4-bit Mode of LCD */
	LCD_Cmd(Entry_mode);				
//LCD_Cmd(moveCursorRight);		/* shift cursor right */
	LCD_Cmd(clear_display);			/* clear whatever is written on display */
	LCD_Cmd(displayOn);					/* Sets the display on with cursor blinking */
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
	for(i = 0; str[i]!= '\0'; i++)	/* Send each char of string till it reaches NULL */
	{
		LCD_Write_Char(str[i]);	/* Call LCD data write for each character */
	}
}
