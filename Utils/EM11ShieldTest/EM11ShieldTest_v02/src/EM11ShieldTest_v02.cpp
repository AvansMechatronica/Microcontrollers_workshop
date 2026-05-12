/*
*  EM11ShieldTest.c
*
*  Copyright (c) 2022 by Avans Hogeschool.
* 
*  Date:    28-12-2022
*  Author:  R. Smeets
*
*/


///////////////////////////////////////////////////////////////////////////////
// system includes

#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

///////////////////////////////////////////////////////////////////////////////
// application specific includes

#include "delay.h"
#include "ports328.h"
#include "timer0.h"

void delayms(uint32_t milliSeconds);


///////////////////////////////////////////////////////////////////////////////
// 

void DisplayLed(uint8_t value)
{
	PORTD = value;
}

///////////////////////////////////////////////////////////////////////////////
// uint8_t GetSwitchValue(void)

uint8_t GetSwitchValue(void)
{
	uint8_t switchValue = 0;
	
	switchValue = ~PINB & 0x0f;
	
	return switchValue;
}

///////////////////////////////////////////////////////////////////////////////
// 

void WalkLeft(void)
{
	uint8_t ix;
	uint8_t value = 0x01; 
	uint16_t delayTime = 500;


	for(ix = 0; ix < 8; ix++)
	{
		DisplayLed(value);
		delayms(delayTime);
		value = value << 1;
	}
}


///////////////////////////////////////////////////////////////////////////////
// 

void WalkRight(void)
{
	uint8_t ix;
	uint8_t value = 0x80; 
	uint16_t delayTime = 500;

	for(ix = 0; ix < 8; ix++)
	{
		DisplayLed(value);
		delayms(delayTime);
		value = value >> 1;
	}
}

void delayms(uint32_t milliSeconds)
{
	timer0_DelayN100us(10 * milliSeconds);
}


uint8_t ReadInput(void)
{
	uint8_t val = 0;
	
	val = PINC & 0x07;
	
	return val;	
}

void WriteOutput(uint8_t val)
{
	uint8_t portValue = 0;
	
	portValue = PINC;
	portValue = portValue & ~0x38; // clear output bits
	
	portValue = portValue | (val << 3); // update output bits
	portValue = portValue | 0x07; //re-enable pull-ups
	
	PORTC = portValue;
		
}

///////////////////////////////////////////////////////////////////////////////
// program entry point

int main(void)
{
	uint8_t switches = 0;
	uint16_t delayTime = 500;

	initPorts();
	
	timer0_Init();
	timer0_SetCompareValue(200 - OCR0_CALL_COMPENSATION);
	timer0_Start();

	/*
	DDRC  = 0x38;	// bit 0,1,2 = input, 3,4,5 = output
	PORTC = 0x07;	// enable pullup on bit 0, 1, 2;
	
	while (true)
	{
		switches = ReadInput();
		WriteOutput(switches);
	}
	
	
	while (true)
	{
		PORTD = 0x00;
		delayms(500);
		PORTD = 0xff;
		delayms(500);
	}
	*/
	
	while (true) // endless loop
	{
		switches = GetSwitchValue();

		if (switches == 0)
		{
			DisplayLed(0xff);  
			delayms(delayTime);
			DisplayLed(0x00);  
			delayms(delayTime);
		}
		else if (switches == 1)
		{
			WalkLeft();
		}
		else if (switches == 2)
		{
			WalkRight();
		}
		else
		{
			DisplayLed(0x55);
			delayms(delayTime);
			DisplayLed(0xaa);
			delayms(delayTime);
		}
	}

	return 0;
}
