import sys
import os
from serial import serialwin32
from elftools.elf.elffile import ELFFile , Segment
from elftools.elf.structs import ELFStructs

#Container({'p_type': 'PT_LOAD', 'p_offset': 65536, 'p_vaddr': 134217728,
# 'p_paddr': 134217728, 'p_filesz': 4891, 'p_memsz': 4891, 'p_flags': 7, 'p_align': 65536})
####################Constants ###########################################################################

START_ADDRESS=0x08000000              #start address of flash (0x08000000)  
FINAL_ADDRESS=0x08010000              #Flash Size = 64K

BL_SIZE=0x2000

START_AVAILABLE_ADDRESS = START_ADDRESS + BL_SIZE #start address of flash (0x08000000) + + BL size shift (0x2000)

#define MAX_DATA_SIZE                 1024
MAX_DATA_SIZE=1024
#define RECEIVED_OK                   1
#define RECEIVED_NOK                  2
RECEIVED_OK = 1
RECEIVED_NOK = 2
#define COMMAND_FLASH_NEW_APP         0xAB
#define COMMAND_FLASH_WRITE_SECTOR    0xBC
#define COMMAND_RESPOND_FRAME         0xCD
#define COMMAND_END_FLASH             0xDE
COMMAND_FLASH_NEW_APP     = 0xAB
COMMAND_FLASH_WRITE_SECTOR= 0xBC
COMMAND_RESPOND_FRAME     = 0xCD
COMMAND_END_FLASH         = 0xDE
#define FLASH_NEW_APP_KEY             0xAA
#define START_OF_FRAME_KEY            0xBB
#define END_FLASH_KEY                 0xCC
FLASH_NEW_APP_KEY =0xAA
START_OF_FRAME_KEY=0xBB
END_FLASH_KEY     =0xCC
#define FLASH_NEW_APP_SIZE            0X13
#define FLASH_WRITE_SECTOR_SIZE       0X0B+(4*MAX_DATA_SIZE)
#define RESPOND_FRAME_SIZE            0x04
#define END_FLASH_SIZE                0x04
FLASH_NEW_APP_SIZE     =0X10
FLASH_WRITE_SECTOR_SIZE=0X0C+(MAX_DATA_SIZE)
RESPOND_FRAME_SIZE     =0x04
END_FLASH_SIZE         =0x04
DUMMY_BYTE=0
##########################################################################################################
port = "COM29"
ser = serialwin32.Serial(port,9600)
file=open(sys.argv[1],"rb")
elf_Handler =ELFFile(file)
Header=elf_Handler.header   #elf file header
Magic=Header.e_ident ['EI_MAG'] #magic number
EntryPoint=Header.e_entry #entry point
program_header_number =elf_Handler.num_segments() #number of segments in the elf file
elf_Class=elf_Handler.elfclass #elf file class
segments_header=[]
segments=[]
Req_num=0
#Verification function
def verify_Elf_File():
    if Magic[0] !=127 or  Magic[1] !=69 or  Magic[2] !=76 or  Magic[3] !=70 or  elf_Class !=32 :
      return False
    else: 
      return True
      
def Send_Flash_New_App_Cmd ():
  FILE_SIZE=0
  Flash_New_App_Cmd_Frame=[]
  Flash_New_App_Cmd_Frame.insert(len(Flash_New_App_Cmd_Frame),START_OF_FRAME_KEY.to_bytes(1, 'little'))
  Flash_New_App_Cmd_Frame.insert(len(Flash_New_App_Cmd_Frame),Req_num.to_bytes(1, 'little')                    )
  Flash_New_App_Cmd_Frame.insert(len(Flash_New_App_Cmd_Frame),COMMAND_FLASH_NEW_APP.to_bytes(1, 'little'))
  Flash_New_App_Cmd_Frame.insert(len(Flash_New_App_Cmd_Frame),FLASH_NEW_APP_KEY.to_bytes(1, 'little')    )
  Flash_New_App_Cmd_Frame.insert(len(Flash_New_App_Cmd_Frame),START_AVAILABLE_ADDRESS.to_bytes(4, 'little')        )
  for seg_header in segments_header:
    if seg_header['p_paddr'] >= START_ADDRESS and seg_header['p_paddr'] < FINAL_ADDRESS and seg_header['p_flags'] != 4 :
      FILE_SIZE+=seg_header['p_memsz']
  FILE_SIZE-=BL_SIZE
  Flash_New_App_Cmd_Frame.insert(len(Flash_New_App_Cmd_Frame),FILE_SIZE.to_bytes(4, 'little') )
  Flash_New_App_Cmd_Frame.insert(len(Flash_New_App_Cmd_Frame),EntryPoint.to_bytes(4, 'little'))
  for elements in Flash_New_App_Cmd_Frame:
    ser.write(elements)
  print ("Flash new app frame sent ...")

def Receive_Respond():
  Received_frame=[]
  Received_frame = ser.read(RESPOND_FRAME_SIZE)
  if Received_frame[0] == START_OF_FRAME_KEY and Received_frame[2] == COMMAND_RESPOND_FRAME:
    print ("Respond frame checked")
    if Received_frame[3] == RECEIVED_OK:
      return True
    else:
      print ("Received NOK")
      return False
  else:
    return False
  
