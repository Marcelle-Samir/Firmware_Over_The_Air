/*
 * Sched.h
 *
 *  Created on: Mar 10, 2020
 *      Author: MOSTAFA
 */

#ifndef SCHED_H_
#define SCHED_H_

typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef unsigned long long uint_64t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

#define OK       0
#define NOT_OK   1

typedef void (* Runnable_t)(void);
typedef struct {
	Runnable_t Runnable;
	uint_32t periodicity;
}task_t;

uint_8t Sched_Init(void);
uint_8t Sched_Start(void);
void Sched_Suspend(void);



#endif /* SCHED_H_ */
