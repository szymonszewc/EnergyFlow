/*
 * measurement.h
 *
 *  Created on: 11 kwi 2021
 *      Author: User
 */

#pragma once

#include <stdint-gcc.h>

extern uint16_t adcDataToCalculate[4];
typedef struct
{
	union
	{
		float value;
		uint8_t array[4];
	} FC_TEMP;
	union
	{
		float value;
		uint8_t array[4];
	} FC_V;
	union
	{
		float value;
		uint8_t array[4];
	} SC_V;
	union
	{
		float value;
		uint8_t array[4];
	} SC_C;
} MEASUREMENTS;
extern MEASUREMENTS VALUES;
extern void adc_init(void);
extern void adc_step(void);

