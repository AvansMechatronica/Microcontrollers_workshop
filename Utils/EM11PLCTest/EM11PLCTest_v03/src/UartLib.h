/*
*  UartLib.h
*
*  Copyright (c) 2009 by Avans Hogeschool.
* 
*  Date:    31-mar-2009
*  Author:  Roel Smeets
*/


#ifndef _UARTLIB_H
#define _UARTLIB_H

#include <stdbool.h>


///////////////////////////////////////////////////////////////////////////////
// define's

#define MAX_MESSAGE_LENGTH 81


///////////////////////////////////////////////////////////////////////////////
// type definitions

typedef	void (*INTERRUPTHANDLER)(uint8_t byteReceived);

///////////////////////////////////////////////////////////////////////////////
// function prototypes

void uart_Init(void);
bool uart_IsTransmitBufferEmpty(void);
void uart_SendByte(char byteToSend);
void uart_SendString(char* stringToSend);
uint8_t uart_GetCommand(void);
void uart_InstallInterruptHandler(INTERRUPTHANDLER handler);
void uart_Printf(const char *format, ...);

#endif	// _UARTLIB_H
