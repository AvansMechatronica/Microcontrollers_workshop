/*
 * OLEDLib.h
 *
 * Created: 14-3-2023 06:24:46
 *  Author: Roel Smeets
 */ 


#ifndef OLEDLIB_H_
#define OLEDLIB_H_

#define ALIGN_LEFT		0
#define ALIGN_RIGHT		1
#define ALIGN_CENTER	2

void oled_Init(void);
void oled_Clear(void);
void oled_WriteLine(uint8_t row, const char *message, uint8_t align);


#endif /* OLEDLIB_H_ */