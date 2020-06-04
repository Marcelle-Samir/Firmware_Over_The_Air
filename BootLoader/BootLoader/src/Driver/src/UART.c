#include "DNVIC.h"
#include "UART.h"
#include "UART_Private.h"

#define STATE_IDLE	0
#define STATE_BUSY	1

#define USART_DEFAULT_CONFIG_MASK		0x0000200C




#define USART_TXE_FLAG					0x00000080
#define USART_RXNE_FLAG					0x00000020
#define USART_LBD_FLAG					0x00000100

#define NULL 							(void*)0

#define DATA_SIZE_CLEAR_MASK			0xFFFFEFFF
#define PARITY_BIT_CLEAR_MASK			0xFFFF3FFF
#define STOP_BITS_CLEAR_MASK			0xFFFFCFFF
#define BREAK_ENABLE                    0x00000001UL


typedef struct
{
	uint_8t *Data;
	uint_32t Position;
	uint_32t Size;
	uint_8t BufferState;
}DataBuffer_t;

static DataBuffer_t TxBuffer;
static DataBuffer_t RxBuffer;

static TxCbf_t TxNotify;
static RxCbf_t RxNotify;
static LBDCbf_t LBDNotify;

extern uint_8t UART_mode;
uint_8t UART_Init(uint_32t BaudRateMantissa, uint_32t BaudRateFraction,uint_32t ParityBits,uint_32t DataSize,uint_32t StopBits)
{
	uint_8t Local_Error=OK;
	UART->BRR= BaudRateFraction | (BaudRateMantissa<<4);
	UART->CR1 |= USART_DEFAULT_CONFIG_MASK | DataSize| ParityBits;
	UART->CR2 |= StopBits;
	Local_Error|=DNVIC_ClearPendingIRQ(USART1);
	Local_Error|=DNVIC_EnableIRQ(USART1);
	return Local_Error;
}

uint_8t UART_Send(uint_8t *Buffer, uint_16t Length)
{
	uint_8t Local_Error=OK;
	if(Buffer && Length>0)
	{
		if(TxBuffer.BufferState==STATE_IDLE)
		{
			TxBuffer.Data=Buffer;
			TxBuffer.Size=Length;
			TxBuffer.Position=0;
			TxBuffer.BufferState=STATE_BUSY;
			UART->DR = TxBuffer.Data[TxBuffer.Position];
			TxBuffer.Position++;
		}
		else
		{
			Local_Error=BUSY;
		}
	}
	else
	{
		Local_Error=NOT_OK;
	}
	return Local_Error;
}


uint_8t UART_Receive(uint_8t *Buffer, uint_16t Length)
{
	uint_8t Local_Error=OK;
	if(Buffer && Length>0)
	{
		if(RxBuffer.BufferState==STATE_IDLE)
		{
			RxBuffer.Size=Length;
			RxBuffer.Position=0;
			RxBuffer.Data=Buffer;
			RxBuffer.BufferState=STATE_BUSY;
		}
		else
		{
			Local_Error=BUSY;
		}
	}
	else
	{
		Local_Error= NOT_OK;
	}
	return Local_Error;
}

uint_8t UART_Config(uint_32t BaudRateMantissa, uint_32t BaudRateFraction,uint_32t ParityBits,uint_32t DataSize,uint_32t StopBits)
{
	uint_8t Local_Error=OK;

	UART->CR1 &= DATA_SIZE_CLEAR_MASK;
	UART->CR1 |= DataSize;
	UART->CR1 &= PARITY_BIT_CLEAR_MASK;
	UART->CR1 |= ParityBits;

	UART->CR2 &= STOP_BITS_CLEAR_MASK;
	UART->CR2 |= StopBits;

	UART->BRR= BaudRateFraction | (BaudRateMantissa<<4);
	return Local_Error;
}

uint_8t UART_SetTxCbf(TxCbf_t TxCbf)
{
	uint_8t Local_Error=OK;
	TxNotify=TxCbf;
	return Local_Error;
}
uint_8t UART_SetRxCbf(RxCbf_t RxCbf)
{
	uint_8t Local_Error=OK;
	RxNotify=RxCbf;
	return Local_Error;
}

uint_8t UART_SetLBDCbf(LBDCbf_t LBDCbf)
{
	uint_8t Local_Error=OK;
	LBDNotify=LBDCbf;
	return Local_Error;
}

void USART1_IRQHandler(void)
{
	if (!UART_mode)
	{
		if(UART->SR & USART_TC_FLAG)
		{
			UART->SR&=~USART_TC_FLAG;
			if(TxBuffer.BufferState==STATE_BUSY)
			{
				if(TxBuffer.Position != TxBuffer.Size)
				{
					UART->DR = TxBuffer.Data[TxBuffer.Position];
					TxBuffer.Position++;
				}
				else
				{
					TxBuffer.Position=0;
					TxBuffer.Size=0;
					TxBuffer.Data=NULL;
					TxBuffer.BufferState=STATE_IDLE;
					/*				UART->CR1 &= ~USART_TXEIE_ENABLE;*/
					if(TxNotify)
					{
						TxNotify();
					}
					else
					{
						/*MISRA*/
					}
				}
			}
			else
			{
				/*MISRA*/
			}
		}
		else
		{
			/*MISRA*/
		}

		if(UART->SR & USART_RXNE_FLAG)
		{
			if(RxBuffer.BufferState==STATE_BUSY)
			{
				if(RxBuffer.Position != RxBuffer.Size)
				{
					UART->SR &= ~USART_RXNE_FLAG;
					RxBuffer.Data[RxBuffer.Position]=UART->DR;
					RxBuffer.Position++;
				}
				else
				{
					RxBuffer.Data=NULL;
					RxBuffer.Position=0;
					RxBuffer.Size=0;
					RxBuffer.BufferState=STATE_IDLE;
					UART->CR1 &= ~USART_RXNEIE_ENABLE;
					if(RxNotify)
					{
						RxNotify();
					}
					else
					{
						/*MISRA*/
					}
				}
			}
			else
			{
				/*MISRA*/
			}

		}
		else
		{
			/*MISRA*/
		}
	}
	else
	{
		/*MISRA*/
	}

	if (UART->SR & USART_LBD_FLAG)
	{
		UART->SR &=~ USART_LBD_FLAG;
		if (LBDNotify)
		{
			LBDNotify();
		}
		else
		{
			/*MISRA*/
		}
	}
}

void DMA_ChannelFour_Finish(void)
{
	while(!(UART->SR & USART_TC_FLAG));

	UART->SR &= ~(USART_TC_FLAG);

	if(TxNotify)
	{
		TxNotify();
	}
	else
	{
		/*MISRA*/
	}
}

void DMA_ChannelFive_Finish(void)
{
	if(RxNotify)
	{
		RxNotify();
	}
	else
	{
		/*MISRA*/
	}
}


void UART_SendBreak(void)
{
	UART->CR1|=BREAK_ENABLE;
}
