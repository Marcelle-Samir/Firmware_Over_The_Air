#!/bin/bash

ST_SW_pin=27
ST_LED_pin=17
ST_INT_pin=22


echo "$ST_SW_pin" >> /sys/class/gpio/export
echo "in" >> /sys/class/gpio/gpio"$ST_SW_pin"/direction

echo "$ST_LED_pin" >> /sys/class/gpio/export
echo "out" >> /sys/class/gpio/gpio"$ST_LED_pin"/direction

echo "$ST_INT_pin" >> /sys/class/gpio/export
echo "out" >> /sys/class/gpio/gpio"$ST_INT_pin"/direction

echo "0" > /sys/class/gpio/gpio"$ST_INT_pin"/value
echo "0" > /sys/class/gpio/gpio"$ST_LED_pin"/value

flag=0

while true; do

gsutil -m cp -R gs://fota_automotive/Request.txt /home/pi/
request=`grep -c "Firmware" /home/pi/Request.txt`
ATMEGA3_request=`grep -c "ATMEGA32" /home/pi/Request.txt`
STMF10_request=`grep -c "STM32F103" /home/pi/Request.txt`

if [[ $request -ne 0 ]]
then
	if [[ $STMF10_request -ne 0 ]]
	then
		echo "in first if" >> /home/pi/debug.txt
		elf_name=`grep -o -E '\w+.elf' /home/pi/Request.txt` 
		gsutil -m cp -R gs://fota_automotive/"$elf_name" /home/pi/
		echo "1" > /sys/class/gpio/gpio"$ST_LED_pin"/value
		while [[ $flag -ne 1 ]]
		do
		if [[ $(cat /sys/class/gpio/gpio"$ST_SW_pin"/value) -eq 1 ]]
		then
			echo "in sec if" >> /home/pi/debug.txt
			echo "1" > /sys/class/gpio/gpio"$ST_INT_pin"/value
			sleep 3
			echo "0" > /sys/class/gpio/gpio"$ST_INT_pin"/value
			python3 /home/pi/myApplications/elfParser.py /home/pi/"$elf_name"
			echo "STMF10 elf parsing" >> /home/pi/debug.txt
	        	echo "done" > /home/pi/Request.txt
	       		gsutil -m cp -R /home/pi/Request.txt gs://fota_automotive/
			rm /home/pi/"$elf_name"
			echo "0" > /sys/class/gpio/gpio"$ST_LED_pin"/value
			flag=1
		fi
		done
	elif [[ $ATMEGA3_request -ne 0 ]]
	then
		gsutil -m cp -R gs://fota_automotive/"$elf_name" /home/pi/
		python3 /home/pi/myApplications/elfParser.py /home/pi/Dummy.elf
		echo "ATMEGA3 elf parsing" >> /home/pi/debug.txt
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
flag=0
done

#New Firmware ATMEGA32 Can boosters schematic.png
