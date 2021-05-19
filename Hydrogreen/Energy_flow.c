/*
 * Energy_flow.c
 *
 *  Created on: 2 maj 2021
 *      Author: User
 */

#include "Energy_flow.h"
#include "gpio.h"
#include "tim.h"
#include "rs485.h"
#include "fans.h"
#include "pidController.h"
#include "measurements.h"

EnergyFlow hydros;

void energyflow_init(void)
{
	 hydros.charging=0;
	 HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	 HAL_GPIO_WritePin(SC_ON_GPIO_Port, SC_ON_Pin, RESET);
	 HAL_GPIO_WritePin(FC_DECHARGING_GPIO_Port, FC_DECHARGING_Pin, RESET);
}

void energyflow_step(void)
{
	switch (RS485_RX_VERIFIED_DATA.mode)
	{
	case 0:
		energyflow_mode0();
	break;

	case 1:
		energyflow_preapre_to_race();
	break;

	case 2:
		energyflow_race();
	break;

	case 3:
		energyflow_end_race();
	break;

	default:
		energyflow_emergency();
	break;
	}
}

void energyflow_mode0()
{
	setTemp=100;
	hydros.charging=0;
	HAL_GPIO_WritePin(SC_ON_GPIO_Port, SC_ON_Pin, RESET);
	HAL_GPIO_WritePin(FC_DECHARGING_GPIO_Port, FC_DECHARGING_Pin, RESET);
}

void energyflow_preapre_to_race()
{
	setTemp=80;
	hydros.charging=0;
	HAL_GPIO_WritePin(SC_ON_GPIO_Port, SC_ON_Pin, RESET);
	HAL_GPIO_WritePin(FC_DECHARGING_GPIO_Port, FC_DECHARGING_Pin, RESET);
}

void energyflow_race()
{
	setTemp=60;
	switch(RS485_RX_VERIFIED_DATA.scOn)
	{
	case 0:
		HAL_GPIO_WritePin(SC_ON_GPIO_Port, SC_ON_Pin, RESET);
	break;
	case 1:
		HAL_GPIO_WritePin(SC_ON_GPIO_Port, SC_ON_Pin, SET);
	break;
	default:
		energyflow_emergency();
	break;
	}
	if (VALUES.SC_C.value >= 1500)
	{
		hydros.charging=50;
		TIM3->CCR3=hydros.charging;
	}
	else
	{
		hydros.charging=100;
		hydros.charging=50;
		TIM3->CCR3=hydros.charging;
	}
	if (VALUES.SC_V.value >=3500)
	{
		hydros.charging=0;
		hydros.charging=50;
		TIM3->CCR3=hydros.charging;
	}
	if (VALUES.FC_V.value <=1500)
	{
		hydros.charging=0;
		hydros.charging=50;
		TIM3->CCR3=hydros.charging;
	}
}

void energyflow_end_race()
{
	 HAL_GPIO_WritePin(SC_ON_GPIO_Port, SC_ON_Pin, RESET);
	 HAL_GPIO_WritePin(FC_DECHARGING_GPIO_Port, FC_DECHARGING_Pin, SET);
}

void energyflow_emergency()
{

}
