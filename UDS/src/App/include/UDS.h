/*
 * UDS.h
 *
 *  Created on: Jun 9, 2020
 *      Author: toshiba
 */

#ifndef APP_INCLUDE_UDS_H_
#define APP_INCLUDE_UDS_H_

#define MARKER_ID 									0xAABB
#define APP_ENTRY_POINT_ID 							0xCCDD


/*General values for all types of frames*/

#define DATA_BLOCK_SIZE								1024
#define NEGATIVE_RESPONSE_SIZE						3
#define SERVICE_ID_TO_RESPONSE_ID					0x40


/*NRC codes list*/
#define GENERAL_REJECT_CODE							0x10
#define SERVICE_NOT_SUPPORTED_CODE					0x11
#define SUB_FUNCTION_NOT_SUPPORTED_CODE				0x12
#define INVALID_FORMAT_CODE							0x13
#define CONDITIONS_NOT_CORRECT_CODE					0x22
#define REQUEST_SEQUENCE_ERROR_CODE					0x24
#define REQUEST_OUT_OF_RANGE_CODE					0x31
#define SECURITY_ACCESS_DENIED_CODE					0x33
#define GENERAL_PROGRAMMING_FAILURE_CODE			0x72
#define RESPONSE_PENDING_CODE						0x78

/*Negative response struct*/
typedef struct
{
	uint_8t NegativeResponseID;
	uint_8t ServiceID;
	uint_8t NRC;

}NegativeResponse_t;

/*List of services used */
/*Diagnostic session control*/
#define DIAGNOSTIC_SESSION_CONTROL_SERVICE_ID		0x10
#define DEFAULT_SESSION_ID							0x01
#define PROGRAMMING_SESSION_ID						0x02
#define EXTENDED_DIAGNOSTIC_SESSION_ID				0x03
#define SAFETY_SYSTEM_DIAGNOSTIC_SESSION_ID			0x04
#define DIAGNOSTIC_SESSION_CONTROL_REQUEST_SIZE		0x02
#define DIAGNOSTIC_SESSION_CONTROL_RESPONSE_SIZE	0x04


typedef struct
{
	uint_8t ServiceID;
	uint_8t SessionID;
}DiagSessCtrlReq_t;

typedef struct
{
	uint_8t ResponseID;
	uint_8t SessionID;
	uint_16t ResponseTime;
}DiagSessCtrlResponse_t;

/*ECU Reset service*/
#define ECU_RESET_SERVICE_ID						0x11
#define HARD_RESET_ID								0x01
#define SOFT_RESET_ID								0x02
#define ECU_RESET_REQUEST_SIZE						0x02
#define ECU_RESET_RESPONSE_SIZE						0x02

typedef struct
{
	uint_8t ServiceID;
	uint_8t ResetID;
}ECUResetReq_t;

typedef struct
{
	uint_8t ResponseID;
	uint_8t ResetID;
}ECUResetResponse_t;


/*Security Access : Request seed - Transfer Key*/
#define SECURITY_ACCESS_SERVICE_ID					0x27
#define REQUEST_SEED_ID								0x01/*use those insted of SECURITY_ACCESS_SERVICE_ID*/
#define TRANSFER_KEY_ID								0x02/*use those insted of SECURITY_ACCESS_SERVICE_ID*/
#define REQUEST_SEED_REQUEST_SIZE					0x02
#define REQUEST_SEED_RESPONSE_SIZE					0x04
#define TRANSFER_KEY_REQUEST_SIZE					0x04
#define TRANSFER_KEY_RESPONSE_SIZE					0x02

typedef struct
{
	uint_8t ServiceID;
	uint_8t SubFuncID;
}RequestSeedReq_t;

typedef struct
{
	uint_8t ResponseID;
	uint_8t SubFuncID;
	uint_16t Seed;
}RequestSeedResponse_t;

typedef struct
{
	uint_8t ServiceID;
	uint_8t SubFuncID;
	uint_16t Key;
}TransferKeyReq_t;

typedef struct
{
	uint_8t ResponseID;
	uint_8t SubFuncID;
}TransferKeyResponse_t;


