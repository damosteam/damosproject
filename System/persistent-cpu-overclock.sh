#!/bin/bash
 
# Author: Daniel Puckowski
# Date (last edit): 04/04/2014
# Purpose: Overclock the Exynos 4412 Prime SoC in the oDroid U3 from 1.7 GHz to
# 1.92 GHz at boot.
# Script version: 0.0.0.4

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Enabling persistent CPU overclock now..." ; tput sgr0

if [ ! -f /etc/rc.local ]; then
	touch /etc/rc.local
	echo "Created file /etc/rc.local"
fi

## Uncomment the next line to create a backup of the /etc/rc.local file when this script is run.
# cp /etc/rc.local /etc/rc.local.bak

stringCheck=$(grep -R "echo 1920000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq" /etc/rc.local) 

if [ ! -n "$stringCheck" ]; then
	echo "Overclock statement already exists in /etc/rc.local."
	echo "Done."
	exit 0
fi

echo -e "Script will remove \"exit 0\" statement before appending to file /etc/rc.local..."
 
read -p "Would you like to more /etc/rc.local to ensure the last line of file is exit 0? " -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    more /etc/rc.local 
    echo

    read -p 'Abort script now? ' -n 1 -r
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
	echo
    	echo "Done."
	exit 0 
    fi
fi

echo 
	
if [ -f /etc/rc.local ]; then
	sed -i '$ d' /etc/rc.local
fi

echo "Appending overclock statement to file /etc/rc.local..."

echo "echo 1920000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq" >> /etc/rc.local 
echo "exit 0" >> /etc/rc.local 

echo -e "${txtred}Done." ; tput sgr0

exit 0
