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

	bool sw3_was_pressed = false;

	while (true)
	{
		// Opdracht 4: uitsluitend schakelaar 3 (PB3) heeft deze functie.
		// Schakelaars zijn active-low (indrukken = laag signaal).
		bool sw3_pressed = ((PINB & (1 << 3)) == 0);

		if (sw3_pressed)
		{
			PORTD = 0xFF;           // LEDs aan zolang schakelaar 3 ingedrukt is
			sw3_was_pressed = true;
		}
		else if (sw3_was_pressed)
		{
			// Schakelaar 3 is net losgelaten: nog 1 seconde LEDs aan houden
			delayms(1000);
			PORTD = 0x00;           // LEDs uit
			sw3_was_pressed = false;
		}
	}

	return 0;
}