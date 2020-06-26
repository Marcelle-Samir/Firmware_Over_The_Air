import sys
import os
from serial import serialwin32
from elftools.elf.elffile import ELFFile , Segment
from elftools.elf.structs import ELFStructs
from Trans import *
from UDSServices import *
DATA_BLOCK_SIZE = 0
                
##################Communication configuration parameters ###############################################################
port = "COM29"
BaudRate = 115200
serial_timeout = 8
seri = Transport_Init(port,BaudRate,serial_timeout)
#################### Bootloader parameters ####################################################
BL_SIZE=0x2C00                        #Bootloader size = 11 KB = 0x2C00
#define MAX_ERRORS_TIMES				3
MAX_ERRORS_TIMES = 3
#define APP_FOUND                     0xAABBCCDD
#define NO_APP                        0xFFFFFFFF
APP_FOUND = 0xAABBCCDD
NO_APP = 0xFFFFFFFF
MEMORY_ADDRESS_LENGTH = WORD_SIZE
####################Flash-Constants ###########################################################################
START_ADDRESS=0x08000000              #start address of flash (0x08000000)  
FINAL_ADDRESS=0x08010000              #Flash Size = 64K
START_AVAILABLE_ADDRESS = START_ADDRESS + BL_SIZE #start address of flash (0x08000000) + + BL size shift (0x2C00)
################### Elf Parser Constants ################################################################
file=open(sys.argv[1],"rb")
elf_Handler =ELFFile(file)
Header=elf_Handler.header   #elf file header
Magic=Header.e_ident ['EI_MAG'] #magic number
EntryPoint=Header.e_entry #entry point
program_header_number =elf_Handler.num_segments() #number of segments in the elf file
elf_Class=elf_Handler.elfclass #elf file class
segments_header=[]
segments=[]

################## UDS states ####################################################################################
UDS_INITIAL_STATE     						= 0x01
UDS_WAITING_STATE			      			= 0x02
UDS_START_PROG_SESSION_STATE			=	0x03
UDS_SECURITY_ACCESS_STATE		      =	0x04
UDS_ERASE_MEM_ROUTINE_STATE	      = 0x05
UDS_REQUEST_DOWNLOAD_STATE	      =	0x06
UDS_TRANSFER_DATA_STATE			      =	0x07
UDS_REQUEST_TRANSFER_EXIT		      =	0x08
UDS_WRITE_MARKER_DATA_BY_ID_STATE =	0x09
UDS_WRITE_ENTRY_DATA_BY_ID_STATE  =	0x0A
UDS_START_DEFAULT_SESSION_STATE		=	0x0B
UDS_ECU_RESET_STATE					      =	0x0C

################## UDS Services INITIALIZATION #############################################################
ReadByID_Service = UDSService (READ_DATA_BY_IDENTIFIER_SERVICE_ID,READ_DATA_BY_IDENTIFIER_RESPONSE_SIZE)
SessionControl_Service = UDSService (DIAGNOSTIC_SESSION_CONTROL_SERVICE_ID,DIAGNOSTIC_SESSION_CONTROL_RESPONSE_SIZE)
SecurityAccessSeedRequest_Service = UDSService (SECURITY_ACCESS_SERVICE_ID,REQUEST_SEED_RESPONSE_SIZE)
SecurityAccessTransferKey_Service = UDSService (SECURITY_ACCESS_SERVICE_ID,TRANSFER_KEY_RESPONSE_SIZE)
Routinecontrol_Service = UDSService (ROUTINE_CONTROL_SERVICE_ID,ROUTINE_CONTROL_RESPONSE_SIZE)
RequestDownload_Service = UDSService (REQUEST_DOWNLOAD_SERVICE_ID,REQUEST_DOWNLOAD_RESPONSE_SIZE)
TransferData_Service = UDSService (TRANSFER_DATA_SERVICE_ID,TRANSFER_DATA_RESPONSE_SIZE)
RequestTransferExit_Service = UDSService (REQUEST_TRANSFER_EXIT_SERVICE_ID,REQUEST_TRANSFER_EXIT_RESPONSE_SIZE)
WriteByID_Service = UDSService (WRITE_DATA_BY_IDENTIFIER_SERVICE_ID,WRITE_DATA_BY_IDENTIFIER_RESPONSE_SIZE)
ECUReset_Service = UDSService (ECU_RESET_SERVICE_ID,ECU_RESET_RESPONSE_SIZE)
################API's ########################################################################################
#Verification function
def verify_Elf_File():
    if Magic[0] !=127 or  Magic[1] !=69 or  Magic[2] !=76 or  Magic[3] !=70 or  elf_Class !=32 :
      return False
    else: 
      return True
