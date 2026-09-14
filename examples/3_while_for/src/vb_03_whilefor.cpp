/*
*  vb_01_main.c
*
*  Copyright (c) 2024 by Avans Hogeschool.
* 
*  Date:    29-02-2024
*  Author:  R. Smeets & G.A. Harkema
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

///////////////////////////////////////////////////////////////////////////////
// program entry point
void setup(void)
{
	Serial.begin(19200);
	initPorts();

	Serial.println("Setup complete.");


}

uint8_t teller = 0;

void loop(void)
{


	teller = 0;
	while (teller < 16)
	{
		PORTD = teller;
		delay(200);
		teller = teller + 1;
	}


	// deze doet exact hetzelfde, maar nu met een for statement: is makkelijker!

	for(teller = 0; teller < 16; teller = teller + 1)
	{
		PORTD = teller;
		delay(200);
	}

	// aftellen kan ook, begin uiteraard bij 15...

	for(teller = 15; teller > 0; teller = teller - 1)
	{
		PORTD = teller;
		delay(200);
	}
}
