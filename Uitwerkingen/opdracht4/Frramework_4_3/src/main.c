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
// functions

void LedsOn(void)
{
	PORTD = 0xff;
}

void LedsOff(void)
{
	PORTD = 0x00;
}

bool IsKnopIngedrukt(uint8_t knopNummer)
{
	uint8_t sw = 0;
	bool ingedrukt = false;
	uint8_t mask = 0;
	
	sw = ~PINB;
	mask = (1 << knopNummer);
	
	if ((sw & mask) == 0)
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
	uint8_t gewensteKnop = 2;
	
	initPorts();
	initTimer();
	
	PORTD = 0x00;	// all LED's off
	
	while (true)
	{
		if (IsKnopIngedrukt(gewensteKnop))
		{
			LedsOn();
			delayms(500);
			
			LedsOff();
			delayms(500);
		}
	}
	
	return 0;
}
