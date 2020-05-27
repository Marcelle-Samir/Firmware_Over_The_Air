/*
 * BootLoader.c
 *
 *  Created on: May 21, 2020
 *      Author: Ahmed Qandeel
 */

#include "DRCC.h"
#include "DGPIO.h"
#include "DMA.h"
#include "DNVIC.h"
#include "HUART.h"
#include "Bootloader_types.h"
#include "FLITF.h"

#define WORD_SIZE                       4
#define SCB_AIRCR                      *((volatile uint_32t*) 0XE000ED0C)
#define SFT_RST                        0x00000004
#define PASSWORD_MASK                  0X05FA0000

static void Com_Handler               (void);
static void Receiving_New_App_Req     (void);
static void Recieve_Data              (void);
static void Received_Finished         (void);
static void Reset_Sys                 (void);
/*
 * done - hannazelo fe makan sabet fel memory
 * */
static uint_32t * Marker = (uint_32t *) (0x08001FF8)                         ;

/*
 * done - Entry Point fe makan sabet
 * */
typedef void(*EntryPoint_t)(void)               ;
EntryPoint_t * APP_EntryPoint = (EntryPoint_t *) (0x08001FFC)                ;



static uint_8t  Buffer[FLASH_WRITE_SECTOR_SIZE] ;
static uint_8t FlashNewAppKey                  ;
static uint_32t APP_Size                        ;
static uint_32t APP_Addr                        ;
static uint_32t COM_Handler_State               ;
static uint_32t Entry_Point_Addr                ;

static RespondFrame_t Respond                   ;

