/*
 * UART.h
 *
 *  Created on: Mar 25, 2020
 *      Author: MOSTAFA, honda, marcelle, marina & donia
 */
#ifndef UART_H_
#define UART_H_

typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed short int int_32t;

#define OK 		0
#define NOT_OK 	1
#define BUSY	2

#define USART_TCEIE_ENABLE				0x00000040
#define USART_TXEIE_ENABLE				0x00000080
#define USART_RXNEIE_ENABLE				0x00000020

typedef void(*TxCbf_t)(void);
typedef void(*RxCbf_t)(void);
typedef void(*LBDCbf_t)(void);

uint_8t UART_Init(uint_32t BaudRateMantissa, uint_32t BaudRateFraction,uint_32t ParityBits,uint_32t DataSize,uint_32t StopBits);
uint_8t UART_Send(uint_8t *Buffer, uint_16t Length);
uint_8t UART_SendDMA(uint_8t *Buffer, uint_16t Length);
uint_8t UART_Receive(uint_8t *Buffer, uint_16t Length);
uint_8t UART_Config(uint_32t BaudRateMantissa, uint_32t BaudRateFraction,uint_32t ParityBits,uint_32t DataSize,uint_32t StopBits);
uint_8t UART_SetTxCbf(TxCbf_t TxCbf);
uint_8t UART_SetRxCbf(RxCbf_t RxCbf);
uint_8t UART_SetLBDCbf(LBDCbf_t LBDCbf);
void DMA_ChannelFour_Finish(void);
void DMA_ChannelFive_Finish(void);
void UART_SendBreak(void);

#endif
