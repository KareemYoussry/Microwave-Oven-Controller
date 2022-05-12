/*#include "tm4c123gh6pm.h"
#include "systick.c"
#include "portsinit.c"*/

/* Hardware connection between Launchpad and LCD1602 module    
||     Lauchpad Pin         <==>      LCD1602 Pin      
||         GND              <==>         Pin1
||         Vcc              <==>         Pin2 (3.3V)
||         GND              <==>         Pin3 (connect a 3.9k to GND) 
||         PA6              <==>         Pin4  (RS)
||         PA5              <==>         Pin5  (R/W, To GND is only enable to write)
||         PA7              <==>         Pin6  (E)
||         PB0              <==>         Pin7
||         PB1              <==>         Pin8
||         PB2              <==>         Pin9
||         PB3              <==>         Pin10
||         PB4              <==>         Pin11
||         PB5              <==>         Pin12
||         PB6              <==>         Pin13
||         PB7              <==>         Pin14                    
||         Vcc              <==>         Pin15,  (A, connect a 330R to Vcc)
||         GND              <==>         Pin16,  (K, connect to Ground) 

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
*/





