/*
 * EM11PLCSimulator_v04.cpp
 *
 * Created: 30-6-2020 16:36:38
 * Author : Roel Smeets
 */ 


///////////////////////////////////////////////////////////////////////////////
// #includes

#include "Arduino.h"

#include "SerialPrintf.h"
#include "EM11PLCSimulator.h"
#include "RotarySwitchHandler.h"
#include "OLEDLib.h"
#include "I2CScanner.h"

#include <Wire.h>

///////////////////////////////////////////////////////////////////////////////
// function prototypes

uint8_t SendFunctionCode(uint8_t functionCode, uint16_t delayTimeMs);


///////////////////////////////////////////////////////////////////////////////
//	uint8_t GetProgramSelectionFromHexSwitch(void)

uint8_t GetProgramSelectionFromHexSwitch(void)
{
	uint8_t selection = 0;
	uint8_t pinState = LOW;
	uint8_t ix = 0;
	
	uint8_t pinList[4] = {PIN_PROGSEL0, PIN_PROGSEL1, PIN_PROGSEL2, PIN_PROGSEL3};
	
	for (ix = 0; ix < 4; ix++)
	{
		pinState = digitalRead(pinList[ix]);
		if (pinState == LOW)	// active LOW input
		{
			selection = selection | (0x01 << ix);
		}
	}
	
	return selection;
}

///////////////////////////////////////////////////////////////////////////////
//	uint8_t GetDIPSwitchValue(void)

uint8_t GetDIPSwitchValue(void)
{
	uint8_t value = 0;
	uint8_t pinState = LOW;
	uint8_t ix = 0;
	
	uint8_t pinList[3] = {PIN_DIP0_IN, PIN_DIP1_IN, PIN_DIP2_IN};
	
	for (ix = 0; ix < 3; ix++)
	{
		pinState = digitalRead(pinList[ix]);
		if (pinState == LOW)	// active LOW input, bit is SET!
		{
			value = value | (0x01 << ix);
		}
	}
	
	return value;
}



///////////////////////////////////////////////////////////////////////////////
//	bool IsChanged(uint16_t val1, uint16_t val2)

bool IsChanged(uint16_t val1, uint16_t val2)
{
	return (val1 != val2);
}


///////////////////////////////////////////////////////////////////////////////
//	void InitIOPins(void)

void InitIOPins(void)
{
	pinMode(PIN_MANUALSYNC_IN, INPUT_PULLUP);
	pinMode(PIN_ACK_IN,		   INPUT_PULLUP);
	
	pinMode(PIN_SYNCOUT_OUT,   OUTPUT);

	pinMode(PIN_PROGSEL3, INPUT_PULLUP);
	pinMode(PIN_PROGSEL2, INPUT_PULLUP);
	pinMode(PIN_PROGSEL1, INPUT_PULLUP);
	pinMode(PIN_PROGSEL0, INPUT_PULLUP);
	
	pinMode(PIN_DIP2_IN,  INPUT_PULLUP);
	pinMode(PIN_DIP1_IN,  INPUT_PULLUP);
	pinMode(PIN_DIP0_IN,  INPUT_PULLUP);

	pinMode(PIN_FC2_OUT,  OUTPUT);
	pinMode(PIN_FC1_OUT,  OUTPUT);
	pinMode(PIN_FC0_OUT,  OUTPUT);
	
	pinMode(PIN_LED2_OUT, OUTPUT);
	pinMode(PIN_LED1_OUT, OUTPUT);
	pinMode(PIN_LED0_OUT, OUTPUT);
}


///////////////////////////////////////////////////////////////////////////////
// function definitions


///////////////////////////////////////////////////////////////////////////////
// void SetSync(void)

void SetSync(void)
{
	digitalWrite(PIN_SYNCOUT_OUT, HIGH);
	delay(1);
}

///////////////////////////////////////////////////////////////////////////////
// void ClearSync(void)

void ClearSync(void)
{
	digitalWrite(PIN_SYNCOUT_OUT, LOW);
	delay(1);
}


///////////////////////////////////////////////////////////////////////////////
// bool IsAcknowledgeBitSet(void)

