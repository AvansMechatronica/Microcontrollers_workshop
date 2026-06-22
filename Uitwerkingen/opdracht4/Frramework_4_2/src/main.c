/*
*  main.c
*
*  Copyright (c) 2024 by Avans Hogeschool.
* 
*  Date:    29-02-2024
*  Author:  R. Smeets & Gerard Harkema
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

///////////////////////////////////////////////////////////////////////////////
// application specific includes

void LedsOn(void)
{
	PORTD = 0xff;
}

void LedsOff(void)
{
	PORTD = 0x00;
}

bool IsEenKnopIngedrukt(void)
{
	uint8_t sw = 0;
	bool ingedrukt = false;
	
	sw = ~PINB;
	
	if ((sw & 0x0f) == 0)
	{
		ingedrukt = false;
	}
	else
	{
		ingedrukt = true;
	}
	
	return ingedrukt;
}

///////////////////////////////////////////////////////////////////////////////
// program entry point

int main(void)
{
	initPorts();
	initTimer();
	
	PORTD = 0x00;	// all LED's off
	
	while (true)
	{
		if (IsEenKnopIngedrukt())
		{
			LedsOn();
			delayms(500);
			
			LedsOff();
			delayms(500);
		}
	}
	
	return 0;
}
