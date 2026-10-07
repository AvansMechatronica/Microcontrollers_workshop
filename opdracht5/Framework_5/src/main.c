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
// definieer vanaf hier de gevraagde functies

void LedsOn(void)
{
	// TODO
}

void LedsOff(void)
{
	// TODO
}

void SetSyncLed(bool ledOn)
{
		// TODO
}

bool IsSyncBitSet(void)
{
	return false;
}

bool IsSyncDetected(void)
{
	// TODO
	return false;
}

void WaitUntilSyncReleased(void)
{
	// TODO
}

void ControlLamps(uint8_t functionCode)
{
	// TODO	
}

uint8_t GetPLCData(void)
{
	return 0;
}


///////////////////////////////////////////////////////////////////////////////
// program entry point

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
