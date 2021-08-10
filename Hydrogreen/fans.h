/*
 * fans.h
 *
 *  Created on: 14 kwi 2021
 *      Author: User
 */

#pragma once

#include <stdint-gcc.h>

void fansStep(void);
void fans_init(void);

typedef struct
{
  uint16_t rpm_1;
  uint16_t rpm_2;
  uint32_t controlValue;
} FC_FANS;
extern FC_FANS FANS;

