/*
 * OLEDLib.cpp
 *
 * Created: 13-3-2023 19:04:52
 *  Author: Roel Smeets
 */ 

///////////////////////////////////////////////////////////////////////////////
// #includes

#include "Arduino.h"
#include "SerialPrintf.h"

#include <SPI.h>
#include <Wire.h>

#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

#include "OLEDLib.h"

#define OLED_NROWS	4
#define OLED_NCOLS	16

#define OLED_XSIZE	128
#define OLED_YSIZE	64


static uint8_t m_rowStart[OLED_NROWS];
static uint8_t m_charWidth = 0;

static SSD1306AsciiAvrI2c m_oled;

// Define proper RST_PIN if required.
#define RST_PIN				(-1)
#define OLED_I2C_ADDRESS	0x3C

///////////////////////////////////////////////////////////////////////////////
// void oled_Init(void)

void oled_Init(void)
{
	int row = 0;
		
	#if RST_PIN >= 0
	m_oled.begin(&Adafruit128x64, OLED_I2C_ADDRESS, RST_PIN);
	#else // RST_PIN >= 0
	m_oled.begin(&Adafruit128x64, OLED_I2C_ADDRESS);
	#endif // RST_PIN >= 0
	
	// Call oled.setI2cClock(frequency) to change from the default frequency.

	memset(m_rowStart, 0, sizeof(m_rowStart));

	m_oled.setFont(ZevvPeep8x16);
	m_oled.clear();
		
	m_charWidth = m_oled.charWidth('a') + 1;	// +1 for interchar spacing
	//SerialPrintf("char width = %d\n", m_charWidth);

	// find out where each row starts:
	
	for (int i = 0; i < OLED_NROWS; i++)
	{
		row = m_oled.row();
		m_rowStart[i] = row;
		m_oled.print("\n");
	}

}

///////////////////////////////////////////////////////////////////////////////
// void oled_Clear(void)

void oled_Clear(void)
{
	m_oled.clear();
}

//////////////////////////////////////////////////////////////////////////////
// oled_WriteLine(uint8_t row, const char *message, uint8_t align)

void oled_WriteLine(uint8_t row, const char *message, uint8_t align)
{
	#define OLED_BUFSIZE (OLED_NCOLS + 1)
	
	uint8_t length = 0;
	uint8_t startCol = 0;
	
	char buf[OLED_BUFSIZE] = "";
	
	length = strlen(message);
	
	switch (align)
	{
		case ALIGN_LEFT:
		startCol = 0;
		break;
		
		case ALIGN_CENTER:
		startCol = (OLED_XSIZE/2) - (length * m_charWidth)/2;
		break;
		
		case ALIGN_RIGHT:
		startCol = OLED_XSIZE - (length * m_charWidth);
		break;
	}

	snprintf_P(buf, OLED_BUFSIZE, PSTR("%s"), message);
	
	m_oled.setCol(0);
	m_oled.setRow(m_rowStart[row]);
	m_oled.clearToEOL();
	
	m_oled.setCol(startCol);
	m_oled.write(buf);
}