#Read Marker and checks it's value
def verify_Marker_Value():
  reqFrame=[]
  reqFrame.insert (len(reqFrame),ReadByID_Service.ServiceID.to_bytes(1, 'little'))
  reqFrame.insert (len(reqFrame),ReadByID_Service.ServiceID.to_bytes(1, 'little'))
  for i in MARKER_ID.to_bytes(2, 'little'):
    reqFrame.insert (len(reqFrame),i.to_bytes(1, 'little'))  
  ReadByID_Service.SetRequest(reqFrame)
  ReadByID_Service.SendRequest(seri,READ_DATA_BY_IDENTIFIER_REQUEST_SIZE)
  print ("Read Marker was sent wait for a response")
  ReadByID_Service.ReceiveResponse(seri)
  if ReadByID_Service.isPositiveResponse():
    #Check on received marker value#
    Marker_Value = int(ReadByID_Service.ResponseFrame[7]<<24)+int(ReadByID_Service.ResponseFrame[6]<<16)+int(ReadByID_Service.ResponseFrame[5]<<8)+int(ReadByID_Service.ResponseFrame[4])
    if Marker_Value == NO_APP:
      print ("Marker has the correct value")
      return True
    else:
      print ("Wrong value for the marker")
      return False
  elif ReadByID_Service.isNegativeResponse():
    print ("Negative Response has received for service ID:"+str(ReadByID_Service.ServiceID))
    return False
  else:
    print ("Error in communication at service ID:"+str(ReadByID_Service.ServiceID))
    return False
#Starting session and sets the timeout with the new response time
def StartSession(SESSION_ID):
  t=0
  SessionControl_Service.SetRequest([SessionControl_Service.ServiceID.to_bytes(1, 'little'),SESSION_ID.to_bytes(1, 'little')])
  SessionControl_Service.SendRequest(seri,DIAGNOSTIC_SESSION_CONTROL_REQUEST_SIZE)
  print ("Session control was sent wait for a response")
  SessionControl_Service.ReceiveResponse(seri)
  if SessionControl_Service.isPositiveResponse():
    #Check on sessin ID is same as the one we have sent#
    if SessionControl_Service.ResponseFrame [1] == SESSION_ID:
      t = int(SessionControl_Service.ResponseFrame[3]<<8)+int(SessionControl_Service.ResponseFrame[2])
      seri.timeout = t
      return True
    else:
      print ("difference between sent and received SessionID")
      return False
  elif SessionControl_Service.isNegativeResponse():
    print ("Negative Response has received for service ID:"+str(SessionControl_Service.ServiceID))
    return False
  else:
    print ("Error in communication at service ID:"+str(SessionControl_Service.ServiceID))
    return False
#Get the security access from the microcontroller
def GetSecureAccess ():
  SEED=0
  KEY=0
  reqFrame=[]
  SecurityAccessSeedRequest_Service.SetRequest([SecurityAccessSeedRequest_Service.ServiceID.to_bytes(1, 'little'),REQUEST_SEED_ID.to_bytes(1, 'little')])
  SecurityAccessSeedRequest_Service.SendRequest(seri,REQUEST_SEED_REQUEST_SIZE)
  print ("Request Seed was sent wait for a response")
  SecurityAccessSeedRequest_Service.ReceiveResponse(seri)
  if SecurityAccessSeedRequest_Service.isPositiveResponse():
    #Check on Received Sub function #
    if SecurityAccessSeedRequest_Service.ResponseFrame [1].to_bytes (1,'little') == SecurityAccessSeedRequest_Service.RequestFrame [1]:
      SEED = int(SecurityAccessSeedRequest_Service.ResponseFrame[3]<<8)+int(SecurityAccessSeedRequest_Service.ResponseFrame[2])
      KEY = GenerateKey(SEED)
      reqFrame.insert (len(reqFrame),SecurityAccessTransferKey_Service.ServiceID.to_bytes(1, 'little'))
      reqFrame.insert (len(reqFrame),TRANSFER_KEY_ID.to_bytes(1, 'little'))
      for i in KEY.to_bytes(2, 'little'):
        reqFrame.insert (len(reqFrame),i.to_bytes(1, 'little')) 
      SecurityAccessTransferKey_Service.SetRequest(reqFrame) 
      SecurityAccessTransferKey_Service.SendRequest(seri,TRANSFER_KEY_REQUEST_SIZE)
      print ("transfer key was sent wait for a response")
      SecurityAccessTransferKey_Service.ReceiveResponse(seri)
      if SecurityAccessTransferKey_Service.isPositiveResponse():
        print ("Secure Access granted")
        return True
      elif SecurityAccessTransferKey_Service.isNegativeResponse():
        print ("Negative Response has received for service ID:"+str(SessionControl_Service.ServiceID))
        return False   
      else:
        print ("Error in communication at service ID:"+str(SessionControl_Service.ServiceID))
        return False
    else:
      print ("difference between sent and received subfunction")
      return False
  elif SecurityAccessSeedRequest_Service.isNegativeResponse():
    print ("Negative Response has received for service ID:"+str(SecurityAccessSeedRequest_Service.ServiceID))
    return False
  else:
    print ("Error in communication at service ID:"+str(SecurityAccessSeedRequest_Service.ServiceID))
    return False
