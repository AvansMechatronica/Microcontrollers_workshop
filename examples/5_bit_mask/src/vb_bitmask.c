/*
*  vb_bitmask.c
*
*  Copyright (c) 2019 by Avans Hogeschool.
* 
*  Date:    23-jan-2019
*  Author:  R. Smeets
*
*
*/


///////////////////////////////////////////////////////////////////////////////
// system includes

#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>


///////////////////////////////////////////////////////////////////////////////
// user includes

#include "delay.h"


///////////////////////////////////////////////////////////////////////////////
// main = startpunt van programma

int main(void)
{
	uint8_t leds  = 0;
	uint8_t mask  = 0;

    DDRB = 0x00;  // gebruik 8 bits van poort B als INput
    DDRD = 0xff;  // gebruik 8 bits van poort D als OUTput
 
    while(true)
    {
		leds = 0x01;

		// even alles aan
		PORTD = ~leds;
		delay(500);

		// gebruik bitwise AND

		for (mask = 0; mask < 16; mask++) // alleen LED's 3..0 selecteren
		{
			leds = 0xff; 			// waarde voor ALLE LED's aan
			leds = leds & mask;		// zet specifieke LED's UIT met masker

			PORTD = ~leds;
			delay(500);
		}


		// gebruik ook bitwise OR erbij:

		for (mask = 0; mask < 16; mask++) // alleen LED's 3..0 selecteren
		{
			leds = 0xff; 			// waarde voor ALLE LED's aan
			leds = leds & mask;		// zet specifieke LED's UIT met masker, mask: 0000 0000 .. 0000 1111

			leds = leds | 0xC0;		// en zet LED's 7 en 6 nu ALTIJD aan! (0xC0 = 1100 0000)

			PORTD = ~leds;
			delay(500);
		}

    }

    return 0;  // hier kom ik dus nooit...
}
