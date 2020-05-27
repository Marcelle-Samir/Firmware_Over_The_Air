/*
 * DMA.c
 *
 *  Created on: Apr 15, 2020
 *      Author: MOSTAFA
 */


#include "DMA.h"
#include "DMA_Cfg.h"

#define ENABLE_DMA			1
#define CHANNELS_MAX_NUMBER	7
#define COUNTER_MAX_NUMBER  65535





Notify_t NotificationArray[7];

typedef struct
{
	uint_32t CCR;
	uint_32t CNDTR;
	uint_32t CPAR;
	uint_32t CMAR;
	uint_32t Reserved;
}DMA_Channel;
#define DMA_2_NVIC 11
typedef struct
{
	uint_32t 			ISR;
	uint_32t 			IFCR;
	DMA_Channel Channel[7];
}DMA_t;

#define DMA ((volatile DMA_t*)0x40020000)

extern DMA_Config DMA_Configure[MAX_NUMBER_OF_CHANNELS];

uint_8t D_DMA_Init(void)
{
	uint_8t Counter;
	uint_8t ErrorStatus=OK;

	for(Counter=0;Counter<MAX_NUMBER_OF_CHANNELS;Counter++)
	{

		if(( DMA_Configure[Counter].ChannelNumber ) < 7 )
		{

			DMA->Channel[DMA_Configure[Counter].ChannelNumber].CCR=
					DMA_Configure[Counter].Mem2Mem |
					DMA_Configure[Counter].PL      |
					DMA_Configure[Counter].MSIZE   |
					DMA_Configure[Counter].PSIZE   |
					DMA_Configure[Counter].MINC    |
					DMA_Configure[Counter].PINC    |
					DMA_Configure[Counter].CIRC    |
					DMA_Configure[Counter].DIR     |
					DMA_Configure[Counter].TEIE    |
					DMA_Configure[Counter].HTIE    |
					DMA_Configure[Counter].TCIE    ;
					ErrorStatus|=DNVIC_ClearPendingIRQ(DMA_Configure[Counter].ChannelNumber+DMA_2_NVIC);
					ErrorStatus|=DNVIC_EnableIRQ(DMA_Configure[Counter].ChannelNumber+DMA_2_NVIC);
		}
		else
		{
			ErrorStatus|=NOK;
		}
	}


	return ErrorStatus;
}


uint_8t D_DMA_Start(uint_32t MemoryAddress,uint_32t PeripheralAddress,uint_32t Counter,uint_8t ChannelNumber)
{
	uint_8t ErrorStatus=OK;

	if((uint_32t*) MemoryAddress || (uint_32t*) PeripheralAddress || ChannelNumber<CHANNELS_MAX_NUMBER || Counter<COUNTER_MAX_NUMBER)
	{
		DMA->Channel[ChannelNumber].CNDTR=Counter;
		DMA->Channel[ChannelNumber].CMAR=MemoryAddress;
		DMA->Channel[ChannelNumber].CPAR=PeripheralAddress;

		DMA->Channel[ChannelNumber].CCR|=ENABLE_DMA;
	}
	else
	{
		ErrorStatus=NOK;
	}

	return ErrorStatus;

}



uint_8t D_DMA_SetNotifyCbf(Notify_t *Notification, uint_8t Channel_Number)
{
	uint_8t ErrorStatus=OK;

	if(Notification || Channel_Number<7)
	{
		NotificationArray[Channel_Number].TC=Notification->TC;
		NotificationArray[Channel_Number].HTC=Notification->HTC;
		NotificationArray[Channel_Number].TE=Notification->TE;
	}
	else
	{
		ErrorStatus=NOK;
	}

	return ErrorStatus;

}

void DMA1_Channel1_IRQHandler(void)
{
	if( (DMA->ISR & DMA1_GET_INT_TC1) ==DMA1_GET_INT_TC1)
	{
		DMA->IFCR |= (DMA1_GET_INT_TC1);
		DMA->Channel[CHANNEL_ONE].CCR&=~ENABLE_DMA;
		if(NotificationArray[CHANNEL_ONE].TC)
		{
			(NotificationArray[CHANNEL_ONE].TC)();
		}
	}
}

void DMA1_Channel2_IRQHandler(void)
{
	if( (DMA->ISR & DMA1_GET_INT_TC2) ==DMA1_GET_INT_TC2)
	{
		DMA->IFCR |= (DMA1_GET_INT_TC2);
		DMA->Channel[CHANNEL_TWO].CCR&=~ENABLE_DMA;
		if(NotificationArray[CHANNEL_TWO].TC)
		{
			NotificationArray[CHANNEL_TWO].TC();
		}
	}
}

void DMA1_Channel3_IRQHandler(void)
{
	if( (DMA->ISR & DMA1_GET_INT_TC3) ==DMA1_GET_INT_TC3)
	{
		DMA->IFCR |= (DMA1_GET_INT_TC3);
		DMA->Channel[CHANNEL_THREE].CCR&=~ENABLE_DMA;
		if(NotificationArray[CHANNEL_THREE].TC)
		{
			NotificationArray[CHANNEL_THREE].TC();
		}
	}
}

void DMA1_Channel4_IRQHandler(void)
{
	if( (DMA->ISR & DMA1_GET_INT_TC4) ==DMA1_GET_INT_TC4)
	{
		DMA->IFCR |= (DMA1_GET_INT_TC4);
		DMA->Channel[CHANNEL_FOUR].CCR&=~ENABLE_DMA;
		if(NotificationArray[CHANNEL_FOUR].TC)
		{
			NotificationArray[CHANNEL_FOUR].TC();
		}
	}
}

void DMA1_Channel5_IRQHandler(void)
{
	if( (DMA->ISR & DMA1_GET_INT_TC5) ==DMA1_GET_INT_TC5)
	{
		DMA->IFCR |= (DMA1_GET_INT_TC5);
		DMA->Channel[CHANNEL_FIVE].CCR&=~ENABLE_DMA;
		if(NotificationArray[CHANNEL_FIVE].TC)
		{
			NotificationArray[CHANNEL_FIVE].TC();
		}
	}
}

void DMA1_Channel6_IRQHandler(void)
{
	if( (DMA->ISR & DMA1_GET_INT_TC6) ==DMA1_GET_INT_TC6)
	{
		DMA->IFCR |= (DMA1_GET_INT_TC6);
		DMA->Channel[CHANNEL_SIX].CCR&=~ENABLE_DMA;
		if(NotificationArray[CHANNEL_SIX].TC)
		{
			NotificationArray[CHANNEL_SIX].TC();
		}
	}
}

void DMA1_Channel7_IRQHandler(void)
{
	if( (DMA->ISR & DMA1_GET_INT_TC7) ==DMA1_GET_INT_TC7)
	{
		DMA->IFCR |= (DMA1_GET_INT_TC7);
		DMA->Channel[CHANNEL_SEVEN].CCR&=~ENABLE_DMA;
		if(NotificationArray[CHANNEL_SEVEN].TC)
		{
			NotificationArray[CHANNEL_SEVEN].TC();
		}
	}
}