def GenerateKey(SEED):
  Temp=(SEED-0x50)*10
  Temp&=0xFFFF
  return Temp
def ControlRoutine (ControlSignal,RoutineID):
  reqFrame=[]
  reqFrame.insert (len(reqFrame),Routinecontrol_Service.ServiceID.to_bytes(1, 'little'))
  reqFrame.insert (len(reqFrame),ControlSignal.to_bytes(1, 'little'))
  for i in RoutineID.to_bytes(2, 'little'):
    reqFrame.insert (len(reqFrame),i.to_bytes(1, 'little'))   
  Routinecontrol_Service.SetRequest(reqFrame)
  Routinecontrol_Service.SendRequest(seri,ROUTINE_CONTROL_REQUEST_SIZE)
  print ("Routine control was sent wait for a response")
  Routinecontrol_Service.ReceiveResponse(seri)
  if Routinecontrol_Service.isPositiveResponse():
    #Check on sessin ID is same as the one we have sent#
    print ("Control Routine successed ")
    return True
  elif Routinecontrol_Service.isNegativeResponse():
    print ("Negative Response has received for service ID:"+str(Routinecontrol_Service.ServiceID))
    return False
  else:
    print ("Error in communication at service ID:"+str(Routinecontrol_Service.ServiceID))
    return False
def RequestDownload (MLength,AppS):
  global DATA_BLOCK_SIZE
  reqFrame=[]
  reqFrame.insert (len(reqFrame),RequestDownload_Service.ServiceID.to_bytes(1, 'little'))
  reqFrame.insert (len(reqFrame),MLength.to_bytes(1, 'little'))
  for i in AppS.to_bytes(2, 'little'):
    reqFrame.insert (len(reqFrame),i.to_bytes(1, 'little'))   
  RequestDownload_Service.SetRequest(reqFrame)
  RequestDownload_Service.SendRequest(seri,REQUEST_DOWNLOAD_REQUEST_SIZE)
  print ("Request was sent wait for a response")
  RequestDownload_Service.ReceiveResponse(seri)
  if RequestDownload_Service.isPositiveResponse():
    print ("Request Download positive response")
    DATA_BLOCK_SIZE = int(RequestDownload_Service.ResponseFrame[3]<<8)+int(RequestDownload_Service.ResponseFrame[2])
    return True
  elif RequestDownload_Service.isNegativeResponse():
    print ("Negative Response has received for service ID:"+str(RequestDownload_Service.ServiceID))
    return False
  else:
    print ("Error in communication at service ID:"+str(RequestDownload_Service.ServiceID))
    return False
