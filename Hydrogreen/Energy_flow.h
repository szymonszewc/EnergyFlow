/*
 * Energy_flow.h
 *
 *  Created on: 2 maj 2021
 *      Author: User
 */

#pragma once

#include <stdint-gcc.h>

typedef struct
{
	uint32_t charging;
}   EnergyFlow;
extern EnergyFlow hydros;


void energyflow_init(void);
void energyflow_step(void);
void energyflow_mode0(void);
void energyflow_preapre_to_race(void);
void energyflow_race(void);
void energyflow_end_race(void);
void energyflow_emergency(void);