bool IsAcknowledgeBitSet(void)
{
	uint8_t pinState = LOW;
	
	pinState = digitalRead(PIN_ACK_IN);
	
	return (pinState == LOW);
}


///////////////////////////////////////////////////////////////////////////////
// bool IsSyncButtonPressed(void)

bool IsSyncButtonPressed(void)
{
	uint8_t pinState = LOW;
	
	pinState = digitalRead(PIN_MANUALSYNC_IN);
	
	return (pinState == LOW);
}


///////////////////////////////////////////////////////////////////////////////
// void EmitFunctionCode(uint8_t functionCode)

void EmitFunctionCode(uint8_t functionCode)
{
	uint8_t pinState = LOW;
	uint8_t pinList[3] = {PIN_FC0_OUT, PIN_FC1_OUT, PIN_FC2_OUT};
	uint8_t ix = 0;
		
	for (ix = 0; ix < 3; ix++)
	{
		pinState = ((functionCode & _BV(ix)) != 0) ? HIGH : LOW;
		digitalWrite(pinList[ix], pinState);
	}
	
	// we have a slow line driver, L293D, long settling time...
	delay(1);
}


///////////////////////////////////////////////////////////////////////////////
// void SetLedValue(uint8_t ledValue)

void SetLedValue(uint8_t ledValue)
{
	uint8_t pinState = LOW;
	uint8_t ix = 0;
	uint8_t pinList[3] = {PIN_LED0_OUT, PIN_LED1_OUT, PIN_LED2_OUT};	
	
	for (ix = 0; ix < 3; ix++)
	{
		pinState = ((ledValue & _BV(ix)) != 0) ? HIGH : LOW;
		digitalWrite(pinList[ix], pinState);
	}
}


///////////////////////////////////////////////////////////////////////////////
// uint8_t WaitForAcknowledge(uint16_t msecs)

uint8_t WaitForAcknowledge(uint16_t msecs)
{
	bool isAckSet = false;
	uint16_t waitCount = 1000;
	uint16_t result = ACK_UNDEFINED;
	
	isAckSet = IsAcknowledgeBitSet();
	
	while ((isAckSet == false) && (waitCount > 0))
	{
		delay(1);
		waitCount--;
		isAckSet = IsAcknowledgeBitSet();
	}
	
	result = ((waitCount == 0) ? ACK_TIMEOUT : ACK_OK);

	return result;
}


///////////////////////////////////////////////////////////////////////////////
// uint8_t WaitForAcknowledge(uint16_t msecs)

uint8_t WaitUntilAcknowledgeReleased(uint16_t msecs)
{
	bool isAckSet = false;
	uint16_t waitCount = 1000;
	uint16_t result = ACK_UNDEFINED;
	
	isAckSet = IsAcknowledgeBitSet();
	
	while ((isAckSet == true) && (waitCount > 0))
	{
		delay(1);
		waitCount--;
		isAckSet = IsAcknowledgeBitSet();
	}
	
	result = ((waitCount == 0) ? ACK_RELEASE_TIMEOUT : ACK_OK);

	return result;
}


///////////////////////////////////////////////////////////////////////////////
// bool IsManualSyncActive(void)
//
// function returns when SYNC push button is RELEASED!

bool IsManualSyncActive(void)
{
	bool isActive = false;
	
	if (IsSyncButtonPressed())
	{
		while(IsSyncButtonPressed())
		{
			// wait for release of SYNC push button
		}
		isActive = true;
	}
	else
	{
		isActive = false;
	}
	
	return isActive;
}


///////////////////////////////////////////////////////////////////////////////
//	uint8_t SimulationMode_0(void)

uint8_t SimulationMode_0(void)
{
	uint8_t ackResult = ACK_OK;
	uint8_t functionCode = 0;
	uint8_t delayTimeMs  = 0;
	
	ClearSync();	// always start a test with SYNC cleared
	
	functionCode = 7;
	ackResult = SendFunctionCode(functionCode, delayTimeMs);
	if (ackResult != ACK_OK)
	{
		return ackResult;
	}
	
	delay(1000);

	functionCode = 0;
	ackResult = SendFunctionCode(functionCode, delayTimeMs);
	if (ackResult != ACK_OK)
	{
		return ackResult;
	}
	
	delay(1000);
	
	return ackResult;
}


