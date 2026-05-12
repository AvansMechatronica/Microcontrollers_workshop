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
// program entry point
int main(void)
{
	uint8_t teller = 0;

	DDRD   = 0xff;  // gebruik 8 bits van poort D als OUTput
	teller = 0;

	while(true)  // herhaal altijd
	{

		// tel elke keer van 0 tot en met 15 (dus TOT 16),
		// gebruikt een while statement:

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

	return 0;  // hier kom ik dus nooit...
}
