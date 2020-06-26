import time
from serial import serialwin32 
def main():     #Test Code                                     
  seri = Transport_Init("COM29",115200,5)
  list = []          
  list2=[]
  for i in range (0,255):
    list.insert(len(list),i.to_bytes(1,'little'))
    
  for i in range (0,255):
    list.insert(len(list),i.to_bytes(1,'little'))

  for i in range (0,255):
    list.insert(len(list),i.to_bytes(1,'little'))  

  for i in range (0,255):
    list.insert(len(list),i.to_bytes(1,'little'))

  for i in range (0,15):
    list.insert(len(list),i.to_bytes(1,'little'))
  print (len(list))
  Transport_TX (seri,list,2)
  Transport_TX (seri,list,8)
#  Transport_RX (seri,1032)
#  print (list2)
#  print (len (list2))
#  Transport_RX (seri,1032)
#  print (list2)
#  print (len (list2))
  
  
def Transport_Init (port,BaudRate,time):
  s=0
  s = serialwin32.Serial(port,BaudRate,timeout=time)
  return s
  
def Transport_TX (ser,a,size):
  padd = 0xff
  Tx_buffer = []
  if size <=7: #Single frame case
    pci=size
    Tx_buffer.insert(len(Tx_buffer),pci.to_bytes(1,'little'))
    for i in range (0,size):
      Tx_buffer.insert(len(Tx_buffer),a[i])
    for i in range (0,(7-size)):
      Tx_buffer.insert(len(Tx_buffer),padd.to_bytes(1,'little'))
    #print (Tx_buffer)
    for i in Tx_buffer:
      ser.write (i)
  else: #First - Consecutive case
    Tx_index=0      
    #constructing first frame 
    pci=0x10
    if (size < 0xff):
      Tx_buffer.insert(len(Tx_buffer),pci.to_bytes(1,'little'))
      Tx_buffer.insert(len(Tx_buffer),size.to_bytes(1,'little'))
    else:
      pci |= (size >> 8)
      Tx_buffer.insert(len(Tx_buffer),pci.to_bytes(1,'little'))
      pci=size&0x0ff
      Tx_buffer.insert(len(Tx_buffer),pci.to_bytes(1,'little'))
    for i in range (0,6):
      Tx_buffer.insert(len(Tx_buffer),a[i])
    #print (Tx_buffer)
    for i in Tx_buffer:
      ser.write (i) 
    Tx_buffer=[]
    Tx_index+=6
    #consecutive frames
    seq_Num=1
    while Tx_index <(size-1):
        pci=0x20 | seq_Num
        Tx_buffer.insert(len(Tx_buffer),pci.to_bytes(1,'little'))
        if (size - Tx_index) >=7: # consecutive frame will occupy the entire 7-bytes
          for i in range (Tx_index,Tx_index+7):
            Tx_buffer.insert(len(Tx_buffer),a[i])
          Tx_index+=7
        else:  #remaining bytes is less than 7-bytes -last consecutive frame case-
          for i in range (Tx_index,size):
            Tx_buffer.insert(len(Tx_buffer),a[i])
          for i in range (0,7-(size - Tx_index)):
            Tx_buffer.insert(len(Tx_buffer),padd.to_bytes(1,'little'))
          Tx_index =size
        seq_Num +=1
        if seq_Num == 0x10:
          seq_Num = 0
        #print (Tx_buffer)
        for i in Tx_buffer:
          ser.write (i)
        Tx_buffer=[]
    
def Transport_RX (ser,size):
  Rx_buffer=[]
  Received_data=[]
  if size <=7: #single frame size
    Rx_buffer = ser.read (8)
    if len(Rx_buffer) == 8:
      for i in range (1,size+1):
        Received_data.insert(len(Received_data),Rx_buffer[i])
      Rx_buffer = []
    else:
      print ("TimeOut!!")
  else: #first and consecutive frames
    prev_seq=0
    DataSize=0
    Rx_buffer = ser.read (8)
    if len(Rx_buffer) == 8:
      if Rx_buffer[0] & 0xf0 == 0x10 :
        DataSize = ((Rx_buffer[0] & 0x0F)<<8) | Rx_buffer[1]
        for i in range(0,6):
          Received_data.insert (len(Received_data),Rx_buffer[i+2])
        DataSize -=6
        while DataSize !=0 :
          Rx_buffer = ser.read (8)
          if (Rx_buffer[0] & 0xf0 == 0x20) and ((Rx_buffer[0] & 0x0f ==prev_seq+1) or (Rx_buffer[0] & 0x0f == 0 and prev_seq ==0x0f)) :
            if DataSize >=7:
              for i in range (0,7):
                Received_data.insert (len(Received_data),Rx_buffer[i+1])
              DataSize-=7
              prev_seq = Rx_buffer[0] & 0x0f
            else: 
              for i in range(0,DataSize):
                Received_data.insert (len(Received_data),Rx_buffer[i+1])
                DataSize = 0
      else: 
        print ("error in receiving the first frame")
    else:
      print ("TimeOut Error")    
  return Received_data

if __name__ == '__main__':
  main()


