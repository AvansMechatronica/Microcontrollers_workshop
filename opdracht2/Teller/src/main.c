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
	// declareer hier de variabele van het type uint8_t met naam: teller

	initPorts();
	initTimer();

	while (true)
	{
		// voeg hier C-code toe voor een teller
		// -  gebruik PORTD om de tellerstand te displayen.
		// - maak gebruik van de variabele teller	
	}

	
}
