/*
 * HUART.c
 *
 *  Created on: Mar 28, 2020
 *      Author: Mohanad
 */
#include "DRCC.h"
#include "DGPIO.h"
#include "DMA.h"
#include "UART.h"
#include "UART_Private.h"
#include "HUART.h"
#include "HUART_config.h"

#define UART_DMA_TX_ENABLE		0x00000080
#define UART_DMA_RX_ENABLE		0x00000040
#define LIN_ENABLE    	      	0x00004000
#define LIN_BREAK_SIZE  	    0x00000020
#define LIN_INTERRUPT_ENABLE	0x00000040
Notify_t Notification_Send,Notification_Receive;
uint_8t UART_mode = INTERRUPT_MODE;
uint_32t Clk;
uint_8t HUART_Init(void)
{
	uint_8t Local_Error=OK;
	uint_32t BaudRate_Fraction;
	uint_32t BaudRate_Mantissa;
	/*configure GPIO Pins*/
	GPIO_t GPIO;
	GPIO.Mode=MODE_PIN10_IP_PUR|MODE_PIN9_AF_PP;
	GPIO.Speed=SPEED_PIN10_INPUT|SPEED_PIN9_2MHZ;
	GPIO.Port=PORT_A;
	GPIO.Pin=PIN_9|PIN_10;
	Local_Error=GPIO_Config(&GPIO);
	/*Set UART initial configuration*/
	Local_Error|=DRCC_GetBusClock(APB2_BUS,&Clk);
	BaudRate_Mantissa = ( (Clk) / (16*BAUD_RATE) );
	BaudRate_Fraction = (( ( (Clk) % (16*BAUD_RATE) ) *16 ) / (16*BAUD_RATE));
#if MODE==DMA_MODE
	UART_mode = DMA_MODE;
	D_DMA_Init();
	UART->CR3 |= UART_DMA_TX_ENABLE;
	UART->CR3 |= UART_DMA_RX_ENABLE;
#elif MODE==INTERRUPT_MODE
	UART->CR1 |= USART_RXNEIE_ENABLE | USART_TCEIE_ENABLE;
#endif

#if LIN_MODE==LIN_ON
	UART->CR2 |=LIN_ENABLE;
	UART->CR2 |=LIN_BREAK_SIZE;
	UART->CR2 |=LIN_INTERRUPT_ENABLE;
#endif
	Local_Error|=UART_Init(BaudRate_Mantissa,BaudRate_Fraction,PARITY_BIT,DATA_BITS,STOP_BITS);
	return Local_Error;

}
uint_8t HUART_Send(uint_8t *Buffer, uint_16t Length)
{
	uint_8t localError=OK;
	/*motawa7esh uart */
#if SEND_MODE==SEND_MODE_INTERRUPT
	localError= UART_Send(Buffer,Length);
#elif SEND_MODE==SEND_MODE_DMA
	Notification_Send.TC=DMA_ChannelFour_Finish;
	D_DMA_SetNotifyCbf(&Notification_Send,CHANNEL_FOUR);
	localError=D_DMA_Start((uint_32t)Buffer,(uint_32t)(&(UART->DR)),Length,CHANNEL_FOUR);
#else
#error("PROBLEM IN CONFIGURATION !!!")
#endif
	return localError;
}


uint_8t HUART_Receive(uint_8t *Buffer, uint_16t Length)
{
	uint_8t localError=OK;

#if RECEIVE_MODE==RECEIVE_MODE_INTERRUPT
	localError= UART_Receive(Buffer,Length);
#elif RECEIVE_MODE==RECEIVE_MODE_DMA
	Notification_Receive.TC=DMA_ChannelFive_Finish;
	D_DMA_SetNotifyCbf(&Notification_Receive,CHANNEL_FIVE);
	localError=D_DMA_Start((uint_32t)Buffer,(uint_32t)(&(UART->DR)),Length,CHANNEL_FIVE);
#else
#error("PROBLEM IN CONFIGURATION !!!")
#endif

	return localError;
}



uint_8t HUART_Config(uint_32t BaudRate,uint_32t ParityBits,uint_32t DataSize,uint_32t StopBits)
{
	uint_8t Local_Error=OK;
	uint_32t BaudRate_Fraction;
	uint_32t BaudRate_Mantissa;
	if((ParityBits==PARITY_DISABLED || ParityBits==PARITY_EVEN || ParityBits==PARITY_ODD) && (DataSize==DATA_8_BITS || DataSize==DATA_9_BITS) && (StopBits==ONE_STOP_BIT || StopBits==TWO_STOP_BIT))
	{
		BaudRate_Mantissa = ( (Clk) / (16*BaudRate) );
		BaudRate_Fraction = (( ( (Clk) % (16*BaudRate) ) *16 ) / (16*BaudRate));
		Local_Error=UART_Config(BaudRate_Mantissa,BaudRate_Fraction,ParityBits,DataSize,StopBits);
	}
	else
	{
		Local_Error=NOT_OK;
	}
	return Local_Error;
}
uint_8t HUART_SetTxCbf(TxCbf_t TxCbf)
{
	uint_8t LocalError=OK;
	if(TxCbf)
	{
		LocalError = UART_SetTxCbf(TxCbf);
	}
	else
	{
		LocalError=NOT_OK;
	}
	return LocalError;

}


uint_8t HUART_SetRxCbf(RxCbf_t RxCbf)
{
	uint_8t LocalError=OK;
	if(RxCbf)
	{
		LocalError = UART_SetRxCbf(RxCbf);
	}
	else
	{
		LocalError=NOT_OK;
	}
	return LocalError;
}

uint_8t HUART_SetLBDCbf(LBDCbf_t LBDCbf)
{
	uint_8t LocalError=OK;
	if(LBDCbf)
	{
		LocalError = UART_SetLBDCbf(LBDCbf);
	}
	else
	{
		LocalError=NOT_OK;
	}
	return LocalError;
}


uint_8t HUART_SendBreak(void)
{
	uint_8t Local_Error=OK;
	if(UART->CR2 & LIN_ENABLE)
		UART_SendBreak();
	else
		Local_Error=NOK;
	return Local_Error;
}



