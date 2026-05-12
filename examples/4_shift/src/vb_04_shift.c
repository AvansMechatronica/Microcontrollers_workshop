/*
*  vb_01_main.c
*
*  Copyright (c) 2024 by Avans Hogeschool.
* 
*  Date:    29-02-2024
*  Author:  R. Smeets
*
*/


///////////////////////////////////////////////////////////////////////////////
// system includes

#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>


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

///////////////////////////////////////////////////////////////////////////////
// main = startpunt van programma

int main(void)
{
	uint8_t leds  = 0;
	uint8_t count = 0;
	uint8_t mask  = 0;

	DDRB   = 0x00;  // gebruik 8 bits van poort B als INput
	DDRD   = 0xff;  // gebruik 8 bits van poort D als OUTput
	

	leds = 0x01;  // beginwaarde

	while(true)
	{
		leds = 0x01;

		// shift left (7x, NIET 8!)
		for (count = 0; count < 7; count++)
		{
			PORTD = leds;
			delay(200);
			leds = leds << 1;
		}

		// shift right (7x, NIET 8!)
		for (count = 0; count < 7; count++)
		{
			PORTD = leds;
			delay(200);
			leds = leds >> 1;
		}

		PORTD = leds;
		delay(100);

		// gebruik bitwise AND

		for (mask = 0; mask < 16; mask++) // alleen LED's 3..0 selecteren
		{
			leds = 0xff; 			// waarde voor alle LED's aan
			leds = leds & mask;		// selectie
			PORTD = leds;
			delay(200);
		}

		delay(100);

		// gebruik bitwise AND
		
		for (mask = 0; mask < 16; mask++) // maak masker
		{
			leds = 0xff; 			// waarde voor alle LED's aan
			leds = leds & (mask << 4);	// maar selecteer nu de BOVENSTE 4 LED's!!
			PORTD = leds;
			delay(200);
		}

	}

	return 0;  // hier kom ik dus nooit...
}
