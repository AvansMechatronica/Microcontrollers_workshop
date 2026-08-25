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
		// Alleen schakelaar 0 (PB0) laat de LEDs knipperen.
		// Andere schakelaars hebben geen effect.
		// Schakelaars zijn actief-laag: ingedrukt = 0, losgelaten = 1.
		if (!(PINB & (1 << PB0)))
		{
			// Schakelaar 0 is ingedrukt: LEDs knipperen
			PORTD = 0xFF;	// alle LEDs aan
			delayms(500);
			PORTD = 0x00;	// alle LEDs uit
			delayms(500);
		}
		else
		{
			// Geen (erkende) schakelaar ingedrukt: LEDs uit
			PORTD = 0x00;
		}
	}

	return 0;
}