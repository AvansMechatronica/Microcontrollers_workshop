/*
 * EM11PLCSimulator.h
 *
 * Created: 23-5-2023 18:56:34
 *  Author: Roel Smeets
 */ 


#ifndef EM11PLCSIMULATOR_H_
#define EM11PLCSIMULATOR_H_

///////////////////////////////////////////////////////////////////////////////
// Arduino pin mapping

#define PIN_MANUALSYNC_IN	6
#define PIN_ACK_IN			7

#define	PIN_PROGSEL3		5
#define	PIN_PROGSEL2		4
#define	PIN_PROGSEL1		3
#define	PIN_PROGSEL0		2

#define PIN_FC2_OUT			10
#define PIN_FC1_OUT			9
#define PIN_FC0_OUT			8

#define PIN_LED2_OUT		13
#define PIN_LED1_OUT		12
#define PIN_LED0_OUT		11

#define PIN_DIP2_IN			A2
#define PIN_DIP1_IN			A1
#define PIN_DIP0_IN			A0

#define PIN_SYNCOUT_OUT		A3


///////////////////////////////////////////////////////////////////////////////
//	#defines

#define ACK_OK					0
#define ACK_ALREADY_SET			1
#define ACK_TIMEOUT				2
#define ACK_RELEASE_TIMEOUT		3
#define ACK_UNDEFINED			100

///////////////////////////////////////////////////////////////////////////////
// maximum number of programs to select with rotary knob

#define MAX_PROG 13


#endif /* EM11PLCSIMULATOR_H_ */