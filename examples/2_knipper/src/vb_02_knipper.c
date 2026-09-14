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

#include <arduino.h>
#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>


///////////////////////////////////////////////////////////////////////////////
// system includes

#include <arduino.h>
#include <inttypes.h>
#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>

///////////////////////////////////////////////////////////////////////////////
// application specific includes


#include "ports328.h"

///////////////////////////////////////////////////////////////////////////////
// program entry point


void setup(void)
{
	Serial.begin(19200);
	initPorts();

	Serial.println("Setup complete.");
}

void loop(void)

{
	DDRD = 0xff;  // gebruik 8 bits van poort D als OUTput

	while(true)   // herhaal altijd
	{
		PORTD = 0xff;
		delay(100);
		PORTD = 0x00;
		delay(100);
	}

	  // hier kom ik dus nooit...
}
