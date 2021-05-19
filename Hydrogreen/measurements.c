/*
 * measurements.c
 *
 *  Created on: Apr 14, 2021
 *      Author: User
 */
#include "adc.h"
#include "measurements.h"

#define adcChannel hadc2

uint16_t adcDataToCalculate[4];
MEASUREMENTS VALUES;

static void calculateValues(void);

void adc_init(void)
{
  HAL_ADC_Start_DMA(&adcChannel, (uint32_t*) adcDataToCalculate, 4);
}

static void calculateValues(void)
{
	VALUES.FC_TEMP.value=(((4095.0-(float)adcDataToCalculate[0])*20))/300;
	VALUES.SC_V.value=((float)adcDataToCalculate[1]*60)/4095;
	VALUES.SC_C.value=((float)adcDataToCalculate[2]*5)/4095;
	VALUES.FC_V.value=((float)adcDataToCalculate[3]*60)/4095;
}
void adc_step()
{
	calculateValues();
}
