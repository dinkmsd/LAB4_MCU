/*
 * list_task.c
 *
 *  Created on: 30 Nov 2022
 *      Author: xanlo
 */

#include "main.h"
#include "list_task.h"
#include <stdio.h>
#include "timer.h"

extern UART_HandleTypeDef huart2;
char str[50];

void task_1 (void) {
	HAL_UART_Transmit(&huart2, str, sprintf(str, "Task 1: %d \r\n",timestamp), 1000);
	HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
}

void task_2 (void) {
	HAL_UART_Transmit(&huart2, str, sprintf(str, "Task 2: %d \r\n",timestamp), 1000);
	HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
}

void task_3 (void){
	HAL_UART_Transmit(&huart2, str, sprintf(str, "Task 3: %d \r\n",timestamp), 1000);
	HAL_GPIO_TogglePin(LED_3_GPIO_Port, LED_3_Pin);
}

void task_4 (void) {
	HAL_UART_Transmit(&huart2, str, sprintf(str, "Task 4: %d \r\n",timestamp), 1000);
	HAL_GPIO_TogglePin(LED_4_GPIO_Port, LED_4_Pin);
}

void task_5 (void) {
	HAL_UART_Transmit(&huart2, str, sprintf(str, "Task 5: %d \r\n",timestamp), 1000);
	HAL_GPIO_TogglePin(LED_5_GPIO_Port, LED_5_Pin);
}