def TransmitData (APPSize):
  FrameSize = TRANSFER_DATA_REQUEST_SIZE + DATA_BLOCK_SIZE
  CheckSum =0
  Block_num=1
  First_Segment_check=0
  Current_Address = START_AVAILABLE_ADDRESS 
  Block_size=0
  current_segment_index=0 
  current_segment_data_pos=BL_SIZE
  remaining_size=0
  current_segment_data = 0
  reqFrame=[]
  while current_segment_index <program_header_number:
    if segments_header[current_segment_index]['p_paddr'] >= START_ADDRESS and segments_header[current_segment_index]['p_paddr'] < FINAL_ADDRESS and segments_header[current_segment_index]['p_flags'] != 4:
      if First_Segment_check == 0:
        remaining_size=segments_header[current_segment_index]['p_filesz']-BL_SIZE
        current_segment_data = segments[current_segment_index].data()
        First_Segment_check =1       
      reqFrame.insert (len(reqFrame),TransferData_Service.ServiceID.to_bytes(1, 'little'))
      reqFrame.insert (len(reqFrame),Block_num.to_bytes(1, 'little'))
      Block_size = min (remaining_size,DATA_BLOCK_SIZE)
      for i in Block_size.to_bytes(2, 'little'):
        reqFrame.insert (len(reqFrame),i.to_bytes(1, 'little'))
      for i in Current_Address.to_bytes(4, 'little'):
        reqFrame.insert (len(reqFrame),i.to_bytes(1, 'little'))
      print ("size = ",str(Block_size))
      print ("Pos = ",str(current_segment_data_pos))
      for elements in range (current_segment_data_pos,current_segment_data_pos+Block_size):
        reqFrame.insert(len(reqFrame),current_segment_data[elements].to_bytes(1, 'little'))
      if (Block_size <DATA_BLOCK_SIZE ):
        for remained in range (0,DATA_BLOCK_SIZE-Block_size):
          reqFrame.insert(len(reqFrame),PADDING_VALUE.to_bytes(1, 'little'))
      TransferData_Service.SetRequest (reqFrame)
      TransferData_Service.SendRequest(seri,FrameSize)
      print ("Send Data Block:"+str(Block_num)+" was sent wait for a response")
      TransferData_Service.ReceiveResponse(seri)
      if TransferData_Service.isPositiveResponse():
        #check on received checksum is correct
        for i in range(8,8 + Block_size):
          CheckSum += int.from_bytes(reqFrame[i], byteorder='little', signed=False)
        CheckSum &= 0xffff
        CheckSum ^= 0xffff
        CheckSum +=1
        #print ("Calculated Checksum:"+str(CheckSum))
        #print ("Received Checksum:"+str(int(TransferData_Service.ResponseFrame[3]<<8)+int(TransferData_Service.ResponseFrame[2])))
        if CheckSum == int(TransferData_Service.ResponseFrame[3]<<8)+int(TransferData_Service.ResponseFrame[2]):
          CheckSum=0
          print ("Check sum is correct. Proceede to Block Validation")
          ValidateBlock = ControlRoutine (START_ROUTINE_ID,VALIDATE_BLOCK_ROUTINE_ID)
          if ValidateBlock == True :
            remaining_size-=Block_size
            Block_num +=1
            reqFrame=[]
            if remaining_size==0: #new segment
              print ("Finished Segment #",str(current_segment_index))
              current_segment_index+=1
              if current_segment_index == program_header_number:
                print ("Data send is done")
                return True
              print ("Start Flashing Segment #",str(current_segment_index))
              remaining_size = segments_header[current_segment_index]['p_filesz']
              current_segment_data_pos=0
              Current_Address = segments_header[current_segment_index]['p_paddr']
              current_segment_data = segments[current_segment_index].data()
            else: #Still in Same segment
              Current_Address+=Block_size
              current_segment_data_pos+=Block_size
          else:
            print ("Error in Validation Block #"+str(Block_num))
            return False
        else:
          print ("Error in checksum for Block# :"+str(Block_num))
          return False
      elif TransferData_Service.isNegativeResponse():
        print ("Negative Response has received for service ID:"+str(TransferData_Service.ServiceID))
        return False
      else:
        print ("Error in communication at service ID:"+str(TransferData_Service.ServiceID))
        return False
    else: 
      print ("This Segment is not located at the Flash memory or it is not writable")
      current_segment_index+=1
  return True
  
def ReqTransferExit ():
  RequestTransferExit_Service.SetRequest([RequestTransferExit_Service.ServiceID.to_bytes(1, 'little'),RequestTransferExit_Service.ServiceID.to_bytes(1, 'little')])
  RequestTransferExit_Service.SendRequest(seri,REQUEST_TRANSFER_EXIT_REQUEST_SIZE)
  print ("Request transfer exit was sent wait for a response")
  RequestTransferExit_Service.ReceiveResponse(seri)
  if RequestTransferExit_Service.isPositiveResponse():
    print ("Request Transfer Exit successed ")
    return True
  elif RequestTransferExit_Service.isNegativeResponse():
    print ("Negative Response has received for service ID:"+str(RequestTransferExit_Service.ServiceID))
    return False
  else:
    print ("Error in communication at service ID:"+str(RequestTransferExit_Service.ServiceID))
    return False
