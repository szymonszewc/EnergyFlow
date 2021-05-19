/*
 * pidController.c
 *
 *  Created on: 22 kwi 2021
 *      Author: User
 */

#include "pidController.h"
#include "measurements.h"
#include "rs485.h"
#include "fans.h"

 float setTemp=15;
 float fcTemp=0;
 float error=0;
 float iError=0;
 float dError=0;
 float lastError=0;
 uint8_t Kp=2;
 uint8_t Ki=1;
 uint8_t Kd=2;
 static uint32_t value=0;


void PIDstep()
{
	//setTemp=RS485_RX_VERIFIED_DATA.fcPrepareToRaceMode;
	//setTemp=100;
	fcTemp=VALUES.FC_TEMP.value;
	error=fcTemp-setTemp;
	dError=error-lastError;
	iError=iError+lastError;
	lastError=error;
	if(fcTemp<setTemp)
	{
		value=0;
		iError=0;
	}
	if(iError>=150)
	{
		iError=150;
	}
	value=Kp*error+Ki*iError+Kd*dError;
	if(fcTemp<setTemp)
	{
		value=0;
	}
	if(value>=255)
	{
		FANS.controlValue=255;
	}
	else
	{
		FANS.controlValue=value;
	}

}
