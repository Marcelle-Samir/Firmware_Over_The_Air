/*
 * BootLoader.c
 *
 *  Created on: May 21, 2020
 *      Author: Amr El-Nobe
 */
#include "STD_TYPES.h"
#include "DRCC.h"
#include "DGPIO.h"
#include "DMA.h"
#include "DNVIC.h"
#include "FLITF.h"
#include "HUART.h"
#include "../../Transport/include/UART_TP.h"
#include "UDS.h"
#include "Bootloader_Application.h"
#include "Bootloader_config.h"



#define DATA_INDEX					8

#define PAGE_SIZE                       0x400
#define MARKER_PAGE						0x08002800
#define CLEAR_WORD						0xFFFFFFFF
#define APP_START_PAGE					0x08002C00
#define APP_END_PAGE					0x0800FC00
#define BOOTLOADER_VECTOR_OFFSET		0x00000000

#define APP_FOUND                     0xAABBCCDD
#define NO_APP                        0xFFFFFFFF

#define ACCESS_DENIED                 0x01
#define ACCESS_ALLOWED                0x10

#define BOOTLOADER_INITIAL_STATE						0x01
#define BOOTLOADER_WAITING_STATE						0x02
#define BOOTLOADER_WRITE_DATA_BY_ID_STATE				0x03
#define BOOTLOADER_START_SESSION_STATE					0x04
#define BOOTLOADER_SECURITY_ACCESS_STATE				0x05
#define BOOTLOADER_ROUTINE_STATE						0x06
#define BOOTLOADER_REQUEST_DOWNLOAD_STATE				0x07
#define BOOTLOADER_TRANSFER_DATA_STATE					0x08
#define BOOTLOADER_REQUEST_TRANSFER_EXIT				0x09
#define BOOTLOADER_ECU_RESET_STATE						0x0A

static uint_8t  ReqBuffer[MAX_REQUEST_FRAME_SIZE] ;
static uint_8t  ResponseBuffer[MAX_RESPONSE_FRAME_SIZE] ;

static uint_8t ErrorCounter ;

static uint_8t BootLoaderState=BOOTLOADER_INITIAL_STATE;
static uint_8t BootLoaderPreviousState=BOOTLOADER_INITIAL_STATE;

static uint_8t SecurityAccess =  ACCESS_DENIED ;
static uint_8t CurrentSession =  DEFAULT_SESSION_ID;

static uint_32t BlockAddress;
static uint_32t AppSize ;
static uint_16t DataSize;
static uint_8t PreviousBlockNumber;

#define ROM_Marker  (uint_32t *)(0x08002BF8)
#define RAM_Marker  (uint_32t *)(0x20000000)



typedef void(*EntryPoint_t)(void);
#define APP_EntryPoint  (EntryPoint_t *)(0x08002BFC)


static void Clear_ROM_Marker (void);



static void Bootloader_State_Machine(void);
static void WaitState(void);
static void Read_Data_By_ID_Request_CBF(void);
static void SessionInitialize(void);
static void SetError(uint_8t ServiceID,uint_8t NRC);
static void ErrorHandler(void);
static void Session_Control_CBF(void);
static void StartDefaultSession(void);
static void StartProgrammingSession(void);
static void Security_Access_CBF(void);
static void GetKey(void);
static void KeyValidate(void);
static void RoutineState(void);
static void Routine_Control_CBF(void);
static void Erase_Application (void);
static void RequestDownloadState (void);
static void Request_Download_CBF (void);
static void TransferDataState (void);
static void Transfer_Data_CBF (void);
static void TransferDataDone (void);
static uint_8t ValidateDataBlock (void);
static void ValidateRoutineDone (void);
static void Request_Transfer_Exit_CBF (void);
static void TransferExitDone (void);
static void Write_Data_By_ID_CBF (void);
static void ECU_Reset_CBF (void);



