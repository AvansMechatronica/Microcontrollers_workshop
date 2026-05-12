/*
*  UartLib.c
*
*  Copyright (c) 2008 by Avans Hogeschool.
* 
*  Date:    17-nov-2017
*  Author:  Roel Smeets
*/


///////////////////////////////////////////////////////////////////////////////
// system includes

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

///////////////////////////////////////////////////////////////////////////////
// application-specific includes

#include "UartLib.h"


///////////////////////////////////////////////////////////////////////////////
// constants

//static const uint8_t BaudrateFactor = 103;	// 16 MHz Arduino, 9600 bps
static const uint8_t BaudrateFactor = 16;		// 16 MHz Arduino, 115200 bps, double speed mode

///////////////////////////////////////////////////////////////////////////////
// user defined interrupt handler, called when byte is received by UART

static INTERRUPTHANDLER g_InterruptHandler = NULL;


///////////////////////////////////////////////////////////////////////////////
// initialize serial communications port hardware, settings: 9600,   N, 8, 1
// asynchronous normal mode

// initialize serial communications port hardware, settings: 115200, N, 8, 1
// asynchronous double speed mode


void uart_Init(void)
{
	UBRR0H = BaudrateFactor >> 8;
	UBRR0L = BaudrateFactor;
	UCSR0B = (_BV(RXEN0)  | _BV(TXEN0) |_BV(RXCIE0));
	UCSR0C = (_BV(UCSZ01) | _BV(UCSZ00));
	
	UCSR0A = _BV(U2X0);	// use double speed mode at high baudrates
}


///////////////////////////////////////////////////////////////////////////////
// returns true if UART transmit buffer is empty

bool uart_IsTransmitBufferEmpty(void)
{
    bool isEmpty = ((UCSR0A & _BV(UDRE0)) != 0);

    return isEmpty;
}


///////////////////////////////////////////////////////////////////////////////
// send a byte

void uart_SendByte(char byteToSend)
{
    while ( uart_IsTransmitBufferEmpty() == false )
    {
    }

    UDR0 = byteToSend;
}


///////////////////////////////////////////////////////////////////////////////
// send a 0-terminated string to serial port

void uart_SendString(char* stringToSend)
{
    long length = strlen(stringToSend);
    long ix     = 0;
	
	if (length > MAX_MESSAGE_LENGTH)  // make output student proof
	{
		length = MAX_MESSAGE_LENGTH;
	}

    for (ix = 0; ix < length; ix++)
    {
        uart_SendByte(*(stringToSend + ix));
    }
}


///////////////////////////////////////////////////////////////////////////////
//	install user defined receive interrupt handler

void uart_InstallInterruptHandler(INTERRUPTHANDLER handler)
{
	g_InterruptHandler = handler;
}

///////////////////////////////////////////////////////////////////////////////
//	hardware interrupt serial line receive handler

ISR(USART_RX_vect)
{
	if (g_InterruptHandler != NULL)			// if valid user handler defined
	{
		uint8_t byteReceived = UDR0;		
		g_InterruptHandler(byteReceived);	// then call user handler, return byte received
	}
}

///////////////////////////////////////////////////////////////////////////////
// void uart_Printf(const char *format, ...)
// behaves as the C-standard printf, outputs string to serial port of Arduino

void uart_Printf(const char *format, ...)
{
	#define BUFSIZE 90
	
	va_list ap;
	char buffer[BUFSIZE];

	va_start(ap, format);
	vsnprintf(buffer, BUFSIZE, format, ap);
	va_end(ap);

	uart_SendString(buffer);
}
