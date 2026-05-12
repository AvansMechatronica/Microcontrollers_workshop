/*
*  ADC.c
*
*  Copyright (c) 2012 by Avans Hogeschool.
* 
*  Date:    24-apr-2012
*  Author:  Roel Smeets
*/


///////////////////////////////////////////////////////////////////////////////
// system includes

#include <avr/io.h>
#include <stdbool.h>


///////////////////////////////////////////////////////////////////////////////
// application-specific includes

#include "ADC.h"


///////////////////////////////////////////////////////////////////////////////
// void adc_Init(void)

void adc_Init(void)
{

	DDRC  = 0x00;        // port C is analog input 

	ADMUX = 0x00;
	ADMUX = _BV(REFS0);  // Vref = AVCC with external capacitor

	// ADC max clock freq == 200 kHz!! Set clock divider in ADCSRA to 64 for 
	// 8 MHz chip clock

	// 16 MHz / 128 = 125 kHz (< 200 kHz)
	ADCSRA  = 0x00;
	ADCSRA  = ( _BV(ADPS2)| _BV(ADPS1) | _BV(ADPS0));  // clock divider 128 for ADC
	ADCSRA |= _BV(ADEN);                   // enable ADC

	ADCSRB = 0x00;
}

///////////////////////////////////////////////////////////////////////////////
// void adc_SelectChannel(uint8_t ADCChannel)

void adc_SelectChannel(uint8_t ADCChannel)
{
	if (ADCChannel <= 15)
	{
		ADMUX &= 0xf0;        // clear previous channel select bits
		ADMUX |= ADCChannel;  // set required channel
	}
}

///////////////////////////////////////////////////////////////////////////////
// void adc_StartConversion(void)

void adc_StartConversion(void)
{
	ADCSRA |= _BV(ADSC); // starts conversion
}



///////////////////////////////////////////////////////////////////////////////
// bool adc_IsBusy(void)

bool adc_IsBusy(void)
{
	bool busy = false;

	if ( (ADCSRA & _BV(ADSC)) != 0)
	{
		busy = true;
	}

	return busy;

}

///////////////////////////////////////////////////////////////////////////////
// void adc_WaitForCompletion(void)

void adc_WaitForCompletion(void)
{
	while ( adc_IsBusy() )	// wait for completion
	{
	}
}


///////////////////////////////////////////////////////////////////////////////
// uint16_t adc_ReadData(void)

uint16_t adc_ReadData(void)
{
	uint16_t adcResult = 0;
	uint16_t hi = 0;  // bits 9..8 of ADC result
	uint16_t lo = 0;  // bits 7..0 of ADC result

	lo = ADCL;  // read ADCL first(!)
	hi = ADCH;	// then read ADCH

	adcResult = (hi << 8 | lo);  // returns 10 bit result

	return adcResult;
}


///////////////////////////////////////////////////////////////////////////////
// uint8_t adc_GetVoltage(uint8_t channel)

uint8_t adc_GetVoltage(uint8_t channel)
{
	uint16_t adcData = 0;

	adc_SelectChannel(channel);
	adc_StartConversion();
	adc_WaitForCompletion();
	
	adcData = adc_ReadData();  // get 10 bits result
	adcData = adcData >> 2;    // make it 8 bits!

	return adcData;
}

