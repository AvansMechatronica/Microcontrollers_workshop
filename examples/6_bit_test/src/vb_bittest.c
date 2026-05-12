/*
*  vb_bittest.c
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
	uint8_t count = 0;
	uint8_t mask  = 0x80;	// bit 7

    DDRB = 0x00;  // gebruik 8 bits van poort B als INput
    DDRD = 0xff;  // gebruik 8 bits van poort D als OUTput
 
    while(true)
    {
		leds = 0x01;

		// even alles aan
		PORTD = ~leds;
		delay(500);


		// gebruik bitwise OR erbij:

		for (count = 0; count < 16; count++) // alleen LED's 3..0 selecteren
		{
			if ((count & 0x01) != 0)	// als bit 0 gelijk is aan 1
			{
				leds = count | mask;	// dan gaat LED 7 ook aan
			}
			else
			{
				leds = count & ~mask;	// anders LED 7 uitzetten
			}

			PORTD = ~leds;
			delay(500);
		}

    }

    return 0;  // hier kom ik dus nooit...
}
