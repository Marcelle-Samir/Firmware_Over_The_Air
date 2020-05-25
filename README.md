# Firmware_Over_The_Air_RaspberryPi

This project is a firmware over the air for automotive industry using RaspberryPi 3B+ and STm32 Mc 

## Tutorial for RaspberryPi

Till now we are using the full image of raspbian-buster

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
>PasswordAuthentication yes

To connect with RaspberryPi:
>ssh-keygen -f "/home/$USER/.ssh/known_hosts" -R "192.168.5.30"
>ssh pi@192.168.5.30

## Configure UART on RaspberryPi 
>sudo raspi-config

append "enable_uart=1" to config.txt

In PC terminal
- to make sure it is connected and given a port name by the kernel use:
>dmesg  -wH  (ex.  /dev/ttyUSB0 )
- to change its permissions so you can read and write to it:
>sudo chmod o+rw /dev/ttyUSB0
- to test read:
>sudo cat /dev/ttyUSB0
- to test write:
>sudo echo "hello" > /dev/ttyUSB0

in RaspberryPi terminal
- To check if mini UART (ttyS0) or PL011 UART (ttyAMA0) is mapped to UART pins, enter following commands:
>ls -l /dev
- to test read from (ttyS0):
>cat /dev/ttyS0
- to test write to (ttyS0):
>echo "hello" > /dev/ttyS0


You can check the references for further help on how they are created.

## References

**UART configurations of RaspberryPi**
(https://www.electronicwings.com/raspberry-pi/raspberry-pi-uart-communication-using-python-and-c)
