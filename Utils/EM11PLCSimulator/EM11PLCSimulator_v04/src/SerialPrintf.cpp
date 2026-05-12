/*
 * SerialPrintf.cpp
 *
 * Created: 19-4-2020 19:17:00
 *  Author: Roel Smeets
 */ 


///////////////////////////////////////////////////////////////////////////////
// #includes

#include "Arduino.h"
#include "SerialPrintf.h"

///////////////////////////////////////////////////////////////////////////////
// void SerialPrintf_P(const char *Format, ...)
//
// just use it like standard C printf! 

void SerialPrintf(const char *Format, ...)
{
	char msg[S_PRINTBUFSIZE];
	
	va_list args;
	
	va_start(args, Format);
	vsnprintf(msg, S_PRINTBUFSIZE, Format, args);
	va_end(args);
	
	Serial.print(msg);
}

///////////////////////////////////////////////////////////////////////////////
// void SerialPrintf_P(const __FlashStringHelper *Format, ...)
//
// just use it like standard C printf! Requires format string from flash
// memory, as in F("some string")

void SerialPrintf_P(const __FlashStringHelper *Format, ...)
{
	char msg[S_PRINTBUFSIZE];
	
	va_list args;
	
	va_start(args, Format);
	vsnprintf_P(msg, S_PRINTBUFSIZE, (const char *)Format, args);
	va_end(args);
	
	Serial.print(msg);
}

