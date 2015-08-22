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

void initPWM()
{
	//Timer1 used in Fast PWM mode
	
	DDRB |= (1<<PINB1);	//OCR1A (PB1) pin as output
	
	TCCR1B |= (1<<CS10);	//No prescaler
	
	TCCR1B |= (1<<WGM13) | (1<<WGM12);	//Fast PWM
	TCCR1A |= (1<<WGM11);	
	
	TCCR1A |= (1<<COM1A1);	//PWM non-inverting mode
	
	ICR1 = 5999;	//top value - for 150Hz PWM freq
	OCR1A = 4000;	//higher value -> high duty cycle
}

int main(void)
{
	initPWM();
	
    while(1)
    {
        
    }
}