/*
 * Sched_config.h
 *
 *  Created on: Mar 10, 2020
 *      Author: MOSTAFA
 */

#ifndef SCHED_CONFIG_H_
#define SCHED_CONFIG_H_
#define SCHED_TICK_mSEC 1
#define MAX_TASKS 1
typedef struct
{
	task_t * AppTask;
	uint_32t FirstDelay;
}TaskBaseInfo_t;


#endif /* SCHED_CONFIG_H_ */
