/*
 * timer.c
 *
 *  Created on: Nov 17, 2022
 *      Author: xanlo
 */


#include "main.h"
#include "scheduler.h"
int timestamp = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2){
		SCH_Update();
		timestamp++;
	}
}
