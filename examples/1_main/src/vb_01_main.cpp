/*
*  vb_01_main.c
*
*  Copyright (c) 2024 by Avans Hogeschool.
* 
*  Date:    29-02-2024
*  Author:  R. Smeets & G.A. Harkema
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
	// hier komt je programma...

}