///////////////////////////////////////////////////////////////////////////////
//	uint8_t SendFunctionCode(uint8_t functionCode, uint16_t delayTimeMs)

uint8_t SendFunctionCode(uint8_t functionCode, uint16_t delayTimeMs)
{
	uint16_t ackWaitTimeMs = 1000;
	uint8_t ackResult = ACK_OK;
	bool isAckSet = false;
	
	ClearSync();
	
	isAckSet = IsAcknowledgeBitSet();

	if (isAckSet)
	{
		return ACK_ALREADY_SET;
	}
	
	EmitFunctionCode(functionCode);
	
	delay(delayTimeMs);
	
	SetSync();
	
	delay(delayTimeMs);

	ackResult = WaitForAcknowledge(ackWaitTimeMs);
	
	ClearSync();	// always clear SYNC!
	
	if (ackResult != ACK_OK)
	{
		return ackResult;
	}

	ackResult = WaitUntilAcknowledgeReleased(ackWaitTimeMs);
	
	if (ackResult != ACK_OK)
	{
		return ackResult;
	}
	
	return ACK_OK;
}


///////////////////////////////////////////////////////////////////////////////
//	uint8_t SimulationMode(uint8_t functionCode)

uint8_t SimulationMode(uint8_t functionCode)
{
	uint8_t  ackResult = ACK_UNDEFINED;
	uint16_t delayMs = 500;

	ackResult = SendFunctionCode(functionCode, delayMs);
	if (ackResult != ACK_OK)
	{
		return ackResult;
	}
	
	delay(1000);

	return ackResult;
}


///////////////////////////////////////////////////////////////////////////////
// void SetAllOutputsHigh(bool setHigh)

void SetAllOutputsHigh(bool setHigh)
{
	uint8_t outputValue = 0;
	
	outputValue = (setHigh) ? 0x07 : 0x00;
	
	SetLedValue(outputValue);
	EmitFunctionCode(outputValue);
	
	if (setHigh)
	{
		SetSync();
	}
	else
	{
		ClearSync();
	}
}

///////////////////////////////////////////////////////////////////////////////
// void ToggleOutputs(void)

void ToggleOutputs(void)
{
	uint8_t ix = 0;
	
	for (ix = 0; ix < 100; ix++)
	{
		SetAllOutputsHigh(true);
		SetAllOutputsHigh(false);
	}
}


///////////////////////////////////////////////////////////////////////////////
//	OLED display text strings

const char *OLEDProgramText[] =
{
	"Outputs OFF",		// program 0
	"FC = 0",			// 1
	"FC = 1",			// 2
	"FC = 2",			// 3
	"FC = 3",			// 4
	"FC = 4",			// 5 
	"FC = 5",			// 6
	"FC = 6",			// 7
	"FC = 7",			// 8
	"increment",		// 9
	"simulation",		// 10
	"Outputs ON",		// 11
	"Outputs toggle",	// 12
	"Manual SYNC"		// 13
};


///////////////////////////////////////////////////////////////////////////////
//	int main(void)

