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

#define SS		PINB2
#define MOSI	PINB3
#define MISO	PINB4
#define SCK		PINB5

volatile uint8_t dataHigh;
volatile uint8_t dataLow;
uint8_t count = 1;

volatile uint16_t ADCvalue;    // Global variable, set to volatile if used with ISR
volatile uint8_t tempValue;

void initADC()
{
    ADMUX = 0;	// use ADC0
	ADMUX |= (1<<REFS0);

    ADCSRA |= (1 << ADPS2);	// Division factor 16
    ADCSRA |= (1 << ADFR);	// Set free running mode
    ADCSRA |= (1 << ADEN);	// Enable the ADC
    ADCSRA |= (1 << ADIE);	// Enable Interrupts 
}

void initSPISlave()
{
	DDRB |= (1<<MISO);	//MISO as o/p
	DDRB &= ~((1<<MOSI)|(1<<SS)|(1<<SCK));	//MOSI, SCK and SS as i/p
	
	PORTB |= (1<<SS); //internal pull up SS;
	
	SPCR &= ~(1<<MSTR);	//set as slave
	SPCR |= (1<<SPE)|(1<<SPIE);	//enable spi and spi interrupt
}

int main(void)
{
	//DDRB = 0xff;
	//DDRD = 0xff;
	//PORTB = 0x00;
	//PORTD = 0x00;
	
	initADC();
	initSPISlave();
	
	sei();

    ADCSRA |= (1 << ADSC);    // Start the ADC conversion
	
    while (1)
    {
		//TODO - convert digital value to temp
		float v = (ADCvalue * 5000) / 1024.0;	//get input voltage value in mV
		tempValue = v / 10;		//convert voltage into degree celsius
    }
}

ISR(ADC_vect)
{
    ADCvalue = ADCW;
	//PORTB = ADCvalue;
	//PORTD = (ADCvalue>>8);
}

ISR(SPI_STC_vect)
{
	uint8_t command, reply;
	
    command = SPDR;   // what Slave has received
	
    if (command == 'Q')	//if query temp
	{
		reply = tempValue;
		SPDR = reply;     // what Slave sends on next SPI  
	}
}