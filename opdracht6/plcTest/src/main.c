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
// #define's

#define SYNC_BIT			3
#define ACK_BIT				7
#define FUNCTIONCODE_MASK	(_BV(2) | _BV(1) | _BV(0))

#define LED_SYNC		6

#define BIT_RED			0
#define BIT_YELLOW		1
#define BIT_GREEN		2
#define BIT_BLUE		3

///////////////////////////////////////////////////////////////////////////////
// void SetSyncLED(ledstate_t ledState)
//
// N.B.: ACK LED is hardwired to port D7! So no need to control an ACK LED.

void SetSyncLED(bool LedLOn)
{
	uint8_t portValue = 0;
	
	portValue = PIND;
	
	if (LedLOn)
	{
		portValue = portValue | _BV(LED_SYNC);
	}
	else
	{
		portValue = portValue & (~_BV(LED_SYNC));
	}
	
	PORTD = portValue;
}

///////////////////////////////////////////////////////////////////////////////
// bool IsSyncBitSet(void)

bool IsSyncBitSet(void)
{
	uint8_t syncValue = 0;
	bool syncPresent = false;

	syncValue = PINB & _BV(SYNC_BIT);
	
	if (syncValue == 0)
	{
		syncPresent = false;
		SetSyncLED(false);
	}
	else
	{
		syncPresent = true;
		SetSyncLED(true);
	}

	return syncPresent;	
}

///////////////////////////////////////////////////////////////////////////////
// bool IsSyncEdgeDetected(void)

bool IsSyncEdgeDetected(void)
{
	while (IsSyncBitSet() == true)
	{
	}

	while (IsSyncBitSet() == false)
	{
	}
	
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// void WaitUntilSyncReleased(void)

void WaitUntilSyncReleased(void)
{
	bool isSyncPresent = true;
	
	while (isSyncPresent)
	{
		isSyncPresent = IsSyncBitSet();
	}
}


///////////////////////////////////////////////////////////////////////////////
// void ControlLamps(uint8_t functionCode)

/*
Function codes:

0:	groen
1:	geel
2:  rood
3:  groen + geel
4:  rood  + geel
5:  blauw
6:  blauw
7: 	lamp test (LT), alle lampen aan
*/


void ControlLamps(uint8_t functionCode)
{
	uint8_t ledValue  = 0;
	uint8_t portValue = 0;
	
	if (functionCode == 0)			// 0 =green
	{
		ledValue = _BV(BIT_GREEN);
	}
	else if (functionCode == 1)		// 1 = yellow
	{
		ledValue = _BV(BIT_YELLOW);
	}
	else if (functionCode == 2)		// 2 = red
	{
		ledValue = _BV(BIT_RED);
	}
	else if (functionCode == 3)		// 3 = yellow & green
	{
		ledValue = _BV(BIT_YELLOW) | _BV(BIT_GREEN);
	}
	else if (functionCode == 4)	// 4 = yellow & red
	{
		ledValue = _BV(BIT_YELLOW) | _BV(BIT_RED);
	}
	else if ((functionCode == 5) || (functionCode == 6))	// 5, 6 = blue
	{
		ledValue = _BV(BIT_BLUE);
	}
	else if (functionCode == 7)		// 7 = lamp test, all on
	{
		ledValue = _BV(BIT_YELLOW) | _BV(BIT_GREEN) | _BV(BIT_BLUE) | _BV(BIT_RED);
	}
	else
	{
	}
	
	portValue = PIND & 0xf0;
	PORTD = portValue | ledValue;
}

///////////////////////////////////////////////////////////////////////////////
// uint8_t GetPLCData(void)

uint8_t GetPLCData(void)
{
	uint8_t data = 0;
	
	data = PINB & 0x0f;
	
	return data;
}

///////////////////////////////////////////////////////////////////////////////
// uint8_t GetFunctionCode(uint8_t inputValue)

uint8_t GetFunctionCode(uint8_t inputValue)
{
	uint8_t functionCode = 0;
	
	functionCode = inputValue & FUNCTIONCODE_MASK;
	
	return functionCode;
}


///////////////////////////////////////////////////////////////////////////////
// void SetAcknowledge(void)

void SetAcknowledge(void)
{
	PORTD = PIND | _BV(ACK_BIT);
}

///////////////////////////////////////////////////////////////////////////////
// void ClearAcknowledge(void)

void ClearAcknowledge(void)
{
	PORTD = PIND & ~_BV(ACK_BIT);
}

///////////////////////////////////////////////////////////////////////////////
// program entry point

int main(void)
{
	uint8_t functionCode = 0;
	uint8_t plcData = 0;
	bool syncDetected = false;

	initPorts();

	while (true) // endless loop
	{
		syncDetected = IsSyncEdgeDetected();
		
		if (syncDetected)
		{
			plcData = GetPLCData();
			functionCode = GetFunctionCode(plcData);
			ControlLamps(functionCode);
			SetAcknowledge();
			WaitUntilSyncReleased();
			ClearAcknowledge();
		}
		else
		{
			// no sync found, do other things
		}
	}

	return 0;
}
