/*
 * Transport.c
 *
 *  Created on: Jun 7, 2020
 *      Author: toshiba
 */
#include "STD_TYPES.h"
#include "HUART.h"
#include "../include/UART_TP.h"


#define TP_FRAME_SIZE			8
#define SINGLE_FRAME_DATA_SIZE	7
#define FIRST_FRAME_DATA_SIZE	6
#define CONSEC_FRAME_DATA_SIZE	7

#define PCI_INDEX				0
#define PADDING_VALUE			0xFF

#define SINGLE_FRAME_PCI_ID		  0x00
#define FIRST_FRAME_PCI_ID 		  0x10
#define CONSEC_FRAME_PCI_ID		  0x20
#define FLOW_CONTROL_FRAME_PCI_ID 0x30

static void UART_TP_TxHandler(void);
static void UART_TP_RxHandler(void);

static TxCbf_t TxNotify;
static RxCbf_t RxNotify;

static uint_8t Tx_counter;
static uint_8t Rx_counter;


static uint_8t Tx_Buffer [TP_FRAME_SIZE];
static uint_8t Rx_Buffer [TP_FRAME_SIZE];

static uint_8t * Tx_ptr;
static uint_8t * Rx_ptr;

static uint_16t  Tx_size;
static uint_16t  Rx_size;

