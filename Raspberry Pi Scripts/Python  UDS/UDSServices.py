from Trans import *
###################UDS Frames Parameters ###################################################################
############ General UDS Parameters ########################################################################
#define SERVICE_ID_TO_RESPONSE_ID					0x40
#define NEGATIVE_RESPONSE_ID						0x7F
SERVICE_ID_TO_RESPONSE_ID = 0x40
NEGATIVE_RESPONSE_ID = 0x7F
ID_LOCATION = 0

PADDING_VALUE = 0xFF
###################NRC CODES ###############################################################################
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
GENERAL_REJECT_CODE					  	=	0x10
SERVICE_NOT_SUPPORTED_CODE			=	0x11
SUB_FUNCTION_NOT_SUPPORTED_CODE	=	0x12
INVALID_FORMAT_CODE						  =	0x13
CONDITIONS_NOT_CORRECT_CODE			=	0x22
REQUEST_SEQUENCE_ERROR_CODE			=	0x24
REQUEST_OUT_OF_RANGE_CODE				=	0x31
SECURITY_ACCESS_DENIED_CODE			=	0x33
GENERAL_PROGRAMMING_FAILURE_CODE=	0x72
RESPONSE_PENDING_CODE						= 0x78

############Diagnostic session control#######################################################################
#define DIAGNOSTIC_SESSION_CONTROL_SERVICE_ID		0x10
#define DEFAULT_SESSION_ID							0x01
#define PROGRAMMING_SESSION_ID						0x02
#define EXTENDED_DIAGNOSTIC_SESSION_ID				0x03
#define SAFETY_SYSTEM_DIAGNOSTIC_SESSION_ID			0x04
#define DIAGNOSTIC_SESSION_CONTROL_REQUEST_SIZE		0x02
#define DIAGNOSTIC_SESSION_CONTROL_RESPONSE_SIZE	0x04
DIAGNOSTIC_SESSION_CONTROL_SERVICE_ID   =		0x10
DEFAULT_SESSION_ID							        =   0x01
PROGRAMMING_SESSION_ID						      =   0x02
EXTENDED_DIAGNOSTIC_SESSION_ID				  =   0x03
SAFETY_SYSTEM_DIAGNOSTIC_SESSION_ID			=   0x04
DIAGNOSTIC_SESSION_CONTROL_REQUEST_SIZE	=	  0x02
DIAGNOSTIC_SESSION_CONTROL_RESPONSE_SIZE= 	0x04
########## ECU Reset service ################################################################################
#define ECU_RESET_SERVICE_ID						0x11
#define HARD_RESET_ID								0x01
#define SOFT_RESET_ID								0x02
#define ECU_RESET_REQUEST_SIZE						0x02
#define ECU_RESET_RESPONSE_SIZE						0x02
ECU_RESET_SERVICE_ID			=	0x11
HARD_RESET_ID							=	0x01
SOFT_RESET_ID							=	0x02
ECU_RESET_REQUEST_SIZE		=	0x02
ECU_RESET_RESPONSE_SIZE		=	0x02
########## Security Access : Request seed - Transfer Key##################################################
#define SECURITY_ACCESS_SERVICE_ID					0x27
#define REQUEST_SEED_ID								0x01
#define TRANSFER_KEY_ID								0x02
#define REQUEST_SEED_REQUEST_SIZE					0x02
#define REQUEST_SEED_RESPONSE_SIZE					0x04
#define TRANSFER_KEY_REQUEST_SIZE					0x04
#define TRANSFER_KEY_RESPONSE_SIZE					0x02
SECURITY_ACCESS_SERVICE_ID	=	0x27
REQUEST_SEED_ID							=	0x01
TRANSFER_KEY_ID							=	0x02
REQUEST_SEED_REQUEST_SIZE		=	0x02
REQUEST_SEED_RESPONSE_SIZE	=	0x04
TRANSFER_KEY_REQUEST_SIZE		=	0x04
TRANSFER_KEY_RESPONSE_SIZE	=	0x02
############Marker Variables ###############################################################################
#define MARKER_ID 									0xAABB
MARKER_ID = 0xAABB
###############AppEntryPoint ID ########################################################################
#define APP_ENTRY_POINT_ID 							0xCCDD
APP_ENTRY_POINT_ID = 0xCCDD
##########Read Data by identifier ##################################################
#define READ_DATA_BY_IDENTIFIER_SERVICE_ID			0x22
#define READ_DATA_BY_IDENTIFIER_REQUEST_SIZE		0x02
#define READ_DATA_BY_IDENTIFIER_RESPONSE_SIZE		0x07
READ_DATA_BY_IDENTIFIER_SERVICE_ID		=	0x22
READ_DATA_BY_IDENTIFIER_REQUEST_SIZE	=	0x04
READ_DATA_BY_IDENTIFIER_RESPONSE_SIZE	=	0x08
##########Write Data by identifier ########################################################################
#define WRITE_DATA_BY_IDENTIFIER_SERVICE_ID			0x2E
#define WRITE_DATA_BY_IDENTIFIER_REQUEST_SIZE		0x08
#define WRITE_DATA_BY_IDENTIFIER_RESPONSE_SIZE	0x01
WRITE_DATA_BY_IDENTIFIER_SERVICE_ID		  =	0x2E
WRITE_DATA_BY_IDENTIFIER_REQUEST_SIZE	  =	0x08
WRITE_DATA_BY_IDENTIFIER_RESPONSE_SIZE	=	0x02
##########Request Download ################################################################################
#define REQUEST_DOWNLOAD_SERVICE_ID					0x34
#define REQUEST_DOWNLOAD_REQUEST_SIZE				0x04
#define REQUEST_DOWNLOAD_RESPONSE_SIZE			0x04
#define WORD_SIZE									0X04
REQUEST_DOWNLOAD_SERVICE_ID			=	0x34
REQUEST_DOWNLOAD_REQUEST_SIZE		=	0x04
REQUEST_DOWNLOAD_RESPONSE_SIZE	=	0x04
WORD_SIZE								        = 0X04
##########Transfer data ################################################################################
#define TRANSFER_DATA_SERVICE_ID					0x36
#define TRANSFER_DATA_REQUEST_SIZE				0x08+DATA_BLOCK_SIZE
#define TRANSFER_DATA_RESPONSE_SIZE				0x04
TRANSFER_DATA_SERVICE_ID			=	0x36
TRANSFER_DATA_REQUEST_SIZE		=	0x08
TRANSFER_DATA_RESPONSE_SIZE		=	0x04
##########Request transfer exit ################################################################################
#define REQUEST_TRANSFER_EXIT_SERVICE_ID			0x37
#define REQUEST_TRANSFER_EXIT_REQUEST_SIZE			0x01
#define REQUEST_TRANSFER_EXIT_RESPONSE_SIZE			0x01
REQUEST_TRANSFER_EXIT_SERVICE_ID		  =	0x37
REQUEST_TRANSFER_EXIT_REQUEST_SIZE		=	0x02
REQUEST_TRANSFER_EXIT_RESPONSE_SIZE		=	0x02
##########Routine control ################################################################################
#define ROUTINE_CONTROL_SERVICE_ID					0x31
#define ROUTINE_CONTROL_REQUEST_SIZE				0x04
#define ROUTINE_CONTROL_RESPONSE_SIZE				0x04
#define START_ROUTINE_ID							0x01
#define STOP_ROUTINE_ID								0x02
#define QUERY_ROUTINE_RESULT_ID						0x03
#define ERASE_APPLICATION_ROUTINE_ID				0xABCD
#define VALIDATE_BLOCK_ROUTINE_ID					0x9876
ROUTINE_CONTROL_SERVICE_ID			=		0x31
ROUTINE_CONTROL_REQUEST_SIZE		=		0x04
ROUTINE_CONTROL_RESPONSE_SIZE		=		0x04
START_ROUTINE_ID						    =  	0x01
STOP_ROUTINE_ID							    =  	0x02
QUERY_ROUTINE_RESULT_ID				  =		0x03
ERASE_APPLICATION_ROUTINE_ID		=		0xABCD
VALIDATE_BLOCK_ROUTINE_ID				=  	0x9876
class UDSService:
  ServiceID=0
  PositiveResponseFrameSize=0
  RequestFrame=[]
  ResponseFrame=[]
  NegativeResponseFrameSize=3
  def __init__ (self,SID,PFS):
    self.ServiceID = SID
    self.PositiveResponseFrameSize = PFS
    
  def SendRequest (self,serialPort,s):
    Transport_TX(serialPort,self.RequestFrame,s)
     
  def ReceiveResponse(self,serialPort):
    self.ResponseFrame=Transport_RX(serialPort,self.PositiveResponseFrameSize)
  
  def isPositiveResponse(self):
    if len (self.ResponseFrame)==0:
      return False
    elif self.ResponseFrame[ID_LOCATION] == self.ServiceID + SERVICE_ID_TO_RESPONSE_ID and len(self.ResponseFrame) == self.PositiveResponseFrameSize:
      return True
    else:
      return False
  def isNegativeResponse(self):
    if len (self.ResponseFrame)==0:
      return False
    elif self.ResponseFrame[ID_LOCATION] == NEGATIVE_RESPONSE_ID  and len(self.ResponseFrame) >= self.NegativeResponseFrameSize:
      return True
    else:
      return False  
  def SetRequest (self,ReqFrame):
    self.RequestFrame = ReqFrame

    
    
  