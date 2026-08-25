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
	
	while (true)
	{
		uint8_t led;

		for (led = 0; led < 8; led++)
		{
			PORTD |= (1 << led);
			delay(1000);
		}

		for (led = 0; led < 8; led++)
		{
			PORTD &= ~(1 << led);
			delay(1000);
		}
	}
	
	return 0;
}