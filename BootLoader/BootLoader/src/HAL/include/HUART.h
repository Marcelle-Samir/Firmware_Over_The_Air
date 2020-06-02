/*
 * HUART.h
 *
 *  Created on: Mar 28, 2020
 *      Author: Mohanad
 */


#ifndef HUART_H_
#define HUART_H_

typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

#define OK 		0
#define NOT_OK 	1
#define BUSY	2

typedef void(*TxCbf_t)(void);
typedef void(*RxCbf_t)(void);
typedef void(*LBDCbf_t)(void);

uint_8t HUART_Init(void);
uint_8t HUART_Send(uint_8t *Buffer, uint_16t Length);
uint_8t HUART_Receive(uint_8t *Buffer, uint_16t Length);
uint_8t HUART_Config(uint_32t BaudRate,uint_32t ParityBits,uint_32t DataSize,uint_32t StopBits);
uint_8t HUART_SetTxCbf(TxCbf_t TxCbf);
uint_8t HUART_SetRxCbf(RxCbf_t RxCbf);
uint_8t HUART_SetLBDCbf(LBDCbf_t LBDCbf);
uint_8t HUART_SendBreak(void);




#endif /* HUART_H_ */
