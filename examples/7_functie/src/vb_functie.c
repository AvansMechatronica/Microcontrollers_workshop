/*
*  vb_functie.c
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
// voorbeeldfunctie: uint8_t TelBijElkaarop(uint8_t a, uint8_t b)

uint8_t TelBijElkaarop(uint8_t a, uint8_t b)
{
	uint8_t som;  // locale variabele

	som = a + b;

	return som;   // geef resultaat terug aan aanroeper
}


///////////////////////////////////////////////////////////////////////////////
// voorbeeldfunctie: uint8_t uint8_t DupliceerBits30Naar74(uint8_t getal)
//
// de bits 3..0 van getal worden gedupliceerd naar de bits 7..4 van het resultaat.
// bits 3..0 worden ook overgenomen in het resultaat

uint8_t DupliceerBits30Naar74(uint8_t getal)
{

	uint8_t bits30 = 0;
	uint8_t bits74 = 0;
	uint8_t resultaat = 0;

	bits30 = getal & 0x0f;	// isoleer de bits 3..0
	bits74 = bits30 << 4;	// zorg dat deze op bitpositie 7..4 komen

	resultaat = bits74 | bits30;	// voeg de bits 3..0 en 7..4 samen

	return resultaat;		// geef het eindresultaat terug
}


///////////////////////////////////////////////////////////////////////////////
// program entry point


int main(void)
{
	uint8_t teller    = 0;
	uint8_t resultaat = 0;
	uint8_t ledsAan   = 0xff;

    DDRC   = 0x00;  // gebruik 8 bits van poort C als INput
    DDRD   = 0xff;  // gebruik 8 bits van poort D als OUTput

    while(true)  // boolean!
    {

		for (teller = 0; teller < 8; teller++)	// teller loopt van 0..7
		{
			resultaat = TelBijElkaarop(teller, 128);  // functie aanroep, bit 7 is nu altijd AAN

			PORTD = ~resultaat;
			delay(500);
		}

		PORTD = ~ledsAan;
		delay(500);

		for (teller = 0; teller < 16; teller++)	// teller loopt van 0..15
		{
			resultaat = DupliceerBits30Naar74(teller);  // functie aanroep, bit 7 moet nu AAN zijn

			PORTD = ~resultaat;
			delay(500);
		}

    }

    return 0;  // hier kom ik dus nooit...
}


