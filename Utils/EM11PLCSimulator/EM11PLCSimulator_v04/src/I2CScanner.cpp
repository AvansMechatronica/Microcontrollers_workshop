/*
 * I2CScanner.cpp
 *
 * Created: 23-5-2023 18:58:48
 *  Author: Roel Smeets
 */ 

///////////////////////////////////////////////////////////////////////////////
// #includes

#include "Arduino.h"
#include <Wire.h>


///////////////////////////////////////////////////////////////////////////////
//	void I2Cscanner(void)

void I2CScanner(void)
{
	byte error = 0;
	byte address = 0;
	int nDevices = 0;
	
	Serial.println("Scanning...");
	
	nDevices = 0;
	
	for(address = 1; address < 127; address++ )
	{
		//SerialPrintf("address == %3d\n", address);
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
		if (error == 0)
		{
			Serial.print("I2C device found at address 0x");
			if (address<16)
			{
				Serial.print("0");
			}
			Serial.println(address,HEX);
			nDevices++;
		}
		else if (error==4)
		{
			Serial.print("Unknown error at address 0x");
			if (address<16) {
				Serial.print("0");
			}
			Serial.println(address,HEX);
		}
	}
	if (nDevices == 0)
	{
		Serial.println("No I2C devices found\n");
	}
	else
	{
		Serial.println("done\n");
	}
}