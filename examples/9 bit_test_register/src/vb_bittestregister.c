/*
*  vb_bittestregister.c
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
	DDRB  = 0xf0;	// B: bits 3..0 inputs, bits 7..4 outputs
    DDRD  = 0xff;	// D: gebruik 8 bits van poort D als OUTput

    while(true)
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

    return 0;  // hier kom ik dus nooit...
}


