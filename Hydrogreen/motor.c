/*
 * motor.c
 *
 *  Created on: May 2, 2021
 *      Author: User
 */

#include "tim.h"
#include "rs485.h"

void motor_init(void)
{
  HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1,(uint32_t*) RS485_RX_VERIFIED_DATA.motorPWM, 1);
}
