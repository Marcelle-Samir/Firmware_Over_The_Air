/*
 * Transport.h
 *
 *  Created on: Jun 7, 2020
 *      Author: toshiba
 */

#ifndef TRANSPORT_INCLUDE_UART_TP_H_
#define TRANSPORT_INCLUDE_UART_TP_H_




typedef void(*TxCbf_t)(void);
typedef void(*RxCbf_t)(void);

uint_8t UART_TP_Send(uint_8t *Buffer, uint_16t Length);
uint_8t UART_TP_Receive(uint_8t *Buffer, uint_16t Length);
uint_8t UART_TP_SetTxCbf(TxCbf_t TxCbf);
uint_8t UART_TP_SetRxCbf(RxCbf_t RxCbf);



#endif /* TRANSPORT_INCLUDE_UART_TP_H_ */
