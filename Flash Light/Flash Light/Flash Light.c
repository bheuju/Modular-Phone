/*
	Title:
		Module 1: Flash Light
		
	Description:
		A modular component that controls the intensity of a LED light.
	
	Author:
		Bishal Heuju
	
	Hardware:
		uC: Atmega8
		XTAL: Internal 1MHz
	
	Technical Specifications:
		* Slave device
		* Uses SPI
		* Uses PWM to control the intensity of the LED
	
	Notes:
		* ** TODO **
		
	Operation Guidelines:
		1. ** TODO **
 */ 

#define F_CPU 1000000L

#define SETBIT(x, y) (x |= _BV(y))
#define CLEARBIT(x, y) (x &= ~(_BV(y)))

#include <avr/io.h>

int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
    }
}