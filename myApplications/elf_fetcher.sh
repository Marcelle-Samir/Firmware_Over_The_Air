#!/bin/bash

while true; do

echo "hello"

gsutil -m cp -R gs://fota_automotive/Request.txt /home/pi/
request=`grep -c "Firmware" /home/pi/Request.txt`
ATMEGA3_request=`grep -c "ATMEGA3" /home/pi/Request.txt`
STMF10_request=`grep -c "STMF10" /home/pi/Request.txt`
if [[ $request -ne 0 ]]
then
	if [[ ATMEGA3_request -ne 0 ]]
	then
#		python3 /myApplications/elfParser.py /myApplications/Dummy.elf
		gsutil -m cp -R gs://fota_automotive/Dummy.elf /home/pi/
		echo "ATMEGA3 elf parsing" >> /home/pi/debug.txt
	        echo "done" > /home/pi/Request.txt
	        gsutil -m cp -R /home/pi/Request.txt gs://fota_automotive/

	elif [[ STMF10_request -ne 0 ]]
	then
#		python3 /myApplications/elfParser.py /myApplications/Dummy.elf
		gsutil -m cp -R gs://fota_automotive/Dummy.elf /home/pi/
		echo "STMF10 elf parsing" >> /home/pi/debug.txt
	        echo "done" > /home/pi/Request.txt
	        gsutil -m cp -R /home/pi/Request.txt gs://fota_automotive/

	else
		echo "no supported MC" > /home/pi/issues.txt
		gsutil -m cp -R /home/pi/issues.txt gs://fota_automotive/
	fi
	
else
	sleep 10
fi

sleep 5

done

#New Firmware ATMEGA32 Can boosters schematic.png
