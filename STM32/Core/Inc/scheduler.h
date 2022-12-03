/*
 * schedule.h
 *
 *  Created on: Nov 17, 2022
 *      Author: xanlo
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"

#define SCH_MAX_TASKS 	40
#define NO_TASK_ID 		0

typedef struct {
	void ( * pTask )( void ) ;
 	uint32_t Delay ;
 	uint32_t Period ;
	uint8_t RunMe ;
	uint32_t TaskID ;
} sTask;

typedef struct {
 	sTask TASK_QUEUE[SCH_MAX_TASKS];
 	int numofTask;
} taskList;

taskList SCH_TASK_LIST;

void SCH_Init(void);
void SCH_Update(void);

unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY , unsigned int PERIOD );
void SCH_Dispatch_Tasks(void);
unsigned char SCH_Delete_Task(const int TASK_INDEX);

#endif /* INC_SCHEDULER_H_ */
