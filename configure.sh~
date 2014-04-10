#!/bin/bash

# Author: Daniel Puckowski
# Purpose: Configure the custom DamOS programs and utilites for use on system.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

startTime=$(date +"%T")

echo -e "${txtred}Configuring the custom DamOS programs and utilities now..." ; tput sgr0

echo 

echo -e "${txtred}Please make sure the folder containing this script and the rest of the custom DamOS programs, utilities, and scripts is named \"damos-programs\" and is located at /damos-programs before proceeding..." ; tput sgr0

echo

read -p 'Stop now to make appropriate changes? ' -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    exit 0
fi

echo

echo 'This script will: install all of the required dependencies, compile the DamOS programs and utilites, add man pages for the DamOS software, and add the programs and utilities to the PATH environment variable for all users for quick access.'

echo

./install-dependencies.sh

./initial-build.sh

cd ManPages

./add-manpages.sh

cd ..

./add-to-path.sh

echo

echo -e "${txtred}Done configuring the custom DamOS programs and utilities." ; tput sgr0

echo "Time started:  ${startTime}."
echo "Time finished: $(date +"%T")."

exit 0