int main(void)
{
	uint8_t currentProgram  = 0;
	uint8_t previousProgram = 0;
	
	uint8_t currentStatus  = ACK_UNDEFINED;
	uint8_t previousStatus = ACK_UNDEFINED;
	
	uint8_t currentDIPSwitches  = 0;
	uint8_t previousDIPSwitches = 0;
	
	uint16_t delayTime = 1000;	// delay time in ms
	
	uint8_t functionCode = 0;
	
	const char *msg = NULL;
	char buf[30];
	
	init();
	
	InitIOPins();

	Serial.begin(115200);
	SerialPrintf_P( F("> EM11 PLC Simulator V0.4\n") );

	rotary_EnablePinChangeInterrupt();
	
	Wire.begin();

	I2CScanner();
	
	oled_Init();
	oled_WriteLine(0, "PLC Simulator", ALIGN_CENTER);
	oled_WriteLine(1, "V0.4", ALIGN_CENTER);
	oled_WriteLine(2, "PlatformIO", ALIGN_CENTER);
	
	delay(2000);
	
	oled_Clear();
	
	previousProgram	= MAX_PROG + 1;	// does not exist!
	
	// enter the infinite loop, avoid blocking functions!!
	
	while (true)
	{
		currentProgram  = rotary_GetProgramSelection();	// default starts at 0
		
		if ( IsChanged(currentProgram, previousProgram) )
		{
			oled_Clear();
			
			sprintf_P(buf, PSTR("PROG = %d"), currentProgram);
			oled_WriteLine(0, buf, ALIGN_CENTER);
			msg = OLEDProgramText[currentProgram];
			oled_WriteLine(1, msg, ALIGN_CENTER);
			
			previousProgram	= currentProgram;
			previousDIPSwitches = 100;
			
			currentStatus  = ACK_UNDEFINED;
			previousStatus = ACK_UNDEFINED;

			SetAllOutputsHigh(false);
			
			if (currentProgram == 9)
			{
				functionCode = 0;	// start value of auto-increment
			}
		}
		
		if (currentProgram == 0)
		{
			SetAllOutputsHigh(false);
		}
		else if ((currentProgram >= 1 && currentProgram <= 8))
		{
			delayTime = 0;
			functionCode = currentProgram - 1;
			currentStatus = SendFunctionCode(functionCode, delayTime);
		}
		else if (currentProgram == 9)	// auto-increment
		{
			delayTime = 500;
			sprintf_P(buf, PSTR("FC = %d"), functionCode);
			oled_WriteLine(1, buf, ALIGN_CENTER);
			currentStatus = SendFunctionCode(functionCode, delayTime);
			functionCode = (functionCode + 1) % 8;	// between 0..7
		}
		else if (currentProgram == 10)
		{
			currentDIPSwitches = GetDIPSwitchValue();
			functionCode = currentDIPSwitches;
			if (IsChanged(currentDIPSwitches, previousDIPSwitches))
			{
				sprintf_P(buf, PSTR("simulate FC = %d"), functionCode);
				oled_WriteLine(1, buf, ALIGN_CENTER);
				previousDIPSwitches = currentDIPSwitches;
			}
			SetLedValue(currentDIPSwitches);
			currentStatus = SimulationMode(currentDIPSwitches);
		}
		else if (currentProgram == 11)
		{
			SetAllOutputsHigh(true);
		} 
		else if (currentProgram == 12)
		{
			ToggleOutputs();
		}
		else if (currentProgram == 13)	// manual SYNC
		{
			if (IsManualSyncActive())
			{
				delayTime = 500;
				currentDIPSwitches = GetDIPSwitchValue();
				functionCode = currentDIPSwitches;
				if (IsChanged(currentDIPSwitches, previousDIPSwitches))
				{
					sprintf_P(buf, PSTR("Manual FC = %d"), functionCode);
					oled_WriteLine(1, buf, ALIGN_CENTER);
					previousDIPSwitches = currentDIPSwitches;
				}
				SetLedValue(currentDIPSwitches);
				currentStatus = SendFunctionCode(functionCode, delayTime);
			}
		}
		
		// SerialPrintf_P( F("currentStatus = %d\n"), currentStatus);
		
		// update display ONLY if status has changed, prevents flickering...
		if ( IsChanged(currentStatus, previousStatus) )
		{
			previousStatus = currentStatus;
			if (currentStatus == ACK_OK)
			{
				msg = "OK";
			}
			else if (currentStatus == ACK_ALREADY_SET)
			{
				msg = "ACK already set";
			}
			else if (currentStatus == ACK_TIMEOUT)
			{
				msg = "ACK time out";
			}
			else if (currentStatus == ACK_RELEASE_TIMEOUT)
			{
				msg = "ACK release TMO";
			}
			sprintf_P(buf, PSTR("Status:"));
			oled_WriteLine(2, buf, ALIGN_CENTER);
			sprintf_P(buf, PSTR("%s"), msg);
			oled_WriteLine(3, buf, ALIGN_CENTER);
		}
		
	}

}
