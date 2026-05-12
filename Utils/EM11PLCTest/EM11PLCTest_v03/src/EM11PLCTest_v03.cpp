/*
*  EM11PLCTest_V03.cpp
*
*  Copyright (c) 2022 by Avans Hogeschool.
* 
*  Date:    26-03-2023
*			26-08-2025
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
// application specific includes

#include "delay.h"
#include "ports328.h"
#include "UartLib.h"
#include "timer0.h"


///////////////////////////////////////////////////////////////////////////////
// #define's

#define SYNC_BIT			3
#define ACK_BIT				7
#define FUNCTIONCODE_MASK	(_BV(2) | _BV(1) | _BV(0))

#define LED_SYNC	6

#define BIT_RED		0
#define BIT_ORANGE	1
#define BIT_GREEN	2
#define BIT_BLUE	3


///////////////////////////////////////////////////////////////////////////////
// typedefs

typedef enum
{
	LED_ON,
	LED_OFF
} ledstate_t;


///////////////////////////////////////////////////////////////////////////////
// uint8_t GetInputValue(void)

uint8_t GetInputValue(void)
{
	uint8_t inputValue = 0;
	
	// only 4 lower bits =
	// = Function code in bits 3..0 + sync input state in bit 4
	
	inputValue = PINB & 0x0f;	
	
	return inputValue;
}


///////////////////////////////////////////////////////////////////////////////
// void SetSyncLED(ledstate_t ledState)
// 
// N.B.: ACK LED is hardwired to port D7! So no need to control an ACK LED.

void SetSyncLED(ledstate_t ledState)
{
	uint8_t portValue = 0;
	
	portValue = PIND;
		
	if (ledState == LED_ON)
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
// bool IsSyncPresent(void)

bool IsSyncPresent(void)
{
	uint8_t inputValue = 0;
	bool syncPresent = false;

	inputValue = GetInputValue();
	
	syncPresent = ((inputValue & _BV(SYNC_BIT)) != 0);
	
	SetSyncLED(syncPresent ? LED_ON : LED_OFF);
		
	return syncPresent;	
}

///////////////////////////////////////////////////////////////////////////////
// bool IsSyncEdgeDetected(void)
//
// always returns true, keeps on waiting indefinitely for a RISING edge of SYNC
// perhaps enhance it with a time-out, and return false...?

bool IsSyncEdgeDetected(void)
{
	bool edgeDetected = false;
	
	while (IsSyncPresent() == true)
	{
		// wait until SYNC is released
	}

	while (IsSyncPresent() == false)
	{
		// wait until SYNC is set
	}
	
	// we get here if the SYNC signal is set

	edgeDetected = true;
	
	return edgeDetected;
}


///////////////////////////////////////////////////////////////////////////////
// ACK signal is externally inverted by an open collector driver (inverts...):
// to SET   the ACK signal to the PLC - clear the ACK bit
// to CLEAR the ACK signal to the PLC - set the ACK bit
//
// 25-MAY-2023:
// LevelShifter V4, SMRA 20230506: NON-inverting!
// so change the code to "normal"
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// void SetAcknowledge(void)

void SetAcknowledge(void)
{
	//PORTD = PIND & ~(_BV(ACK_BIT));	// == CLEAR the ACK bit!!
	PORTD = PORTD | _BV(ACK_BIT);		// == SET the ACK bit!! V4
}

///////////////////////////////////////////////////////////////////////////////
// void ClearAcknowledge(void)

void ClearAcknowledge(void)
{
	//PORTD = PIND | _BV(ACK_BIT);	// == SET the ACK bit!!
	PORTD = PORTD & ~(_BV(ACK_BIT));	// == CLEAR the ACK bit!! V4
}


///////////////////////////////////////////////////////////////////////////////
// void WaitUntilSyncReleased(void)

void WaitUntilSyncReleased(void)
{
	bool isSyncPresent = true;
	
	while (isSyncPresent)
	{
		isSyncPresent = IsSyncPresent();
	}
}


///////////////////////////////////////////////////////////////////////////////
// void ControlLamps(uint8_t functionCode)

/*
Function codes:

0:	groen
1:	oranje
2:  rood
3:  groen + oranje
4:  groen + oranje
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
	else if (functionCode == 1)		// 1 = orange
	{
		ledValue = _BV(BIT_ORANGE);
	}
	else if (functionCode == 2)		// 2 = red
	{
		ledValue = _BV(BIT_RED);
	}
	else if ((functionCode == 3) || (functionCode == 4))	// 3, 4 = orange & green
	{
		ledValue = _BV(BIT_ORANGE) | _BV(BIT_GREEN);
	}
	else if ((functionCode == 5) || (functionCode == 6))	// 5, 6 = blue
	{
		ledValue = _BV(BIT_BLUE);
	}
	else if (functionCode == 7)		// 7 = lamp test, all on
	{
		ledValue = _BV(BIT_ORANGE) | _BV(BIT_GREEN) | _BV(BIT_BLUE) | _BV(BIT_RED);
	}
	else
	{
	}
	
	portValue = PIND & 0xf0;
	PORTD = portValue | ledValue;

}

///////////////////////////////////////////////////////////////////////////////
// uint8_t GetLampCode(uint8_t inputValue)

uint8_t GetFunctionCode(uint8_t inputValue)
{
	uint8_t functionCode = 0;
	
	functionCode = inputValue & FUNCTIONCODE_MASK;
	
	return functionCode;
}

void delayms(uint32_t milliSeconds)
{
	timer0_DelayN100us(10 * milliSeconds);
}

///////////////////////////////////////////////////////////////////////////////
// program entry point

int main(void)
{
	uint8_t functionCode = 0;
	uint8_t inputValue = 0;

	initPorts();
	
	// UART output can only be used for debugging ACK / SYNC...
	// as it used also output PD0 and PD1 which
	// are assigned to lamp 0 and lamp 1.
	
	//uart_Init();
	//uart_Printf("EM11 / PLC Test Program V01\n");
	
	/*
	while (true)
	{
		SetAcknowledge();
		delay(1000);
		ClearAcknowledge();
		delay(1000);
	}
	*/
	
	timer0_Init();
	timer0_Start();
	
	ClearAcknowledge();
	
	while (true) // endless loop
	{
		if (IsSyncEdgeDetected())
		{
			inputValue = GetInputValue();
			//uart_Printf("> 1. SYNC received, inputvalue = 0x%04x\n", inputValue);

			functionCode = GetFunctionCode(inputValue);
			//uart_Printf("> 2. function code = %d\n", functionCode);

			ControlLamps(functionCode);

			//uart_Printf("> 3. setting ACK\n");
			SetAcknowledge();
			
			//uart_Printf("> 4. waiting for SYNC release...\n");
			WaitUntilSyncReleased();
			//uart_Printf("> SYNC released!\n");

			//uart_Printf("> 5. clearing ACK\n");
			ClearAcknowledge();

			//uart_Printf("> 6. done!\n");
		}
		else
		{
			// no sync found, do other things
		}
	}

	return 0;
}