void main (void)
{
	if ( RAM_MARKER_VALUE == *RAM_Marker )
	{
		*RAM_Marker=CLEAR_WORD;
		Clear_ROM_Marker();
		DNVIC_voidChangeVectorOffset(BOOTLOADER_VECTOR_OFFSET);
	}
	else
	{
		/*MISRA*/
	}

	switch(*ROM_Marker)
	{
	case APP_FOUND :
		/*Initialize stack pointer*/
		asm ("ldr r1, =_estack\n"
				"mov sp, r1");
		(*APP_EntryPoint)();
		break ;
	case NO_APP :
		*RAM_Marker=CLEAR_WORD;
		DRCC_SetPriephralStatus (GPIO_A_ENABLE,ON)  ;
		DRCC_SetPriephralStatus (GPIO_C_ENABLE,ON)  ;
		DRCC_SetPriephralStatus (USART_1_ENABLE,ON) ;
		DRCC_SetPriephralStatus(DMA_1_ENABLE,ON)    ;
		HUART_Init()   	                            ;
		while(1)
		{
			Bootloader_State_Machine();
		}
		break ;
	}

}


static void Bootloader_State_Machine(void)
{
	switch (BootLoaderState)
	{
	case BOOTLOADER_INITIAL_STATE:
		UDS_GetRequest(READ_DATA_BY_IDENTIFIER_SERVICE_ID,(void *)ReqBuffer,Read_Data_By_ID_Request_CBF);
		WaitState();

		break;
	case BOOTLOADER_START_SESSION_STATE:
		UDS_GetRequest(DIAGNOSTIC_SESSION_CONTROL_SERVICE_ID,(void *)ReqBuffer,Session_Control_CBF);
		WaitState();

		break;
	case BOOTLOADER_SECURITY_ACCESS_STATE:
		UDS_GetRequest(REQUEST_SEED_ID,(void *)ReqBuffer,Security_Access_CBF);
		WaitState();
		break;
	case BOOTLOADER_ROUTINE_STATE:
		UDS_GetRequest(ROUTINE_CONTROL_SERVICE_ID,(void *)ReqBuffer,Routine_Control_CBF);
		WaitState();
		break;
	case BOOTLOADER_REQUEST_DOWNLOAD_STATE:
		UDS_GetRequest(REQUEST_DOWNLOAD_SERVICE_ID,(void *)ReqBuffer,Request_Download_CBF);
		WaitState();
		break;
	case BOOTLOADER_TRANSFER_DATA_STATE:
		UDS_GetRequest(TRANSFER_DATA_SERVICE_ID,(void *)ReqBuffer,Transfer_Data_CBF);
		WaitState();
		break;
	case BOOTLOADER_REQUEST_TRANSFER_EXIT:
		UDS_GetRequest(REQUEST_TRANSFER_EXIT_SERVICE_ID,(void *)ReqBuffer,Request_Transfer_Exit_CBF);
		WaitState();
		break;
	case BOOTLOADER_WRITE_DATA_BY_ID_STATE:
		UDS_GetRequest(WRITE_DATA_BY_IDENTIFIER_SERVICE_ID,(void *)ReqBuffer,Write_Data_By_ID_CBF);
		WaitState();
		break;
	case BOOTLOADER_ECU_RESET_STATE:
		UDS_GetRequest(ECU_RESET_SERVICE_ID,(void *)ReqBuffer,ECU_Reset_CBF);
		WaitState();
		break;
	case BOOTLOADER_WAITING_STATE:
		break;
	}
}

static void WaitState(void)
{
	BootLoaderPreviousState = BootLoaderState;
	BootLoaderState = BOOTLOADER_WAITING_STATE;
}

static void Read_Data_By_ID_Request_CBF(void)
{

	ReadDataByIDReq_t *ReqFrame  = (ReadDataByIDReq_t *) ReqBuffer;
	ReadDataByIDResponse_t *ResponseFrame  = (ReadDataByIDResponse_t *) ResponseBuffer;
	if (ReqFrame->ServiceID == READ_DATA_BY_IDENTIFIER_SERVICE_ID)
	{
		switch (ReqFrame->DataID)
		{
		case MARKER_ID:
			ErrorCounter = 0;
			ResponseFrame->Data = *ROM_Marker;
			UDS_SendPositiveResponse(ReqFrame->ServiceID,(void *)ResponseBuffer,SessionInitialize);
			break;
		default:

			SetError (ReqFrame->ServiceID,SUB_FUNCTION_NOT_SUPPORTED_CODE);
			break;
		}
	}
	else
	{
		SetError (ReqFrame->ServiceID,REQUEST_SEQUENCE_ERROR_CODE);
	}

}

