/*
*  vb_register.c
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
// global variables
uint8_t teller    = 0;
uint8_t ledsAan   = 0xff;


///////////////////////////////////////////////////////////////////////////////
// program entry point


void setup(void)
{
	Serial.begin(19200);
	initPorts();

	Serial.println("Setup complete.");

	PORTD = ~ledsAan; // alle LED's aan
	delay(500);

}


void loop(void)
{


	DDRD = 0xf0;	// bits 7..4 worden output
	delay(500);

	DDRD = 0x00;	// alles weer input
	delay(500);

	// bits 0..3 een voor een OUTput:
	for (teller = 0; teller < 4; teller++)
	{
		DDRD = DDRD | _BV(teller);
		delay(500);
	}
	
	// bits 0..3 een voor een weer INput:
	for (teller = 0; teller < 4; teller++)
	{
		DDRD = DDRD & ~(_BV(teller));
		delay(500);
	}

}


