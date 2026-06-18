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

#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

///////////////////////////////////////////////////////////////////////////////
// application specific includes

#include "delay.h"
#include "ports328.h"
#include "timer0.h"

///////////////////////////////////////////////////////////////////////////////
// program entry point
// Paats hier de code die je in de main functie wilt uitvoeren


int main(void)
{
	// declareer hier de variabele van het type uint8_t met naam: teller
	int8_t teller = 0; //let op: SIGNED!!

	initPorts();
	initTimer();

	while (true)
	{
		// tel AF van 15 tot en met 10,
		// gebruik een while statement:

		teller = 15;
		while (teller >= 0)
		{
			PORTD = ~teller;
        	delay(500);
			teller = teller - 1;			
		}


		PORTD = 0x00;	// even laten zien dat we met een for beginnen...
		delay(500);

		// deze doet exact hetzelfde, maar nu met een for statement: is makkelijker!

		for(teller = 15; teller >= 0; teller--)  
        {
			PORTD = ~teller;
        	delay(500);
		}
	}

	return 0;
}