/*Switch to start session state*/
static void SessionInitialize(void)
{
	BootLoaderState = BOOTLOADER_START_SESSION_STATE;
}

/*General Error handling */

static void SetError(uint_8t ServiceID,uint_8t NRC)
{
	ErrorCounter ++;
	UDS_SendNegativeResponse(ServiceID,NRC,ErrorHandler);
}


static void ErrorHandler(void)
{
	if (ErrorCounter ==MAX_ERRORS_TIMES)
	{
		BootLoaderState = BOOTLOADER_INITIAL_STATE;
	}
	else
	{
		BootLoaderState = BootLoaderPreviousState;
	}
}

/*Start session control */
static void Session_Control_CBF(void)
{
	DiagSessCtrlReq_t *ReqFrame  = (DiagSessCtrlReq_t *) ReqBuffer;
	DiagSessCtrlResponse_t *ResponseFrame  = (DiagSessCtrlResponse_t *) ResponseBuffer;
	if (ReqFrame->ServiceID == DIAGNOSTIC_SESSION_CONTROL_SERVICE_ID)
	{
		CurrentSession = ReqFrame->SessionID;
		ResponseFrame->SessionID = ReqFrame->SessionID;
		switch (ReqFrame->SessionID)
		{
		case DEFAULT_SESSION_ID:
			ErrorCounter = 0;
			Flash_Lock();
			UDS_SendPositiveResponse(ReqFrame->ServiceID,(void *)ResponseBuffer,StartDefaultSession);
			break;
		case PROGRAMMING_SESSION_ID:
			ErrorCounter = 0;
			Flash_Unlock();
			ResponseFrame->ResponseTime = BOOTLOADER_RESPONSE_TIME;
			UDS_SendPositiveResponse(ReqFrame->ServiceID,(void *)ResponseBuffer,StartProgrammingSession);
			break;
		default:
			SetError (ReqFrame->ServiceID,SUB_FUNCTION_NOT_SUPPORTED_CODE);
			break;
		}
	}
	else
	{
		SetError (ReqFrame->ServiceID,REQUEST_SEQUENCE_ERROR_CODE);

	}


}

static void StartDefaultSession(void)
{
	BootLoaderState = BOOTLOADER_ECU_RESET_STATE;
}
static void StartProgrammingSession(void)
{

	BootLoaderState = BOOTLOADER_SECURITY_ACCESS_STATE;
}

static void Security_Access_CBF(void)
{
	RequestSeedReq_t *ReqFrame  = (RequestSeedReq_t *) ReqBuffer;
	RequestSeedResponse_t *ResponseFrame  = (RequestSeedResponse_t *) ResponseBuffer;
	if (ReqFrame->ServiceID == SECURITY_ACCESS_SERVICE_ID && ReqFrame->SubFuncID == REQUEST_SEED_ID)
	{
		ErrorCounter = 0;
		ResponseFrame->SubFuncID = ReqFrame->SubFuncID;
		ResponseFrame->Seed =  SEED_VALUE;
		UDS_SendPositiveResponse(ReqFrame->SubFuncID,(void *)ResponseBuffer,GetKey);
	}
	else
	{
		SetError (ReqFrame->ServiceID,REQUEST_SEQUENCE_ERROR_CODE);
	}

}
static void GetKey(void)
{
	UDS_GetRequest(TRANSFER_KEY_ID,(void *)ReqBuffer,KeyValidate);
}
static void KeyValidate(void)
{
	uint_16t KeyCalculated = KEY_GENERATE(SEED_VALUE);
	TransferKeyReq_t *ReqFrame  = (	TransferKeyReq_t *) ReqBuffer;
	TransferKeyResponse_t *ResponseFrame  = (TransferKeyResponse_t *) ResponseBuffer;
	if (ReqFrame->ServiceID == SECURITY_ACCESS_SERVICE_ID && ReqFrame->SubFuncID == TRANSFER_KEY_ID )
	{
		if (ReqFrame->Key == KeyCalculated)
		{
			SecurityAccess = ACCESS_ALLOWED;
			ErrorCounter = 0;
			ResponseFrame->SubFuncID = ReqFrame->SubFuncID;
			UDS_SendPositiveResponse(ReqFrame->SubFuncID,(void *)ResponseBuffer,RoutineState);

		}
		else
		{

			SetError (ReqFrame->ServiceID,SECURITY_ACCESS_DENIED_CODE);

		}
	}
	else
	{
		SetError (ReqFrame->ServiceID,REQUEST_SEQUENCE_ERROR_CODE);
	}
}
static void RoutineState(void)
{
	BootLoaderState = BOOTLOADER_ROUTINE_STATE;
}