#define READ_DATA_BY_IDENTIFIER_SERVICE_ID			0x22
#define READ_DATA_BY_IDENTIFIER_REQUEST_SIZE		0x04
#define READ_DATA_BY_IDENTIFIER_RESPONSE_SIZE		0x08


typedef struct
{
	uint_8t ServiceID;
	uint_8t Reserved;
	uint_16t DataID;
}ReadDataByIDReq_t;

typedef struct
{
	uint_8t ResponseID;
	uint_8t Reserved [3];
	uint_32t Data;
}ReadDataByIDResponse_t;


#define WRITE_DATA_BY_IDENTIFIER_SERVICE_ID			0x2E
#define WRITE_DATA_BY_IDENTIFIER_REQUEST_SIZE		0x08
#define WRITE_DATA_BY_IDENTIFIER_RESPONSE_SIZE		0x02
typedef struct
{
	uint_8t ServiceID;
	uint_8t Reserved;
	uint_16t DataID;
	uint_32t Data;
}WriteDataByIDReq_t;

typedef struct
{
	uint_8t ResponseID;
	uint_8t reserved;
}WriteDataByIDResponse_t;

#define REQUEST_DOWNLOAD_SERVICE_ID					0x34
#define REQUEST_DOWNLOAD_REQUEST_SIZE				0x04
#define REQUEST_DOWNLOAD_RESPONSE_SIZE				0x04
#define WORD_SIZE									0X04
typedef struct
{
	uint_8t ServiceID;
	uint_8t MemAddLength;
	uint_16t AppSize;
}RequestDownloadReq_t;

typedef struct
{
	uint_8t ResponseID;
	uint_8t Reserved;
	uint_16t DataBlockSize;
}RequestDownloadResponse_t;


#define TRANSFER_DATA_SERVICE_ID					0x36
#define TRANSFER_DATA_REQUEST_SIZE					0x08+DATA_BLOCK_SIZE
#define TRANSFER_DATA_RESPONSE_SIZE					0x04
typedef struct
{
	uint_8t ServiceID;
	uint_8t BlockNum;
	uint_16t BlockSize;
	uint_32t BlockAddress;
	uint_8t Data [DATA_BLOCK_SIZE];
}TransferDataReq_t;

typedef struct
{
	uint_8t ResponseID;
	uint_8t BlockNum;
	uint_16t CheckSum;
}TransferDataResponse_t;

#define REQUEST_TRANSFER_EXIT_SERVICE_ID			0x37
#define REQUEST_TRANSFER_EXIT_REQUEST_SIZE			0x02
#define REQUEST_TRANSFER_EXIT_RESPONSE_SIZE			0x02

typedef struct
{
	uint_8t ServiceID;
	uint_8t reserved;
}ReqTransferExitReq_t;

typedef struct
{
	uint_8t ResponseID;
	uint_8t reserved;

}ReqTransferExitResponse_t;

#define ROUTINE_CONTROL_SERVICE_ID					0x31
#define ROUTINE_CONTROL_REQUEST_SIZE				0x04
#define ROUTINE_CONTROL_RESPONSE_SIZE				0x04
#define START_ROUTINE_ID							0x01
#define STOP_ROUTINE_ID								0x02
#define QUERY_ROUTINE_RESULT_ID						0x03
#define ERASE_APPLICATION_ROUTINE_ID				0xABCD
#define VALIDATE_BLOCK_ROUTINE_ID					0x9876


typedef struct
{
	uint_8t ServiceID;
	uint_8t ControlRoutineSignalID;
	uint_16t RoutineID;
}RoutineControlReq_t;

typedef struct
{
	uint_8t ResponseID;
	uint_8t ControlRoutineSignalID;
	uint_16t RoutineID;
}RoutineControlResponse_t;

/*UDS APIs*/
uint_8t UDS_GetRequest (uint_8t ServiceID, void * RequestData,RxCbf_t cbf);
uint_8t UDS_SendPositiveResponse (uint_8t ServiceID, void * ResponseData,TxCbf_t cbf );
uint_8t UDS_SendNegativeResponse (uint_8t ServiceID,uint_8t NRC,RxCbf_t cbf);


#endif /* APP_INCLUDE_UDS_H_ */
