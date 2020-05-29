/*
 * Sched_config.c
 *
 *  Created on: Mar 10, 2020
 *      Author: MOSTAFA
 */

#include "Sched.h"
#include "Sched_config.h"
extern task_t task1;


const TaskBaseInfo_t SysTask_info[MAX_TASKS]={
		{.AppTask=&task1,.FirstDelay=0}
};