def WriteData (ID,Data):
  reqFrame=[]
  reqFrame.insert (len(reqFrame),WriteByID_Service.ServiceID.to_bytes(1, 'little'))
  reqFrame.insert (len(reqFrame),WriteByID_Service.ServiceID.to_bytes(1, 'little'))
  for i in ID.to_bytes(2, 'little'):
    reqFrame.insert (len(reqFrame),i.to_bytes(1, 'little'))
  for i in Data.to_bytes(4, 'little'):
    reqFrame.insert (len(reqFrame),i.to_bytes(1, 'little'))
  WriteByID_Service.SetRequest(reqFrame)
  WriteByID_Service.SendRequest(seri,WRITE_DATA_BY_IDENTIFIER_REQUEST_SIZE)
  print ("Write Data was sent wait for a response")
  WriteByID_Service.ReceiveResponse(seri)
  if WriteByID_Service.isPositiveResponse():
    print ("Write Data successed ")
    return True
  elif WriteByID_Service.isNegativeResponse():
    print ("Negative Response has received for service ID:"+str(WriteByID_Service.ServiceID))
    return False
  else:
    print ("Error in communication at service ID:"+str(WriteByID_Service.ServiceID))
    return False
def ResetECU (RESET_ID):
  reqFrame=[]
  reqFrame.insert (len(reqFrame),ECUReset_Service.ServiceID.to_bytes(1, 'little'))
  reqFrame.insert (len(reqFrame),RESET_ID.to_bytes(1, 'little'))
  ECUReset_Service.SetRequest(reqFrame)
  ECUReset_Service.SendRequest(seri,ECU_RESET_REQUEST_SIZE)
  print ("ECU Reset was sent wait for a response")
  ECUReset_Service.ReceiveResponse(seri)
  if ECUReset_Service.isPositiveResponse():
    print ("ECU Reset Exit successed ")
    return True
  elif ECUReset_Service.isNegativeResponse():
    print ("Negative Response has received for service ID:"+str(ECUReset_Service.ServiceID))
    return False
  else:
    print ("Error in communication at service ID:"+str(ECUReset_Service.ServiceID))
    return False  
################# main #######################################################################################
def main ():
  CheckFile=verify_Elf_File()
  ErrorCounter=1
  APPSize = 0
  if CheckFile == True :
    print ("Elf file verified")
    for i in range(0,program_header_number):
        if elf_Handler._get_segment_header(i)['p_type']:
          segments_header.append(elf_Handler._get_segment_header(i))#elf file segments header
          segments.append(elf_Handler. get_segment(i)) #elf file segments
        if segments_header [i]['p_type'] == 'PT_LOAD':
          APPSize += segments_header [i]['p_filesz']
    APPSize-=BL_SIZE
