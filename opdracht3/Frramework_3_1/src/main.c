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
		// voeg hier de uitwerking in van de opdracht(en)
	}
	
	return 0;
}