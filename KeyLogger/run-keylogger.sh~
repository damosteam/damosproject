#!/bin/bash

# Author: Daniel Puckowski
# Purpose: Automate the setup and execution of the custom DamOS Linux keylogging program.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

if [ ! $# == 1 ]; then
    echo -e "${txtred}Usage: ./run-keylogger.sh <Root Password>" ; tput sgr0
    exit 1
fi

echo -e "${txtred}Starting custom DamOS keylogging program now..." ; tput sgr0

read -p 'Use default settings? ' -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    # sudo -S $2
    su -S $2
    ./logger /dev/input/event2 logger_output.txt &
fi

echo

#read -p 'Print input device list? ' -n 1 -r
#if [[ $REPLY =~ ^[Yy]$ ]]
#then
#    echo
#    more /proc/bus/input/devices
#fi

#echo

echo -e "${txtred}Done." ; tput sgr0

exit 0
