#!/bin/bash

my_car_model=verna_2018
my_car_id=verna_2018_1

ST_INT_pin=18
AVR_INT_pin=17 


echo "$ST_INT_pin" >> /sys/class/gpio/export
echo "out" >> /sys/class/gpio/gpio"$ST_INT_pin"/direction
echo "0" > /sys/class/gpio/gpio"$ST_INT_pin"/value


echo "$AVR_INT_pin" >> /sys/class/gpio/export
echo "out" >> /sys/class/gpio/gpio"$AVR_INT_pin"/direction
echo "0" > /sys/class/gpio/gpio"$AVR_INT_pin"/value

flag=0
snooze_count=0
else_count=0

gsutil -m cp -R gs://fotaproject_bucket/cars_ids.xml /home/pi/
xmlstarlet ed -u '/cars/verna_2018_1' -v "available" </home/pi/cars_ids.xml>/home/pi/new_status.xml
mv /home/pi/new_status.xml /home/pi/cars_ids.xml
gsutil -m cp -R /home/pi/cars_ids.xml gs://fotaproject_bucket/

while true; do

echo "0" > /sys/class/gpio/gpio"$ST_INT_pin"/value

gsutil -m cp -R gs://fotaproject_bucket/Request.xml /home/pi/

echo "first request downloaded" >> /home/pi/debug.txt

status_value=`xmlstarlet sel -T -t -m '/data/Status' -v . -n /home/pi/Request.xml`
controller_name=`xmlstarlet sel -T -t -m '/data/CarsTarget' -v . -n /home/pi/Request.xml`
cars_model=`xmlstarlet sel -T -t -m '/data/CarsModel' -v . -n /home/pi/Request.xml`
cars_id=`xmlstarlet sel -T -t -m '/data/CarsID' -v . -n /home/pi/Request.xml`

echo "done parsing xml" >> /home/pi/debug.txt

if [[ $status_value = "Released" ]]
then
	echo "i'm status in" >> /home/pi/debug.txt
	if [[ $cars_model = $my_car_model ]] 
	then
		echo "i'm car model in" >> /home/pi/debug.txt

		if [[ $cars_id = $my_car_id ]]
		then
			echo "i'm car id in" >> /home/pi/debug.txt
			if [[ $controller_name = "STM32F103-1" ]]
			then
				echo "in first if" >> /home/pi/debug.txt
				elf_name=`xmlstarlet sel -T -t -m '/data/FileName' -v . -n /home/pi/Request.xml`
				gsutil -m cp -R gs://fotaproject_bucket/"$elf_name" /home/pi/
				xmlstarlet ed -u '/data/Status' -v "Downloaded" </home/pi/Request.xml>/home/pi/new.xml
				mv /home/pi/new.xml /home/pi/Request.xml
				gsutil -m cp -R /home/pi/Request.xml gs://fotaproject_bucket/ 
		
				while [[ $flag -ne 1 ]]
				do
					echo `yad --title="3faret El Embedded FOTA project" --list --width=500 --height=200 --column "New Firmware for $controller_name is available. Select action" 'Flash now' 'Snooze 5 min' --no-buttons --timeout=60` > /home/pi/action.txt
					action_result=`sed -n '1{p;q}' /home/pi/action.txt`
		
					if [[ $action_result = "Flash now|" ]]
					then
						echo "in sec if" >> /home/pi/debug.txt
						echo "1" > /sys/class/gpio/gpio"$ST_INT_pin"/value
						sleep 2
						echo "0" > /sys/class/gpio/gpio"$ST_INT_pin"/value
						sleep 0.5
						python3 /home/pi/myApplications/elfParser.py /home/pi/"$elf_name"
						echo "STMF10 elf parsing" >> /home/pi/debug.txt
						rm /home/pi/"$elf_name"
						xmlstarlet ed -u '/data/Status' -v "Flashed" </home/pi/Request.xml>/home/pi/new.xml
						mv /home/pi/new.xml /home/pi/Request.xml
						gsutil -m cp -R /home/pi/Request.xml gs://fotaproject_bucket/ 	
						yad --title="3faret El Embedded FOTA project" --text="Flashing for $controller_name is done" --width=350 --height=10 --timeout=5  --dnd
						snooze_count=0		
						flag=1

					elif [[ $action_result = "Snooze 5 min|" ]]
					then
						echo "action elif" >> debug.txt
						snooze_count=$(($snooze_count+1))
						if [[ $snooze_count -eq 3 ]]
						then
							echo "action elif if" >> debug.txt	
							xmlstarlet ed -u '/data/Status' -v "Ignored" </home/pi/Request.xml>/home/pi/new.xml
							mv /home/pi/new.xml /home/pi/Request.xml
							gsutil -m cp -R /home/pi/Request.xml gs://fotaproject_bucket/ 	
							flag=1
						else
							echo "action elif else" >> debug.txt
							sleep 60
						fi
					else
						else_count=$(($else_count+1))
						if [[ $else_count -eq 3 ]]
						then
							echo "action elif if" >> debug.txt	
							xmlstarlet ed -u '/data/Status' -v "Ignored" </home/pi/Request.xml>/home/pi/new.xml
							mv /home/pi/new.xml /home/pi/Request.xml
							gsutil -m cp -R /home/pi/Request.xml gs://fotaproject_bucket/ 	
							flag=1
						else
							sleep 60
							echo "action else" >> debug.txt
						fi
 					fi
				done
			fi
		fi
	fi	
else
	sleep 1
fi

sleep 1
flag=0
done
