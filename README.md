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

## Enable UART in RaspberryPi 



You can check the references for further help on how they are created.

## References

**UART configurations of RaspberryPi**
(https://www.electronicwings.com/raspberry-pi/raspberry-pi-uart-communication-using-python-and-c)