static void Routine_Control_CBF(void)
{
	uint_8t RoutineStatus;
	RoutineControlReq_t *ReqFrame  = (RoutineControlReq_t *) ReqBuffer;
	RoutineControlResponse_t *ResponseFrame  = (RoutineControlResponse_t *) ResponseBuffer;
	if (ReqFrame->ServiceID == ROUTINE_CONTROL_SERVICE_ID)
	{
		ResponseFrame->ControlRoutineSignalID = ReqFrame->ControlRoutineSignalID;
		ResponseFrame->RoutineID = ReqFrame->RoutineID;
		switch (ReqFrame->RoutineID)
		{
		case ERASE_APPLICATION_ROUTINE_ID:

			switch (ReqFrame->ControlRoutineSignalID)
			{
			case START_ROUTINE_ID:
				if (SecurityAccess == ACCESS_ALLOWED && CurrentSession == PROGRAMMING_SESSION_ID )
				{
					ErrorCounter = 0;
					Erase_Application();
					UDS_SendPositiveResponse(ReqFrame->ServiceID,(void *)ResponseBuffer,RequestDownloadState);
				}
				else
				{
					Erase_Application();
					SetError (ReqFrame->ServiceID,SECURITY_ACCESS_DENIED_CODE);
				}
				break;
				/*case STOP_ROUTINE_ID:*/
				/*Not supported yet*/
				/*break;*/
				/*case QUERY_ROUTINE_RESULT_ID:*/
				/*Not supported yet*/
				/*break;*/
			}
			break;
			case VALIDATE_BLOCK_ROUTINE_ID:
				switch (ReqFrame->ControlRoutineSignalID)
				{
				case START_ROUTINE_ID:
					if (SecurityAccess == ACCESS_ALLOWED && CurrentSession == PROGRAMMING_SESSION_ID )
					{
						RoutineStatus = ValidateDataBlock();
						if (!RoutineStatus)/*Validation is done successfully*/
						{
							AppSize-=DataSize;    /**/
							PreviousBlockNumber ++;
							UDS_SendPositiveResponse(ReqFrame->ServiceID,(void *)ResponseBuffer,ValidateRoutineDone);
						}
						else
						{
							Erase_Application();
							SetError (ReqFrame->ServiceID,GENERAL_PROGRAMMING_FAILURE_CODE);
						}
					}
					else
					{
						SetError (ReqFrame->ServiceID,SECURITY_ACCESS_DENIED_CODE);
					}
					break;
					/*case STOP_ROUTINE_ID:*/
					/*Not supported yet*/
					/*break;*/
					/*case QUERY_ROUTINE_RESULT_ID:*/
					/*Not supported yet*/
					/*break;*/
				}
				break;
				default:
					SetError (ReqFrame->ServiceID,SUB_FUNCTION_NOT_SUPPORTED_CODE);
					break;
		}
	}
	else
	{
		SetError (ReqFrame->ServiceID,REQUEST_SEQUENCE_ERROR_CODE);
	}

}

static void Erase_Application    (void)
{
	uint_32t PagesIterator;
	/*Erase Application pages*/
	for  (PagesIterator = APP_START_PAGE ; PagesIterator <= APP_END_PAGE;PagesIterator+=PAGE_SIZE)
	{
		Flash_ErasePage(PagesIterator);
	}
}

