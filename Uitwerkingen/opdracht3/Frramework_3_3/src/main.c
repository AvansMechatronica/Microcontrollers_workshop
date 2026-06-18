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
// program entry point
// Paats hier de code die je in de main functie wilt uitvoeren

int main(void)
{
	initPorts();
	initTimer();

	PORTD = 0x00;	// all LED's off
	
	const uint8_t SWITCH_MASK = _BV(PB1);	// schakelaar 2 op PB1
	// Dit mag ook 
	// const uint8_t SWITCH_MASK = 0x02;
	
	while (true)
	{
		if ((PINB & SWITCH_MASK) != 0)
		{
			PORTD = 0xFF;			// all LED's on
			delayms(1000);			// exactly 1 second on-time
			PORTD = 0x00;			// all LED's off

			// Wait for release so a long press triggers only once.
			while ((PINB & SWITCH_MASK) != 0)
			{
			}
		}
	}
	
	return 0;
}