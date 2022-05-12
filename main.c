//#include "lcd_driver.c"
#include "tm4c123gh6pm.h"
//#include "systick.c"
//#include "portsinit.c"


void Sstick_wait(unsigned long delay){
  NVIC_ST_CTRL_R=0x00;
	NVIC_ST_RELOAD_R=delay-1;
	NVIC_ST_CURRENT_R =0;
	NVIC_ST_CTRL_R=0x05;
	while(( NVIC_ST_CTRL_R&0x00010000)==0){}
}



void genericdelay(unsigned long time){
int i;
	for(i=0;i<time;i++){
	Sstick_wait(16000);
	}
}

////////////////////////////////////////////////////////////////////////////////
void SystemInitAB(){
SYSCTL_RCGCGPIO_R |=0x01;
while((SYSCTL_RCGCGPIO_R & 0x01)==0)
{}
	
//GPIO_PORTB_LOCK_R=0x4C4F434B;
 GPIO_PORTA_AMSEL_R &= ~0xE0;      
 GPIO_PORTA_PCTL_R &= ~0xFFF00000;                    
    GPIO_PORTA_DIR_R |= 0xE0;         
    GPIO_PORTA_AFSEL_R &= ~0xE0;           
    GPIO_PORTA_DEN_R |= 0xE0;
    GPIO_PORTA_DR8R_R |= 0xE0;
	
	SYSCTL_RCGCGPIO_R |=0x02;

while((SYSCTL_RCGCGPIO_R & 0x02)==0)
{}
	GPIO_PORTB_AMSEL_R &= ~0xFF;      
    GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;                    
    GPIO_PORTB_DIR_R |= 0xFF;         
    GPIO_PORTB_AFSEL_R &= ~0xFF;           
    GPIO_PORTB_DEN_R |= 0xFF;
    GPIO_PORTB_DR8R_R |= 0xFF;
	

}
///////////////////////////////////////////////////////////////////////////////////////////////
void Write_Command(unsigned char LCD_Command){  //LCD1602 Write Commend to LCD module
    GPIO_PORTA_DATA_R &= ~0xE0;     //RS=0,RW=0,E=0
    GPIO_PORTB_DATA_R = LCD_Command;         //Write Command    
    GPIO_PORTA_DATA_R |= 0X80;                  //RS=0,RW=0,E=1
   // GPIO_PORTA_DATA_R &= ~(RS+RW);
    Sstick_wait(5);                       //Enable width 230 ns
    GPIO_PORTA_DATA_R &=~0xE0 ;     //RS=0,RW=0,E=0
    Sstick_wait(16000);                     //Delay 1 ms
}

void Write_Data(unsigned char LCD_Data){
    GPIO_PORTB_DATA_R = LCD_Data;            //Write Data
    GPIO_PORTA_DATA_R |= 0xC0;               //RS=1,RW=0,E=1
    //GPIO_PORTA_DATA_R &= ~RW;
     Sstick_wait(5);                    //Enable width 230 ns
      GPIO_PORTA_DATA_R &= ~0xE0;     //RS=0,RW=0,E=0
    Sstick_wait(16000);               //Delay 1 ms
}     



void LCD_Init(){        
   SystemInitAB()   ;
	 genericdelay(16);                    //Delay 15ms   
    Write_Command(0x38);
    genericdelay(6);                     //Delay 5ms  
    Write_Command(0x38);
   Sstick_wait(2400);                   //Delay 150us      
        
    Write_Command(0x0C);            
    Write_Command(0x01);            
    Write_Command(0x06);
            
     genericdelay(51);                     //Delay 50ms    
}      

void LCD_Clear(){
    Write_Command(0x01);    
}

void LCD_DisplayString(unsigned char *str){      
    while(*str != 0){
        Write_Data(*str++);                  
    }    
}

void LCD_DisplayChar(unsigned char CHAR){      
    Write_Data(CHAR); 
}

void LCD_DisplayDec(unsigned int number){   
    if(number >=10){
        LCD_DisplayDec(number/10);
        number = number%10;
    }
    LCD_DisplayChar(number+'0');   
}

void LCD_DisplayPosition(unsigned char Line,unsigned int digit){   
    Write_Command(Line + digit);
}




int main(void)
{
	
	SystemInitAB();
	LCD_Init();

	LCD_DisplayChar('x');
	while (1)
	{
		
	}
	
}

