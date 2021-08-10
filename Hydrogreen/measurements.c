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
static void averaging_Values(void);
/*
 * Inicjalizacja adc z dma oraz stałych filtrujących dla filtru
 */
void adc_init(void)
{
  HAL_ADC_Start_DMA(&adcChannel, (uint32_t*) adcDataToCalculate, 4);
  VALUES.FC_Temp_Const = 255;
  VALUES.FC_V_Const = 99;
  VALUES.SC_C_Const = 225;
  VALUES.SC_V_Const = 99;
}
/*
 * Funkcja przelicza wartosci z ADC na wartosci uzyteczne
 */
static void calculateValues(void)
{
  //Przelicza wartosci z ADC na temperature w stopniach Celsjusza, napiecie i prad
  VALUES.FC_Temp_to_average = (((4095.0f - (float) adcDataToCalculate[0]) * 20))
      / 300.0f; //zależność wyznaczona eksperymentalnie w sali
  VALUES.SC_V_to_average = (((float) adcDataToCalculate[1]) * 65.2f) / 4095.0f;
  // VALUES.SC_C_to_average = (((float) adcDataToCalculate[2]) / 4095.0f) * 5.0f;
  VALUES.SC_C_to_average =
      ((((float) adcDataToCalculate[2] * 5.22f) / 4095.0f));
  VALUES.FC_V_to_average = (((float) adcDataToCalculate[3]) * 65.2f) / 4095.0f;
}
/*
 * Funkcja filtrujaca pomiary
 */
static void averaging_Values(void)
{
  VALUES.FC_TEMP.value = (VALUES.prev_FC_Temp * (VALUES.FC_Temp_Const - 1)
      + VALUES.FC_Temp_to_average) / VALUES.FC_Temp_Const;
  VALUES.SC_V.value = (VALUES.prev_SC_V * (VALUES.SC_V_Const - 1)
      + VALUES.SC_V_to_average) / VALUES.SC_V_Const;
  VALUES.SC_C.value = (VALUES.prev_SC_C * (VALUES.SC_C_Const - 1)
      + VALUES.SC_C_to_average) / VALUES.SC_C_Const;
  VALUES.FC_V.value = (VALUES.prev_FC_V * (VALUES.FC_V_Const - 1)
      + VALUES.FC_V_to_average) / VALUES.FC_V_Const;
  VALUES.prev_FC_Temp = VALUES.FC_Temp_to_average;
  VALUES.prev_FC_V = VALUES.FC_V_to_average;
  VALUES.prev_SC_C = VALUES.SC_C_to_average;
  VALUES.prev_SC_V = VALUES.SC_V_to_average;
}
void adc_step()
{
  calculateValues();
  averaging_Values();
}