def Send_data():
    First_Segment_check=0
    Flash_Write_Sector_frame=[]
    Current_Address = START_AVAILABLE_ADDRESS 
    Current_size=0
    current_segment_index=0
    Req_num=0
    current_segment_data_pos=BL_SIZE
    remaining_size=0
    current_segment_data = 0
    while current_segment_index <program_header_number:
        if segments_header[current_segment_index]['p_paddr'] >= START_ADDRESS and segments_header[current_segment_index]['p_paddr'] < FINAL_ADDRESS and segments_header[current_segment_index]['p_flags'] != 4 :
          if First_Segment_check == 0:
            remaining_size=segments_header[current_segment_index]['p_memsz']-BL_SIZE
            current_segment_data = segments[current_segment_index].data()
            First_Segment_check =1
          Flash_Write_Sector_frame.insert(len(Flash_Write_Sector_frame),START_OF_FRAME_KEY.to_bytes(1, 'little'))
          Flash_Write_Sector_frame.insert(len(Flash_Write_Sector_frame),Req_num.to_bytes(1, 'little'))
          Flash_Write_Sector_frame.insert(len(Flash_Write_Sector_frame),COMMAND_FLASH_WRITE_SECTOR.to_bytes(1, 'little'))
          Flash_Write_Sector_frame.insert(len(Flash_Write_Sector_frame),DUMMY_BYTE.to_bytes(1, 'little'))
          Flash_Write_Sector_frame.insert(len(Flash_Write_Sector_frame),Current_Address.to_bytes(4, 'little'))
          Current_size = min (remaining_size,MAX_DATA_SIZE)
          Flash_Write_Sector_frame.insert(len(Flash_Write_Sector_frame),Current_size.to_bytes(4, 'little'))
          print ("size = ",str(Current_size))
          print ("Pos = ",str(current_segment_data_pos))
          for elements in range (current_segment_data_pos,current_segment_data_pos+Current_size):
            Flash_Write_Sector_frame.insert(len(Flash_Write_Sector_frame),current_segment_data[elements].to_bytes(1, 'little'))
          if (Current_size <MAX_DATA_SIZE ):
            for remained in range (0,MAX_DATA_SIZE-Current_size):
              Flash_Write_Sector_frame.insert(len(Flash_Write_Sector_frame),DUMMY_BYTE.to_bytes(1, 'little'))
          for elements in Flash_Write_Sector_frame:
            ser.write(elements)
          print ("Sending ...")
          Check_Data_Response = Receive_Respond()
          if Check_Data_Response == True:
            remaining_size-=Current_size
            Req_num+=1
            Flash_Write_Sector_frame=[]
            if remaining_size==0: #new segment
              print ("Finished Segment #",str(current_segment_index))
              current_segment_index+=1
              if current_segment_index == program_header_number:
                print ("Data send is done")
                return True
              print ("Start Flashing Segment #",str(current_segment_index))
              remaining_size = segments_header[current_segment_index]['p_memsz']
              current_segment_data_pos=0
              Current_Address = segments_header[current_segment_index]['p_paddr']
              current_segment_data = segments[current_segment_index].data()
            else: #still in the same segment
              Current_Address+=Current_size
              current_segment_data_pos+=Current_size
          else:
            print ("error in frame Respond")
            return False
        else: 
          print ("This Segment is not located at the Flash memory or it is not writable")
          current_segment_index+=1
    return True
  
def Send_End_frame():
  Flash_ending_frame=[]
  Flash_ending_frame.insert(len(Flash_ending_frame),START_OF_FRAME_KEY.to_bytes(1, 'little'))
  Flash_ending_frame.insert(len(Flash_ending_frame),Req_num.to_bytes(1, 'little'))
  Flash_ending_frame.insert(len(Flash_ending_frame),COMMAND_END_FLASH.to_bytes(1, 'little'))
  Flash_ending_frame.insert(len(Flash_ending_frame),END_FLASH_KEY.to_bytes(1, 'little'))
  for elements in Flash_ending_frame:
    ser.write(elements)
  print ("Sending End flashing frame ......")
  return Receive_Respond()

  
def main ():
  CheckFile=verify_Elf_File()
  if CheckFile == True :
    print ("Elf file verified")
    for i in range(0,program_header_number):
        if elf_Handler._get_segment_header(i)['p_type']:
          segments_header.append(elf_Handler._get_segment_header(i))#elf file segments header
          segments.append(elf_Handler. get_segment(i)) #elf file segments
    Send_Flash_New_App_Cmd()
    Flash_New_App_Response=Receive_Respond()
    if Flash_New_App_Response == True :
      print ("Sending Data ...")
      Check_data_send=Send_data()
      if Check_data_send == True:
          print ("Data has been flashed successsfully, Ending communication with the microController")
          check_end_flashing = Send_End_frame()
          if check_end_flashing == True:
            print ("Flashing has been done")
          else:
            print ("Error in ending the flashing process")
      else:
          print("error in sending data")
    else:
      print ("request for flash new app has been failed")
  else:
    print ("Invalid Elf type")


if __name__ == '__main__':
  main()