uint_8t UART_TP_Send(uint_8t *Buffer, uint_16t Length)
{
	uint_8t LocalError = OK;
	uint_8t * PCI_ptr;
	uint_8t bytesIterator;
	HUART_SetTxCbf(UART_TP_TxHandler);
	if (Length<=SINGLE_FRAME_DATA_SIZE)/*Single Frame case*/
	{
		Tx_Buffer [PCI_INDEX] = Length;/*PCI Value*/
		for (bytesIterator = 1 ; bytesIterator <= Length ; bytesIterator ++) /*Append data bytes into the single */
		{
			Tx_Buffer [bytesIterator] = Buffer [bytesIterator -1];
		}
		for (bytesIterator = Length+1; bytesIterator <=SINGLE_FRAME_DATA_SIZE ;bytesIterator ++)
		{
			Tx_Buffer [bytesIterator] = PADDING_VALUE;
		}

		LocalError |= HUART_Send(Tx_Buffer,TP_FRAME_SIZE);
		Tx_counter=0;
	}
	else /*Data bytes will be divided into first frame and consecutive frames*/
	{
		Tx_ptr = Buffer;
		Tx_size = Length;
		Tx_Buffer[PCI_INDEX]=0x10;
		PCI_ptr =(uint_8t *)  & Length;
		Tx_Buffer[PCI_INDEX+1] = *PCI_ptr;
		Tx_Buffer[PCI_INDEX] |= *(PCI_ptr+1);
		for (bytesIterator = 0 ; bytesIterator <FIRST_FRAME_DATA_SIZE ; bytesIterator ++)
		{
			Tx_Buffer [2+bytesIterator] = Tx_ptr[bytesIterator];
		}
		LocalError|= HUART_Send(Tx_Buffer,TP_FRAME_SIZE);
		Tx_counter = (Length - FIRST_FRAME_DATA_SIZE ) / 7; /*calculating #of consecutive frames*/
		if ((Length - FIRST_FRAME_DATA_SIZE ) % 7)
		{
			Tx_counter++;
		}

	}
	return LocalError;
}
uint_8t UART_TP_Receive(uint_8t *Buffer, uint_16t Length)
{
	uint_8t LocalError = OK;
	Rx_counter =0;
	Rx_size=0;
	Rx_ptr=0;
	LocalError |= HUART_SetRxCbf(UART_TP_RxHandler);
	Rx_ptr = Buffer;
	if (Length <= 7) /*the data will be received in a single frame*/
	{
		LocalError |=HUART_Receive(Rx_Buffer,TP_FRAME_SIZE);
		Rx_counter = 0;
	}
	else /*Data will be sent into first and consecutive frames */
	{
		Rx_size = Length;
		Rx_counter = (Length - FIRST_FRAME_DATA_SIZE ) / 7; /*calculating #of consecutive frames*/
		if ((Length - FIRST_FRAME_DATA_SIZE ) % 7)
		{
			Rx_counter++;
		}
		LocalError |= HUART_Receive(Rx_Buffer,TP_FRAME_SIZE);
	}
	return LocalError;
}
uint_8t UART_TP_SetTxCbf(TxCbf_t TxCbf)
{
	uint_8t LocalError = OK;
	if(TxCbf)
	{
		TxNotify = TxCbf;
	}
	else
	{
		LocalError = NOK;
	}
	return LocalError ;
}
uint_8t UART_TP_SetRxCbf(RxCbf_t RxCbf)
{
	uint_8t LocalError = OK;
	if(RxCbf)
	{
		RxNotify= RxCbf;
	}
	else
	{
		LocalError = NOK;
	}
	return LocalError ;
}
static void UART_TP_TxHandler(void)
{
	static uint_16t TX_index=FIRST_FRAME_DATA_SIZE;
	static uint_8t SeqNum;
	uint_8t bytesIterator;
	if (!Tx_counter)
	{
		if (TxNotify)
		{
			TxNotify();
		}
		else
		{
			/*MISRA*/
		}
	}
	else
	{
		Tx_counter --;
		SeqNum ++;
		if (SeqNum == 0x10)
		{
			SeqNum = 0;
		}
		Tx_Buffer [PCI_INDEX]=0x20 | SeqNum;
		if (Tx_counter)
		{
			for (bytesIterator = 1 ; bytesIterator <=CONSEC_FRAME_DATA_SIZE ;bytesIterator ++)
			{
				Tx_Buffer[bytesIterator] = Tx_ptr [bytesIterator + TX_index -1];
			}
			HUART_Send(Tx_Buffer,TP_FRAME_SIZE);
			TX_index+=7;
		}
		else
		{
			for (bytesIterator = 1 ; bytesIterator <= Tx_size - TX_index; bytesIterator ++)
			{
				Tx_Buffer[bytesIterator] = Tx_ptr [bytesIterator + TX_index -1];
			}
			for (bytesIterator = 7 ; bytesIterator >Tx_size - TX_index; bytesIterator --)
			{
				Tx_Buffer[bytesIterator] = PADDING_VALUE;
			}
			HUART_Send(Tx_Buffer,TP_FRAME_SIZE);
			TX_index+=Tx_size - TX_index;

		}
	}
}
static void UART_TP_RxHandler(void)
{
	static uint_16t Rx_index;
	uint_8t bytesIterator;
	if (!Rx_counter)
	{
		if ((Rx_Buffer[PCI_INDEX] & 0xF0 )== SINGLE_FRAME_PCI_ID) /*Received a single frame */
		{
			for (bytesIterator = 0 ; bytesIterator <((Rx_Buffer[PCI_INDEX] & 0x0F));bytesIterator ++ )
			{
				Rx_ptr [bytesIterator] = Rx_Buffer [bytesIterator + 1];
			}
			Rx_index=0;
			if (RxNotify)
			{
				RxNotify();
			}
			else
			{
				/*MISRA*/
			}

		}
		else /*Last consecutive frame*/
		{
			for (bytesIterator = 0 ; bytesIterator < Rx_size - Rx_index;bytesIterator ++)
			{
				Rx_ptr [bytesIterator + Rx_index] = Rx_Buffer [bytesIterator+1];
			}
			Rx_index=0;
			if (RxNotify)
			{
				RxNotify();
			}
			else
			{
				/*MISRA*/
			}

		}
	}
	else /*First frame or consecutive frame*/
	{
		if ((Rx_Buffer[PCI_INDEX] & 0xF0) == FIRST_FRAME_PCI_ID )
		{
			for (bytesIterator = 0 ; bytesIterator < FIRST_FRAME_DATA_SIZE;bytesIterator ++)
			{
				Rx_ptr [bytesIterator + Rx_index] = Rx_Buffer [bytesIterator+2];
			}
			Rx_index+=FIRST_FRAME_DATA_SIZE;
			Rx_counter --;
			HUART_Receive(Rx_Buffer,TP_FRAME_SIZE);
		}
		else if ((Rx_Buffer[PCI_INDEX] & 0xF0) == CONSEC_FRAME_PCI_ID)
		{
			for (bytesIterator = 0 ; bytesIterator < CONSEC_FRAME_DATA_SIZE;bytesIterator ++)
			{
				Rx_ptr [bytesIterator + Rx_index] = Rx_Buffer [bytesIterator+1];
			}
			Rx_index+=CONSEC_FRAME_DATA_SIZE;
			Rx_counter --;
			HUART_Receive(Rx_Buffer,TP_FRAME_SIZE);
		}
		else if ((Rx_Buffer[PCI_INDEX] & 0xF0) == FLOW_CONTROL_FRAME_PCI_ID)
		{
			/*Not supported*/
		}
		else
		{
			/*MISRA*/
		}
	}
}
