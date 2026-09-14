/*
*  vb_bittestregister.c
*
*  Copyright (c) 2019 by Avans Hogeschool.
* 
*  Date:    23-jan-2019
*  Author:  R. Smeets & G.A. Harkema
*
*
*/


///////////////////////////////////////////////////////////////////////////////
// system includes

#include <arduino.h>
#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>


///////////////////////////////////////////////////////////////////////////////
// user includes
#include "ports328.h"




///////////////////////////////////////////////////////////////////////////////
// program entry point


void setup(void)
{
	Serial.begin(19200);
	initPorts();

	Serial.println("Setup complete.");
}

void loop(void)
{

	PORTD = ~0x01;				// stap 1:
	while ((~PINB & 0x0f) == 0)	// wacht op een willekeurige knop
	{
	}
	PORTD = ~0x02;
	while ((~PINB & 0x0f) != 0)	// wacht totdat willekeurige knop losgelaten
	{
	}


	PORTD = ~0x03;					// stap 2:
	while ((~PINB & _BV(0)) == 0)	// wacht op knop 0
	{
	}
	PORTD = ~0x04;
	while ((~PINB & _BV(0)) != 0)	// wacht totdat knop 0 losgelaten
	{
	}


	PORTD = ~0x05;					// stap 3:
	while ((~PINB & _BV(3)) == 0)	// wacht op knop 3
	{
	}
	PORTD = ~0x06;
	while ((~PINB & _BV(3)) != 0)	// wacht totdat knop 3 losgelaten
	{
	}

}


