/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 10/19/2018
Author  : 
Company : 
Comments: 


Chip type               : ATmega8
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega8.h>
#include <delay.h>
#define F_CPU 8000000
#define SW_ON PINC.0
#define SW_OFF PINC.1
#define LED PORTD.0
unsigned char Data_Master=0;
unsigned char Data_Slave=0;

void SPI_Master_Init(void);
void SPI_Slave_Init(void);
unsigned char Check_SW(void);
unsigned char SPI_Master_Transfer(unsigned char data_Master);
unsigned char SPI_Slave_Receive(void);
void main(void)
{
    SPI_Slave_Init();
    DDRD=0xFF; 
    #asm("sei")         // Global enable interrupts
    while (1)
          { 
            /*-----------Slave Implementation---------*/ 
            LED=SPI_Slave_Receive();
            /*-----------------------------------------*/

          }
}


void SPI_Master_Init(void){
     DDRB = (1<<5)|(1<<3);                // Set MOSI, SCK as Output
     SPCR =  (1<<SPE)|(1<<MSTR);          // Enable SPI, Set as Master,Fosc/4 (2Mhz)
}
void SPI_Slave_Init(void){
    DDRB = (1<<4);     //MISO as OUTPUT
    SPCR = (1<<SPE);   //Enable SPI
}
unsigned char Check_SW(void)
{
    if(SW_ON==0)    return 1;
    if(SW_OFF==0)   return 0;
}
unsigned char SPI_Master_Transfer(unsigned char data_Master)
{  
    SPDR = data_Master;       // Load data into the buffer
    while(!(SPSR & (1<<SPIF) ));
    return(SPDR);             // Return received data
}
unsigned char SPI_Slave_Receive(void)
{
    while(!(SPSR & (1<<SPIF) ));
    return(SPDR);      // Return received data
}