############## Start UDS State machine #####################################################################3
    UDS_STATE = UDS_INITIAL_STATE
    while True:
      if UDS_STATE == UDS_INITIAL_STATE:
        MarkerCheck = verify_Marker_Value() #Step1,2
        if MarkerCheck == True:
          UDS_STATE = UDS_START_PROG_SESSION_STATE
          ErrorCounter = 1
        elif MarkerCheck == False and ErrorCounter < MAX_ERRORS_TIMES :  
          ErrorCounter +=1
          print ("Error at State: "+str(UDS_STATE))
        else:
          print ("Reached Max Times of errors!!!")
          break
      elif UDS_STATE == UDS_START_PROG_SESSION_STATE:
        InitializeProgramingSession = StartSession(PROGRAMMING_SESSION_ID) #step3,4
        if InitializeProgramingSession == True :
          UDS_STATE = UDS_SECURITY_ACCESS_STATE
          ErrorCounter = 1
        elif InitializeProgramingSession == False and ErrorCounter < MAX_ERRORS_TIMES :  
          print ("Error at State: "+str(UDS_STATE))
          ErrorCounter +=1
        else:
          print ("Reached Max Times of errors!!!")
          break
      elif UDS_STATE == UDS_SECURITY_ACCESS_STATE:
        SecurityAccess = GetSecureAccess ()
        if SecurityAccess == True :
          UDS_STATE = UDS_ERASE_MEM_ROUTINE_STATE
          ErrorCounter = 1
        elif SecurityAccess == False and ErrorCounter < MAX_ERRORS_TIMES :  
          print ("Error at State: "+str(UDS_STATE))
          ErrorCounter +=1
        else:
          print ("Reached Max Times of errors!!!")
          break        
      elif UDS_STATE == UDS_ERASE_MEM_ROUTINE_STATE: 
        EraseMem = ControlRoutine (START_ROUTINE_ID,ERASE_APPLICATION_ROUTINE_ID)
        if EraseMem == True :
          ErrorCounter = 1
          print ("Phase 1 done")
          UDS_STATE = UDS_REQUEST_DOWNLOAD_STATE
        elif EraseMem == False and ErrorCounter < MAX_ERRORS_TIMES :  
          print ("Error at State: "+str(UDS_STATE))
          ErrorCounter +=1
        else:
          print ("Reached Max Times of errors!!!")
          break 
      elif UDS_STATE == UDS_REQUEST_DOWNLOAD_STATE: 
        ReqDownload = RequestDownload (MEMORY_ADDRESS_LENGTH,APPSize)
        if ReqDownload == True :
          ErrorCounter = 1
          UDS_STATE = UDS_TRANSFER_DATA_STATE
        elif ReqDownload == False and ErrorCounter < MAX_ERRORS_TIMES :  
          print ("Error at State: "+str(UDS_STATE))
          ErrorCounter +=1
        else:
          print ("Reached Max Times of errors!!!")
          break
      elif UDS_STATE == UDS_TRANSFER_DATA_STATE:
        print ("Start Downloading")
        DataTransmission = TransmitData (APPSize)
        if DataTransmission == True :
          ErrorCounter = 1
          UDS_STATE = UDS_REQUEST_TRANSFER_EXIT
        elif DataTransmission == False and ErrorCounter < MAX_ERRORS_TIMES :  
          print ("Error at State: "+str(UDS_STATE))
          ErrorCounter +=1
        else:
          print ("Reached Max Times of errors!!!")
          break           
      elif UDS_STATE == UDS_REQUEST_TRANSFER_EXIT:
        TransferExit = ReqTransferExit ()
        if TransferExit == True :
          ErrorCounter = 1
          UDS_STATE = UDS_WRITE_ENTRY_DATA_BY_ID_STATE
        elif TransferExit == False and ErrorCounter < MAX_ERRORS_TIMES :  
          print ("Error at State: "+str(UDS_STATE))
          ErrorCounter +=1
        else:
          print ("Reached Max Times of errors!!!")
          break
      elif UDS_STATE == UDS_WRITE_ENTRY_DATA_BY_ID_STATE:
        WriteEntryCheck = WriteData (APP_ENTRY_POINT_ID,EntryPoint)
        if WriteEntryCheck == True :
          ErrorCounter = 1
          UDS_STATE = UDS_WRITE_MARKER_DATA_BY_ID_STATE
        elif WriteEntryCheck == False and ErrorCounter < MAX_ERRORS_TIMES :  
          print ("Error at State: "+str(UDS_STATE))
          ErrorCounter +=1
        else:
          print ("Reached Max Times of errors!!!")
          break
      elif UDS_STATE == UDS_WRITE_MARKER_DATA_BY_ID_STATE:
        WriteMarkerCheck = WriteData (MARKER_ID,APP_FOUND)
        if WriteMarkerCheck == True :
          ErrorCounter = 1
          UDS_STATE = UDS_START_DEFAULT_SESSION_STATE
        elif WriteMarkerCheck == False and ErrorCounter < MAX_ERRORS_TIMES :  
          print ("Error at State: "+str(UDS_STATE))
          ErrorCounter +=1
        else:
          print ("Reached Max Times of errors!!!")
          break
      elif UDS_STATE == UDS_START_DEFAULT_SESSION_STATE:
        InitializeDefaultSession = StartSession(DEFAULT_SESSION_ID) 
        if InitializeDefaultSession == True :
          UDS_STATE = UDS_ECU_RESET_STATE
          ErrorCounter = 1
        elif InitializeDefaultSession == False and ErrorCounter < MAX_ERRORS_TIMES :  
          print ("Error at State: "+str(UDS_STATE))
          ErrorCounter +=1
        else:
          print ("Reached Max Times of errors!!!")
          break
      elif UDS_STATE == UDS_ECU_RESET_STATE:
        ResetCheck = ResetECU (SOFT_RESET_ID)
        if ResetCheck == True :
          ErrorCounter = 1
          print ("Flashing has been done successfully")
          break
        elif ResetCheck == False and ErrorCounter < MAX_ERRORS_TIMES :  
          print ("Error at State: "+str(UDS_STATE))
          ErrorCounter +=1
        else:
          print ("Reached Max Times of errors!!!")
          break 
  else: 
    print ("uncompatible .elf file")
  
  

if __name__ == '__main__':
  main()