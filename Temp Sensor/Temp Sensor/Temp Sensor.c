/*
	Title:
		Module 2: Temperature Sensor
		
	Description:
		A modular component that returns the temperature value.
	
	Author:
		Bishal Heuju
	
	Hardware:
		uC: Atmega8
		XTAL: Internal 1MHz
	
	Technical Specifications:
		* Slave device
		* Uses SPI
		* Uses ADC to control the intensity of the LED
	
	Notes:
		* TODO
		
		
	Operation Guidelines:
		1. ** TODO **
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t ADCvalue;    // Global variable, set to volatile if used with ISR

void initADC()
{
    ADMUX = 0;	// use ADC0
	ADMUX |= (1<<REFS0);

    ADCSRA |= (1 << ADPS2);	// Division factor 16
    ADCSRA |= (1 << ADFR);	// Set free running mode
    ADCSRA |= (1 << ADEN);	// Enable the ADC
    ADCSRA |= (1 << ADIE);	// Enable Interrupts 
}

int main(void)
{

	DDRB = 0xff;
	DDRD = 0xff;
	PORTB = 0x00;
	PORTD = 0x00;

	initADC();
	sei();

    ADCSRA |= (1 << ADSC);    // Start the ADC conversion

    while (1)
    {
           
    }
}


ISR(ADC_vect)
{
    ADCvalue = ADCW;
	PORTB = ADCvalue;
	PORTD = (ADCvalue>>8);
}