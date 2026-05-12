/*
*  vb_register.c
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
// program entry point


int main(void)
{
	uint8_t teller    = 0;
	uint8_t ledsAan   = 0xff;

    DDRC   = 0x00;  // gebruik 8 bits van poort C als INput
    DDRD   = 0xff;  // gebruik 8 bits van poort D als OUTput

	// "misbruik" van Data Direction Register D (DDRD) als voorbeeld van bitmanipulaties 
	// in een register. Normaal gesproken moet de LED's natuurlijk aan- of uit worden
	// gezet met PORTD (i.p.v. DDRD)!!

	PORTD = ~ledsAan; // alle LED's aan
	delay(500);

	DDRD = 0x00;	// poort D wordt INPUT, LED's worden niet meer aangestuurd!

    while(true)
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

    return 0;  // hier kom ik dus nooit...
}


