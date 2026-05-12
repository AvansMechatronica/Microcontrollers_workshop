/*
 * SerialPrintf.h
 *
 * Created: 19-4-2020 19:25:10
 *  Author: Roel Smeets
 */ 


#ifndef _SERIALPRINTF_H_
#define _SERIALPRINTF_H_

///////////////////////////////////////////////////////////////////////////////
// #defines

#define S_PRINTBUFSIZE 120

///////////////////////////////////////////////////////////////////////////////
// function prototypes

void SerialPrintf  (const char *Format, ...);
void SerialPrintf_P(const __FlashStringHelper *Format, ...);

#endif /* _SERIALPRINTF_H_ */
