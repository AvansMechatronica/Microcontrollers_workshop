/*
 * RotarySwitchHandler.cpp
 *
 * Created: 23-5-2023 18:50:46
 *  Author: Roel Smeets
 */ 

///////////////////////////////////////////////////////////////////////////////
// #includes

#include "Arduino.h"
#include "SerialPrintf.h"

#include "EM11PLCSimulator.h"

///////////////////////////////////////////////////////////////////////////////
//

void rotary_EnablePinChangeInterrupt(void)
{
	PCICR  = PCICR	| _BV(PCIE2);	// port D pin changes
	PCMSK2 = PCMSK2 | _BV(PCINT18);	// == bit PD2 = PIN_PROGSEL0
}

///////////////////////////////////////////////////////////////////////////////
// rotary switch interrupt handler for program selection

static uint8_t  g_ProgramSelection = 0;

ISR(PCINT2_vect)	// ISR for port D
{
	uint8_t pin_PS0 = digitalRead(PIN_PROGSEL0);
	uint8_t pin_PS1 = digitalRead(PIN_PROGSEL1);

	if (pin_PS0 != pin_PS1)	// clockwise (CW), see doc of rotary switch
	{
		if (g_ProgramSelection < MAX_PROG)
		{
			g_ProgramSelection++;
		}
	}
	else // counter clockwise (CW), see doc of rotary switch
	{
		if (g_ProgramSelection > 0)
		{
			g_ProgramSelection--;
		}
	}
	
}

///////////////////////////////////////////////////////////////////////////////
//	uint8_t GetProgramSelection(void)

uint8_t rotary_GetProgramSelection(void)
{
	return g_ProgramSelection;
}

