/* License

Copyright (c) 2022 ElecompTech

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*/
/*
 * TM1637_.c
 *
 *  Created and Modified on: 2022/4/2
 *  Author: Amin Hosseini
 */

#ifndef TM1637_H_
#define TM1637_H_
#include "stm32f0xx_hal.h"

void TM1637_Init(void);
void TM1637_Demo(void);
void TM1637_DisplayDec(int v, int displaySeparator);
void TM1637_SetBrightness(char brightness);
void TM1637_Start(void);
void TM1637_Stop(void);
void TM1637_ReadResult(void);
void TM1637_WriteByte(unsigned char b);
void TM1637_DelayUsec(unsigned int i);
void TM1637_ClkHigh(void);
void TM1637_ClkLow(void);
void TM1637_DataHigh(void);
void TM1637_DATALow(void);
#endif /* TM1637_H_ */
