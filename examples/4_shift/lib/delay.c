/*
*  Copyright (c) 2013, 2022 by Avans Hogeschool.
* 
*  Date:    06-feb-2013
*			28-dec-2022
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
// application includes

#include "delay.h"

///////////////////////////////////////////////////////////////////////////////
// void delay(uint32_t count)

void delay(uint32_t count)
{
	volatile int i = 0;
	volatile int j = 0;
	volatile int k = 0;
	
	for (i = 0; i < 1000; i++)
	{
		for (j = 0; j < count; j++)
		{
			k++;
		}
	}
}

