#!/bin/bash

ip a
iwconfig

nmcli dev wifi list
sudo iw wlan0 scan | grep SSID

read -p "Enter the SSID: " ssid # Prompts the user for the ESSID/BSSID
read -p "Enter the password: " password # Prompts the user for the password

output=$(nmcli device wifi connect "$ssid" password "$password" iface wlan0 --timeout 10) # Tries to connect

ping
if [[ $? -eq 0 ]]; then
	echo "Connected."
	exit 0
else
	echo "Error. $output"
	exit 1
fi

