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

#include <arduino.h>
#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>


///////////////////////////////////////////////////////////////////////////////
// application specific includes


#include "ports328.h"
#include "timer0.h"

///////////////////////////////////////////////////////////////////////////////
// program entry point
// Paats hier de code die je in de main functie wilt uitvoeren


void setup(void)
{
	Serial.begin(19200);
	initPorts();

	Serial.println("Setup complete.");
}

void loop(void)

{
	initPorts();

	while(true)
	{
		// voeg hier C-code toe waarmee het gedrag van
		// de switches kan worden onderzocht.
		// Maak hiervoor gebruik van PORTD en PINB

		// N.B.: kijk UITSLUITEND naar de LED's B3..B0!!

		PORTD = 0;
	}

	
}