static uint_8t ValidateDataBlock (void)
{
	uint_16t DataIterator;
	uint_8t Localerror=OK;
	for (DataIterator = 0; DataIterator < DataSize;DataIterator ++)
	{
		if (ReqBuffer [DATA_INDEX + DataIterator] != *((uint_8t *)(BlockAddress)+DataIterator))
		{
			Localerror = NOK;
		}
	}
	return Localerror;

}

static void RequestDownloadState (void)
{
	BootLoaderState = BOOTLOADER_REQUEST_DOWNLOAD_STATE;
}

static void ValidateRoutineDone (void)
{
	uint_16t i;
	for (i=0;i<MAX_REQUEST_FRAME_SIZE;i++)
	{
		ReqBuffer[i]=0;
	}
	if (!AppSize) /*The segment data is flashed successfully and its expected a request transfer exit*/
	{
		BootLoaderState = BOOTLOADER_REQUEST_TRANSFER_EXIT;
	}
	else /*a new transfer data block is expected*/
	{
		UDS_GetRequest(TRANSFER_DATA_SERVICE_ID,(void *)ReqBuffer,Transfer_Data_CBF);
	}
}

static void Request_Download_CBF (void)
{
	RequestDownloadReq_t *ReqFrame  = (RequestDownloadReq_t *) ReqBuffer;
	RequestDownloadResponse_t *ResponseFrame  = (RequestDownloadResponse_t *) ResponseBuffer;
	if (ReqFrame->ServiceID == REQUEST_DOWNLOAD_SERVICE_ID)
	{
		if (ReqFrame->MemAddLength == WORD_SIZE)
		{
			ErrorCounter = 0;
			AppSize = ReqFrame->AppSize;
			ResponseFrame->DataBlockSize =DATA_BLOCK_SIZE;
			UDS_SendPositiveResponse(ReqFrame->ServiceID,(void *)ResponseBuffer,TransferDataState);
		}
		else
		{
			SetError (ReqFrame->ServiceID,INVALID_FORMAT_CODE);
		}
	}
	else
	{
		SetError (ReqFrame->ServiceID,REQUEST_SEQUENCE_ERROR_CODE);

	}
}
static void TransferDataState (void)
{
	BootLoaderState = BOOTLOADER_TRANSFER_DATA_STATE;
}

static void Transfer_Data_CBF (void)
{
	uint_32t Check=0;
	uint_16t DataIterator;
	TransferDataReq_t *ReqFrame  = (TransferDataReq_t *) ReqBuffer;
	TransferDataResponse_t *ResponseFrame  = (TransferDataResponse_t *) ResponseBuffer;

	if (ReqFrame->ServiceID == TRANSFER_DATA_SERVICE_ID)
	{
		if (ReqFrame->BlockNum == PreviousBlockNumber +1) /*Check sequence of block #'s*/
		{
			BlockAddress = ReqFrame->BlockAddress;
			DataSize = ReqFrame->BlockSize;
			Flash_ProgramWrite((void *)ReqFrame->BlockAddress,(void *)&ReqFrame->Data,DataSize);
			for (DataIterator =0 ; DataIterator <DataSize;DataIterator ++)
			{
				Check +=ReqFrame->Data[DataIterator];
			}
			ResponseFrame->CheckSum = (uint_16t)Check;
			ResponseFrame->CheckSum = ~ResponseFrame->CheckSum+1; /*2's compliment of the sum of block data*/
			ErrorCounter = 0;
			ResponseFrame->BlockNum = ReqFrame->BlockNum;
			UDS_SendPositiveResponse(ReqFrame->ServiceID,(void *)ResponseBuffer,TransferDataDone);

		}
		else
		{
			SetError (ReqFrame->ServiceID,GENERAL_PROGRAMMING_FAILURE_CODE);
		}
	}
	else
	{
		SetError (ReqFrame->ServiceID,REQUEST_SEQUENCE_ERROR_CODE);
	}

}

static void TransferDataDone (void)
{

	BootLoaderState = BOOTLOADER_ROUTINE_STATE;/*Validate routine is expected*/
}

