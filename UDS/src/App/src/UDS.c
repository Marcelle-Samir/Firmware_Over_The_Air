/*
 * UDS.c
 *
 *  Created on: Jun 9, 2020
 *      Author: toshiba
 */
#include "STD_TYPES.h"
#include "../../Transport/include/UART_TP.h"
#include "UDS.h"

#define NEGATIVE_RESPONSE_ID						0x7F



uint_8t UDS_GetRequest (uint_8t ServiceID, void * RequestData,RxCbf_t cbf)
{
	uint_8t LocalError = OK;
	uint_16t FrameLength;
	switch (ServiceID)
	{
	case DIAGNOSTIC_SESSION_CONTROL_SERVICE_ID:
		FrameLength = DIAGNOSTIC_SESSION_CONTROL_REQUEST_SIZE;
		break;
	case ECU_RESET_SERVICE_ID:
		FrameLength = ECU_RESET_REQUEST_SIZE;
		break;
	case REQUEST_SEED_ID:
		FrameLength = REQUEST_SEED_REQUEST_SIZE;
		break;
	case TRANSFER_KEY_ID:
		FrameLength = TRANSFER_KEY_REQUEST_SIZE;
		break;
	case READ_DATA_BY_IDENTIFIER_SERVICE_ID:
		FrameLength = READ_DATA_BY_IDENTIFIER_REQUEST_SIZE;
		break;
	case WRITE_DATA_BY_IDENTIFIER_SERVICE_ID:
		FrameLength = WRITE_DATA_BY_IDENTIFIER_REQUEST_SIZE;
		break;
	case REQUEST_DOWNLOAD_SERVICE_ID:
		FrameLength = REQUEST_DOWNLOAD_REQUEST_SIZE;
		break;
	case TRANSFER_DATA_SERVICE_ID:
		FrameLength = TRANSFER_DATA_REQUEST_SIZE;
		break;
	case REQUEST_TRANSFER_EXIT_SERVICE_ID:
		FrameLength = REQUEST_TRANSFER_EXIT_REQUEST_SIZE;
		break;
	case ROUTINE_CONTROL_SERVICE_ID:
		FrameLength = ROUTINE_CONTROL_REQUEST_SIZE;
		break;
	default :
		FrameLength = 0;
		LocalError =NOK;
		break;
	}
	LocalError|= UART_TP_SetRxCbf(cbf);
	LocalError|= UART_TP_Receive((uint_8t *)RequestData,FrameLength);
	return LocalError;
}
uint_8t UDS_SendPositiveResponse (uint_8t ServiceID, void * ResponseData,TxCbf_t cbf )
{
	uint_8t LocalError = OK;
	uint_16t FrameLength;
	switch (ServiceID)
	{
	case DIAGNOSTIC_SESSION_CONTROL_SERVICE_ID:
		FrameLength = DIAGNOSTIC_SESSION_CONTROL_RESPONSE_SIZE;
		break;
	case ECU_RESET_SERVICE_ID:
		FrameLength = ECU_RESET_RESPONSE_SIZE;
		break;
	case REQUEST_SEED_ID:
		ServiceID = SECURITY_ACCESS_SERVICE_ID;
		FrameLength = REQUEST_SEED_RESPONSE_SIZE;
		break;
	case TRANSFER_KEY_ID:
		ServiceID = SECURITY_ACCESS_SERVICE_ID;
		FrameLength = TRANSFER_KEY_RESPONSE_SIZE;
		break;
	case READ_DATA_BY_IDENTIFIER_SERVICE_ID:
		FrameLength = READ_DATA_BY_IDENTIFIER_RESPONSE_SIZE;
		break;
	case WRITE_DATA_BY_IDENTIFIER_SERVICE_ID:
		FrameLength = WRITE_DATA_BY_IDENTIFIER_RESPONSE_SIZE;
		break;
	case REQUEST_DOWNLOAD_SERVICE_ID:
		FrameLength = REQUEST_DOWNLOAD_RESPONSE_SIZE;
		break;
	case TRANSFER_DATA_SERVICE_ID:
		FrameLength = TRANSFER_DATA_RESPONSE_SIZE;
		break;
	case REQUEST_TRANSFER_EXIT_SERVICE_ID:
		FrameLength = REQUEST_TRANSFER_EXIT_RESPONSE_SIZE;
		break;
	case ROUTINE_CONTROL_SERVICE_ID:
		FrameLength = ROUTINE_CONTROL_RESPONSE_SIZE;
		break;
	default :
		FrameLength = 0;
		LocalError =NOK;
		break;
	}
	((uint_8t *)ResponseData) [0] = ServiceID + SERVICE_ID_TO_RESPONSE_ID;
	LocalError|= UART_TP_SetTxCbf(cbf);
	LocalError|= UART_TP_Send((uint_8t *)ResponseData,FrameLength);
	return LocalError;

}
uint_8t UDS_SendNegativeResponse (uint_8t ServiceID,uint_8t NRC,RxCbf_t cbf)
{
	static NegativeResponse_t NegativeFrame;
	uint_8t LocalError = OK;
	NegativeFrame.NegativeResponseID = NEGATIVE_RESPONSE_ID;
	NegativeFrame.ServiceID = ServiceID;
	NegativeFrame.NRC = NRC;
	LocalError|= UART_TP_SetTxCbf(cbf);
	LocalError|= UART_TP_Send((uint_8t *)&NegativeFrame,NEGATIVE_RESPONSE_SIZE);
	return LocalError;
}
