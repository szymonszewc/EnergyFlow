/*
 * pidController.h
 *
 *  Created on: 22 kwi 2021
 *      Author: User
 */

#pragma once

#include <stdint-gcc.h>


extern uint32_t controlValue;
extern float setTemp;
extern float fcTemp;
extern float error;
extern float iError;
extern float dError;
extern float lastError;
extern float Kp;
extern float Ki;
extern float Kd;

void PIDstep();

