# Firmware_Over_The_Air_RaspberryPi

This project is a firmware over the air for automotive industry using RaspberryPi 3B+ and STm32 Mc 

Till now we are using the full image of raspbian-buster

## The image for RaspberryPi
- you can download the Raspian Image from:
https://www.raspberrypi.org/downloads/raspbian/

- First unzip the the downloaded file using unzip command.
>unzip 2019-09-26-raspbian-buster.zip
- Then insert your SD card into your laptop, To discover the SD card
>lsblk -p   (this name should be /dev/mmcblk0 or /dev/sdX)
- Now time to Copy the unzipped image onto the mounted device using command dd.
>dd bs=4M if=raspbian.img of=/dev/sdX status=progress conv=fsync


## Enable Ethernet connection

To Configure a static IP for RPI3, Modify the file "/etc/network/interfaces" on your Raspbian image (or any Debian image):

Disable the DHCP client for eth0 interface by commenting this line using "#"
>iface eth0 inet dhcp    ====>   #iface eth0 inet dhcp

Add these lines after it to configure eth0 interface to use static IP:

>auto eth0\
>iface eth0 inet static\
>wait-delay 15\
>hostname $(hostname)\
>address 192.168.5.30\
>netmask 255.255.255.0

To enable ssh create an empty file named "ssh" in boot directory
>touch ssh

To enable password authentication, uncomment
>sudo nano /etc/ssh/sshd_config\
>#PasswordAuthentication yes   ====>   PasswordAuthentication yes

To connect with RaspberryPi:
>ssh-keygen -f "/home/$USER/.ssh/known_hosts" -R "192.168.5.30"
>ssh pi@192.168.5.30 (defualt user: pi, default password: raspberry)

## Configure UART on RaspberryPi 
>sudo raspi-config

- select -> interfacing options

<img src="images/interfacing_options.jpeg" width="500">

- then, select seroal option to enable UART

<img src="images/serial.jpeg" width="500">

- then select No to login shell to be accessible over serial

<img src="images/serial__access.jpeg" width="500">

- then select Yes to enable hardware serial port

<img src="images/uart_enable.jpeg" width="500">

- Now our UART is enabled for serial communication on Tx and Rx of RaspberryPi

<img src="images/uart_done.jpeg" width="500">


- add "enable_uart=1" at the end of /boot/config.txt

In PC terminal
- to make sure it is connected and given a port name by the kernel use:
>dmesg  -wH  (ex.  /dev/ttyUSB0 )
- to change its permissions so you can read and write to it:
>sudo chmod o+rw /dev/ttyUSB0
- to test read from (ex. ttyUSB0):
>sudo cat /dev/ttyUSB0
- to test writing to (ex. ttyUSB0) :
>sudo echo "hello" > /dev/ttyUSB0

- connect your TTL(Tx) ==> RaspberryPi(Rx) and then TTL(Rx) ==>  RaspberryPi(Tx), pins (GPIO14 and GPIO15)
and cobbect TTL(GND) to RaspberryPi(GND)

<img src="images/uart_pins.jpeg" width="300">


In RaspberryPi terminal
- To check if mini UART (ttyS0) or PL011 UART (ttyAMA0) is mapped to UART pins, enter following commands:
>ls -l /dev
- to test reading from (ttyS0):
>cat /dev/ttyS0
- to test writing to (ttyS0):
>echo "hello" > /dev/ttyS0


You can check the references for further help on how they are created.

## References

**Connecting to RPI3 - SSH Over Wired**
- https://www.raspberrypi.org/documentation/remote-access/ssh/README.md
- https://www.raspberrypi.org/documentation/configuration/security.md
- https://www.raspberrypi.org/documentation/remote-access/ip-address.md
- https://elinux.org/RPi_Serial_Connection#Console_serial_parameters
- https://pinout.xyz/pinout/uart#

**UART configurations of RaspberryPi**
- https://www.electronicwings.com/raspberry-pi/raspberry-pi-uart-communication-using-python-and-c
