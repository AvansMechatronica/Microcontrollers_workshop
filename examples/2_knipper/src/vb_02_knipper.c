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
	DDRD = 0xff;  // gebruik 8 bits van poort D als OUTput

	while(true)   // herhaal altijd
	{
		PORTD = 0xff;
		delay(100);
		PORTD = 0x00;
		delay(100);
	}

	return 0;  // hier kom ik dus nooit...
}
