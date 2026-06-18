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
	initPorts();
	initTimer();

	PORTD = 0x00;	// all LED's off
	
	while (true)
	{
		// Alleen schakelaar 1 (PB0) laat de LEDs knipperen.
		// Als schakelaar 1 niet is ingedrukt, blijft de laatste LED-stand behouden.
		if ((PINB & 0x01) != 0)
		{
			PORTD ^= 0xFF;
			delayms(200);
		}
	}
	
	return 0;
}