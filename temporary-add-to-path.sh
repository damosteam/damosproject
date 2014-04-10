#!/bin/bash

# Author: Daniel Puckowski
# Purpose: Temporarily add the custom DamOS programs and utilities to PATH.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Temporarily adding the custom DamOS programs and utilites to PATH now..." ; tput sgr0

echo

echo -e "${txtred}This script needs to be run as \"source\" -- source ./script.sh" ; tput sgr0

echo

# echo 'Note: Script assumes program executables are stored in their respective folders in the /damos-programs directory.'

# echo

export PATH=$PATH:/damos-programs/Cipher/:/damos-programs/Client/:/damos-programs/Server/:/damos-programs/KeystrokeLogging/LinuxLogging/KeyLogger/:/damos-programs/KeystrokeLogging/LinuxLogging/LogProcessor/:/damos-programs/MenuReader/

echo -e "${txtred}Added to path." ; tput sgr0

exit 0