void main (void)
{

	switch(*Marker)
	{
	case APP_FOUND :
		/*Initialize stack pointer*/
		asm ("ldr r1, =_estack\n"
				"mov sp, r1");
		(*APP_EntryPoint)();
		break ;
	case NEW_APP_REQ :
		/*CBF*/
		DRCC_SetPriephralStatus (GPIO_A_ENABLE,ON)  ;
		DRCC_SetPriephralStatus (GPIO_C_ENABLE,ON)  ;
		DRCC_SetPriephralStatus (USART_1_ENABLE,ON) ;
		DRCC_SetPriephralStatus(DMA_1_ENABLE,ON)    ;
		HUART_Init()                               ;
		/*erase old application*/
		while(1)
		{
			Com_Handler();
		}
		break ;
	case NO_APP :
		DRCC_SetPriephralStatus (GPIO_A_ENABLE,ON)  ;
		DRCC_SetPriephralStatus (GPIO_C_ENABLE,ON)  ;
		DRCC_SetPriephralStatus (USART_1_ENABLE,ON) ;
		DRCC_SetPriephralStatus(DMA_1_ENABLE,ON)    ;
		HUART_Init()                               ;
		while(1)
		{
			Com_Handler();
		}
		break ;
	}
}
void Com_Handler(void)
{
	switch(COM_Handler_State)
	{
	case WAITING_NEW_APP_CMD :
		HUART_Receive(Buffer,FLASH_NEW_APP_SIZE);
		HUART_SetRxCbf(Receiving_New_App_Req);
		COM_Handler_State=WAITING_STATE;
		break ;
	case NEW_APP_CMD_RECEIVED :
		HUART_Receive(Buffer,FLASH_WRITE_SECTOR_SIZE);
		HUART_SetRxCbf(Recieve_Data);
		COM_Handler_State=WAITING_STATE;
		break ;
	case FLASH_WRITE_FINISHED :
		HUART_Receive(Buffer,END_FLASH_SIZE);
		HUART_SetRxCbf(Received_Finished);
		COM_Handler_State=WAITING_STATE;
		break ;
	case WAITING_STATE :
		break ;
	}
}
void Receiving_New_App_Req(void)
{
	FlashNewAppCmd_t * NewApp_ptr = (FlashNewAppCmd_t *) Buffer ;
	if(NewApp_ptr->Header.Start_Of_Frame == START_OF_FRAME_KEY)
	{
		if(NewApp_ptr->Header.command_Num == COMMAND_FLASH_NEW_APP)
		{
			FlashNewAppKey   = NewApp_ptr->key ;
			Entry_Point_Addr = NewApp_ptr->EntryPoint ;
			APP_Addr         = NewApp_ptr->Address ;
			APP_Size         = NewApp_ptr->Size ;
			Respond.ACK_Key  = RECEIVED_OK ;
		}
		else
		{
			Respond.ACK_Key = RECEIVED_NOK ;
		}
	}
	else
	{
		Respond.ACK_Key = RECEIVED_NOK ;
	}
	Respond.Header.Start_Of_Frame = START_OF_FRAME_KEY ;
	Respond.Header.command_Num    = COMMAND_RESPOND_FRAME ;
	HUART_Send((uint_8t*)&Respond,RESPOND_FRAME_SIZE);
	COM_Handler_State             = NEW_APP_CMD_RECEIVED ;
}
void Recieve_Data         (void)
{
	uint_16t iterator  ;
	/*volatile*/ uint_8t  Error=0     ;
	FlashWriteSector_t * ReceivedData_ptr = (FlashWriteSector_t *) Buffer ;
	if(ReceivedData_ptr->Header.Start_Of_Frame == START_OF_FRAME_KEY)
	{
		if(ReceivedData_ptr->Header.command_Num == COMMAND_FLASH_WRITE_SECTOR)
		{
			if(FlashNewAppKey == FLASH_NEW_APP_KEY)
			{
				Flash_Unlock();
				/*Flash_ErasePage(ReceivedData_ptr->Address);*/
				Flash_ProgramWrite((void*)ReceivedData_ptr->Address,(void*)ReceivedData_ptr->Data,ReceivedData_ptr->Size );
				for(iterator = 0; iterator<ReceivedData_ptr->Size ; iterator ++ )
				{
					if(ReceivedData_ptr->Data[iterator] != *((uint_8t *)(ReceivedData_ptr->Address)+iterator))
					{
						Error = 1 ;
					}
				}
				if(!Error)
				{
					Respond.ACK_Key = RECEIVED_OK;
					APP_Size       -= ReceivedData_ptr->Size ;
				}
				else
				{
					Respond.ACK_Key = RECEIVED_NOK ;
				}
			}
			else
			{
				Respond.ACK_Key     = RECEIVED_NOK ;
			}
		}
		else
		{
			Respond.ACK_Key         = RECEIVED_NOK ;
		}
	}
	else
	{
		Respond.ACK_Key   = RECEIVED_NOK ;
	}
	if(!APP_Size)
	{
		COM_Handler_State = FLASH_WRITE_FINISHED ;
	}
	else
	{
		COM_Handler_State = NEW_APP_CMD_RECEIVED;
	}
	HUART_Send((uint_8t*)&Respond,RESPOND_FRAME_SIZE);
}
void Received_Finished         (void)
{
	uint_32t temp ;
	EndFlashing_t * ReceivedDataFinished_ptr = (EndFlashing_t *) Buffer ;
	if(ReceivedDataFinished_ptr->Header.Start_Of_Frame == START_OF_FRAME_KEY)
	{
		if(ReceivedDataFinished_ptr->Header.command_Num == COMMAND_END_FLASH)
		{
			if(ReceivedDataFinished_ptr->End_Flashing_Key == END_FLASH_KEY)
			{
				Respond.ACK_Key = RECEIVED_OK      ;
				temp            = APP_FOUND        ;
				Flash_ProgramWrite((void *)Marker,(void *)&temp,WORD_SIZE);
				temp            = Entry_Point_Addr ;
				Flash_ProgramWrite((void *)APP_EntryPoint,(void *)&temp,WORD_SIZE);
			}
			else
			{
				Respond.ACK_Key = RECEIVED_NOK ;
			}
		}
		else
		{
			Respond.ACK_Key     = RECEIVED_NOK ;
		}
	}
	else
	{
		Respond.ACK_Key         = RECEIVED_NOK ;
	}
	HUART_Send((uint_8t*)&Respond,RESPOND_FRAME_SIZE);
	HUART_SetTxCbf(Reset_Sys);
}

static void Reset_Sys (void)
{
	SCB_AIRCR |= SFT_RST | PASSWORD_MASK ;
	while (1);

}
