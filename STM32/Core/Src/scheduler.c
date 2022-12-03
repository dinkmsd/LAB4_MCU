/*
 * schedule.c
 *
 *  Created on: Nov 17, 2022
 *      Author: xanlo
 */


#include "scheduler.h"
#include "main.h"
#include <stdio.h>
#include "timer.h"

uint8_t ERROR_CODE = 0;
extern UART_HandleTypeDef huart2;
char str[50];

int count = 0;

void SCH_Init(void){
	 unsigned char i ;
	 for (i = 0; i < SCH_MAX_TASKS; i++) {
		 // Delete all tasks
		 SCH_Delete_Task(i);
	 }
 }

void SCH_Update(void) {
	if (!SCH_TASK_LIST.TASK_QUEUE[0].pTask) {
			//ERROR: No task available
			ERROR_CODE = 3;
			return;
	}

	if (SCH_TASK_LIST.TASK_QUEUE[0].Delay == 0) {
		SCH_TASK_LIST.TASK_QUEUE[0].RunMe += 1;
	} else {
		SCH_TASK_LIST.TASK_QUEUE[0].Delay -= 1;
		count++;
	}



}

unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD) {
	if (SCH_TASK_LIST.numofTask >= SCH_MAX_TASKS) {
		//ERROR: Full queue
		ERROR_CODE = 1;
		return 1;
	}

	sTask temp;
	temp.pTask = pFunction;
	temp.Delay = DELAY;
	temp.Period =  PERIOD;
	temp.RunMe = 0;

	int index = 0;
	while (SCH_TASK_LIST.TASK_QUEUE[index].Delay <= temp.Delay && index < SCH_TASK_LIST.numofTask) {
		index++;
	}

	for (int i = SCH_TASK_LIST.numofTask; i > index; i--) {
		SCH_TASK_LIST.TASK_QUEUE[i] = SCH_TASK_LIST.TASK_QUEUE[i - 1];
	}

	SCH_TASK_LIST.TASK_QUEUE[index] = temp;
	SCH_TASK_LIST.numofTask++;
	return index;
}

void SCH_Report() {
	if (ERROR_CODE != 0) {
		switch(ERROR_CODE) {
		case 1:
			printf("ERROR: TOO MANY TASKS!\r\n");
			break;
		case 2:
			printf("ERROR: CANNOT DELETE TASK!\r\n");
			break;
		case 3:
			printf("ERROR: NO TASK AVAILABLE!\r\n");
		}
	}
}


unsigned char SCH_Delete_Task ( const int index ) {
	for (int i = index; i < SCH_TASK_LIST.numofTask - 1; i++) {
		SCH_TASK_LIST.TASK_QUEUE[i] = SCH_TASK_LIST.TASK_QUEUE[i + 1];
	}
	SCH_TASK_LIST.TASK_QUEUE[SCH_TASK_LIST.numofTask - 1].pTask = 0x0000 ;
	SCH_TASK_LIST.TASK_QUEUE[SCH_TASK_LIST.numofTask - 1].Delay = 0;
	SCH_TASK_LIST.TASK_QUEUE[SCH_TASK_LIST.numofTask - 1].Period = 0;
	SCH_TASK_LIST.TASK_QUEUE[SCH_TASK_LIST.numofTask - 1].RunMe = 0;
	SCH_TASK_LIST.numofTask--;
	return 1;
 }


void SCH_Dispatch_Tasks(void){

	if (!SCH_TASK_LIST.TASK_QUEUE[0].pTask) {
		// ERROR: No task available
		ERROR_CODE = 3;
		return ;
	}

	if (SCH_TASK_LIST.TASK_QUEUE[0].RunMe > 0) {

		for (int i = 1; i <  SCH_TASK_LIST.numofTask; i++){
			SCH_TASK_LIST.TASK_QUEUE[i].Delay -= count;
		}
		count = 0;

		while (SCH_TASK_LIST.TASK_QUEUE[0].RunMe > 0) {
			(*(SCH_TASK_LIST.TASK_QUEUE[0].pTask))();
			SCH_TASK_LIST.TASK_QUEUE[0].RunMe--;
			if (SCH_TASK_LIST.TASK_QUEUE[0].Period > 0) {
				SCH_Add_Task(SCH_TASK_LIST.TASK_QUEUE[0].pTask, SCH_TASK_LIST.TASK_QUEUE[0].Period, SCH_TASK_LIST.TASK_QUEUE[0].Period);
			}
			SCH_Delete_Task(0);
		}
	}
	SCH_Report();
}

