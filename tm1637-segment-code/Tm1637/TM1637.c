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
#include "TM1637.h"
#include "main.h"
#include "gpio.h"

#include "stm32f0xx_hal.h"

const char segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
    0x00
};

void TM1637_ClkHigh(void)
{
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_SET);
}

void TM1637_ClkLow(void)
{
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET);
}

void TM1637_DataHigh(void)
{
    HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_SET);
}

void TM1637_DataLow(void)
{
    HAL_GPIO_WritePin(DATA_GPIO_Port, DATA_Pin, GPIO_PIN_RESET);
}

void TM1637_Demo(void)
{
	uint8_t i = 0;

	TM1637_Init();
	TM1637_SetBrightness(8);

	while(1){
		TM1637_DisplayDec(i++, 0);
	}
}


void TM1637_Init(void)
{
	MX_GPIO_Init();
    TM1637_SetBrightness(8);
}


void TM1637_DisplayDec(int v, int displaySeparator)
{
    unsigned char digitArr[4];
    for (int i = 0; i < 4; ++i) {
        digitArr[i] = segmentMap[v % 10];
        if (i == 2 && displaySeparator) {
            digitArr[i] |= 1 << 7;
        }
        v /= 10;
    }

    TM1637_Start();
    TM1637_WriteByte(0x40);
    TM1637_ReadResult();
    TM1637_Stop();

    TM1637_Start();
    TM1637_WriteByte(0xc0);
    TM1637_ReadResult();

    for (int i = 0; i < 4; ++i) {
        TM1637_WriteByte(digitArr[3 - i]);
        TM1637_ReadResult();
    }

    TM1637_Stop();
}

// Valid brightness values: 0 - 8.
// 0 = display off.
void TM1637_SetBrightness(char brightness)
{
    // Brightness command:
    // 1000 0XXX = display off
    // 1000 1BBB = display on, brightness 0-7
    // X = don't care
    // B = brightness
    TM1637_Start();
    TM1637_WriteByte(0x87 + brightness);
    TM1637_ReadResult();
    TM1637_Stop();
}

void TM1637_Start(void)
{
    TM1637_ClkHigh();
    TM1637_DataHigh();
    TM1637_DelayUsec(2);
    TM1637_DataLow();
}

void TM1637_Stop(void)
{
    TM1637_ClkLow();
    TM1637_DelayUsec(2);
    TM1637_DataLow();
    TM1637_DelayUsec(2);
    TM1637_ClkHigh();
    TM1637_DelayUsec(2);
    TM1637_DataHigh();
}

void TM1637_ReadResult(void)
{
    TM1637_ClkLow();
    TM1637_DelayUsec(5);

    TM1637_ClkHigh();
    TM1637_DelayUsec(2);
    TM1637_ClkLow();
}

void TM1637_WriteByte(unsigned char b)
{
	for (int i = 0; i < 8; ++i) {
		TM1637_ClkLow();
		if (b & 0x01) {
			TM1637_DataHigh();
		}
		else {
			TM1637_DataLow();
		}
		TM1637_DelayUsec(3);
		b >>= 1;
		TM1637_ClkHigh();
		TM1637_DelayUsec(3);
	}
}

void TM1637_DelayUsec(unsigned int i)
{
    for (; i>0; i--) {
        for (int j = 0; j < 500; ++j) {
					__NOP();
        }
    }
}



