/*
*  ADCControl.h
*
*  Copyright (c) 2011 by Avans Hogeschool.
* 
*  Date:    21-nov-2011
*  Author:  Roel Smeets
*/

#ifndef _ADC_H
#define _ADC_H

#include <stdbool.h>

///////////////////////////////////////////////////////////////////////////////
// function prototypes

void adc_Init(void);
void adc_SelectChannel(uint8_t ADCChannel);
void adc_StartConversion(void);
bool adc_IsBusy(void);
void adc_WaitForCompletion(void);
uint16_t adc_ReadData(void);
uint8_t  adc_GetVoltage(uint8_t channel);

#endif  // _ADC_H
