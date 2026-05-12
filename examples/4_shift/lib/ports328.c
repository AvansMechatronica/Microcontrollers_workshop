/*
*  ports328.c
*
*  Copyright (c) 2012 by Avans Hogeschool
*
*  Date:     27-mar-2012
*  Author:   Gerbrandt Schor
*
*  IO ports for Arduino Uno board. Uses:
*      8-bit output on port D (bits 7..0)
*      4-bit input  on port B (bits 3..0)
*/


///////////////////////////////////////////////////////////////////////////////
// system includes

#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>


///////////////////////////////////////////////////////////////////////////////
// application specific includes

#include "ports328.h"


///////////////////////////////////////////////////////////////////////////////
// void portsInit(void)

void initPorts(void)
{
	//output: PORTD 7..0
	//input:  PINB  3..0

	DDRD = 0xFF;	// D: all outputs
	DDRB = 0x00;	// B: all inputs
}