static void Request_Transfer_Exit_CBF (void)
{
	ReqTransferExitReq_t *ReqFrame  = (ReqTransferExitReq_t *) ReqBuffer;
	if (ReqFrame->ServiceID == REQUEST_TRANSFER_EXIT_SERVICE_ID)
	{
		UDS_SendPositiveResponse(ReqFrame->ServiceID,(void *)ResponseBuffer,TransferExitDone);
	}
	else
	{
		SetError (ReqFrame->ServiceID,REQUEST_SEQUENCE_ERROR_CODE);
	}

}

static void TransferExitDone (void)
{
	uint_8t i=0;

	for (i=0;i<REQUEST_TRANSFER_EXIT_REQUEST_SIZE;i++)
	{
		ReqBuffer[i]=0;
	}
	BootLoaderState = BOOTLOADER_WRITE_DATA_BY_ID_STATE;
}
static void Write_Data_By_ID_CBF (void)
{
	WriteDataByIDReq_t *ReqFrame  = (WriteDataByIDReq_t *) ReqBuffer;
	if (ReqFrame->ServiceID == WRITE_DATA_BY_IDENTIFIER_SERVICE_ID)
	{
		switch (ReqFrame->DataID)
		{
		case MARKER_ID:
			Flash_ProgramWrite((void *)ROM_Marker,(void *)&ReqFrame->Data,WORD_SIZE);
			UDS_SendPositiveResponse(ReqFrame->ServiceID,(void *)ResponseBuffer,SessionInitialize);
			break;
		case APP_ENTRY_POINT_ID:
			Flash_ProgramWrite((void *)APP_EntryPoint,(void *)&ReqFrame->Data,WORD_SIZE);
			UDS_SendPositiveResponse(ReqFrame->ServiceID,(void *)ResponseBuffer,TransferExitDone);
			break;
		default:
			SetError (ReqFrame->ServiceID,SUB_FUNCTION_NOT_SUPPORTED_CODE);
			break;
		}
	}
	else
	{
		SetError (ReqFrame->ServiceID,REQUEST_SEQUENCE_ERROR_CODE);
	}
}

static void Clear_ROM_Marker(void)
{
	uint_8t ramArray [PAGE_SIZE];
	uint_16t Iterator;

	/*change marker value*/
	/*Move page to RAM*/
	for (Iterator=0;Iterator <PAGE_SIZE;Iterator ++)
	{
		ramArray[Iterator]=((uint_8t *) MARKER_PAGE) [Iterator];
	}
	/*Erase Flash page*/
	Flash_Unlock();
	Flash_ErasePage(MARKER_PAGE);

	/*Change marker value and erase entry point old value in the ram*/
	*(uint_32t *)&(ramArray[1016])=NO_APP;/*Marker*/
	*(uint_32t *)&(ramArray[1020])=CLEAR_WORD;/*Entry point*/
	/*Flash again the marker page after editing*/
	Flash_ProgramWrite((void *)MARKER_PAGE,ramArray,PAGE_SIZE);
	Flash_Lock();
}
static void ECU_Reset_CBF (void)
{
	ECUResetReq_t *ReqFrame  = (ECUResetReq_t *) ReqBuffer;
	ECUResetResponse_t *ResponseFrame  = (ECUResetResponse_t *) ResponseBuffer;
	if (ReqFrame->ServiceID == ECU_RESET_SERVICE_ID)
	{
		switch (ReqFrame->ResetID)
		{
		case SOFT_RESET_ID:
			ResponseFrame->ResetID = ReqFrame->ResetID;
			UDS_SendPositiveResponse(ReqFrame->ServiceID,(void *)ResponseBuffer,DNVIC_voidSysReset);
			break;
			/*	case HARD_RESET_ID:*/
			/*Not supported yet*/
			/*break;*/
		default:
			SetError(ReqFrame->ServiceID,SUB_FUNCTION_NOT_SUPPORTED_CODE);
			break;
		}
	}
	else
	{
		SetError(ReqFrame->ServiceID,REQUEST_SEQUENCE_ERROR_CODE);
	}
}
