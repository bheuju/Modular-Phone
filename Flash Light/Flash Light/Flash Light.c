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
		* Receives 16 bit data for PWM value
		* Master needs to send two times 8 bit data (dataLow -> dataHigh)
		
		
	Operation Guidelines:
		1. ** TODO **
 */ 

#define F_CPU 1000000L

#define SETBIT(x, y) (x |= _BV(y))
#define CLEARBIT(x, y) (x &= ~(_BV(y)))

#include <avr/io.h>
#include <avr/interrupt.h>

#define SS		PINB2
#define MOSI	PINB3
#define MISO	PINB4
#define SCK		PINB5

volatile uint8_t dataHigh;
volatile uint8_t dataLow;
volatile uint16_t data = 1;

uint8_t count = 1;

void initPWM()
{
	//Timer1 used in Fast PWM mode
	
	DDRB |= (1<<PINB1);	//OCR1A (PB1) pin as output
	
	TCCR1B |= (1<<CS10);	//No prescaler
	
	TCCR1B |= (1<<WGM13)|(1<<WGM12);	//Fast PWM
	TCCR1A |= (1<<WGM11);	
	
	TCCR1A |= (1<<COM1A1);	//PWM non-inverting mode
	
	ICR1 = 5999;	//top value - for 150Hz PWM freq
	//ICR1 = 19999;
	OCR1A = 1;	//higher value -> high duty cycle
}

void initSpiSlave()
{
	DDRB |= (1<<MISO);	//MISO as o/p
	DDRB &= ~((1<<MOSI)|(1<<SS)|(1<<SCK));	//MOSI, SCK and SS as i/p
	
	PORTB |= (1<<SS); //internal pull up SS;
	
	SPCR &= ~(1<<MSTR);	//set as slave
	SPCR |= (1<<SPE)|(1<<SPIE);	//enable spi and spi interrupt
}

int main(void)
{
	initPWM();
	initSpiSlave();
	
	sei();
	
    while(1)
    {
		OCR1A = data;
    }
}

ISR(SPI_STC_vect)
{
	if (count == 1)
	{
		dataLow = SPDR;
	}
	else if (count == 2)
	{
		dataHigh = SPDR;
		data = dataHigh;
		
		data = (data<<8) | dataLow;
	}
	count++;
	if (count > 2)
	{
		count = 1;
	}
}