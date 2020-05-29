/*
 * Sched.c
 *
 *  Created on: Mar 10, 2020
 *      Author: MOSTAFA
 */

#include "DRCC.h"
#include "DSYSTICK.h"
#include "Sched.h"
#include "Sched_config.h"
#define TASK_READY 1
#define TASK_SUSPEND 2
typedef struct
{
	TaskBaseInfo_t * TaskInfo;
	uint_32t state;
	uint_32t PeriodTicks;
	uint_32t TicksToExec;
}systask_t;
uint_32t OSFlag;
/*uint_32t TickFreq;*/
systask_t SysTask [MAX_TASKS];
uint_8t idx;
extern  TaskBaseInfo_t SysTask_info [MAX_TASKS];
static void Sched_SetOSFlag (void)
{
	OSFlag++;
}
static void Sched(void)
{
	for (idx=0;idx<MAX_TASKS;idx++)
	{
		if (SysTask[idx].TicksToExec==0 && SysTask[idx].state==TASK_READY)
		{
			SysTask[idx].TaskInfo->AppTask->Runnable();
			SysTask[idx].TicksToExec=SysTask[idx].PeriodTicks;
		}
		SysTask[idx].TicksToExec--;
	}
}

uint_8t Sched_Init(void)
{
	uint_8t i;
	uint_8t localError;
	/*uint_32t STKPre;*/
	uint_32t BusFreq;
	/*get AHB bus*/
	localError=RCC_GetBusClock(AHB_BUS,&BusFreq);
	if (!localError)
	{
		/*calculate tick msec*/
		/*localError=SYSTICK_GetPrescale(&STKPre);*/
		if (!localError)
		{
		/*	TickFreq=BusFreq/STKPre;
			TickFreq/=1000;*/
		}
		else
		{
			localError=NOT_OK;
		}
	}
	else
	{
		localError=NOT_OK;
	}
	SYSTICK_Init();
	/*set call back for the systick*/
	SYSTICK_SetCallback(&Sched_SetOSFlag);
	/*Setting time for systick in microseconds,
	 *Converting time from milli to micro
	 */
	SYSTICK_SetTime(SCHED_TICK_mSEC*1000,BusFreq);
	for (i=0;i<MAX_TASKS;i++)
	{
		SysTask[i].TaskInfo=&SysTask_info[i];
		SysTask[i].state=TASK_READY;
		SysTask[i].PeriodTicks=(SysTask[i].TaskInfo->AppTask->periodicity)/SCHED_TICK_mSEC;
		SysTask[i].TicksToExec=(SysTask[i].TaskInfo->FirstDelay)/SCHED_TICK_mSEC;
	}
	return localError;
}
uint_8t Sched_Start(void)
{
	SYSTICK_Start();
	while (1)
	{
		if (OSFlag)
		{
			OSFlag--;
			Sched();
		}
	}
}
void Sched_Suspend(void)
{
	SysTask[idx].state=TASK_SUSPEND;
}

