#!/bin/bash

# Author: Daniel Puckowski
# Purpose: Add the custom DamOS programs and utilities to PATH in the ~/.bashrc file.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Adding the custom DamOS programs and utilites to PATH in the ~/.bashrc file now..." ; tput sgr0

# echo -e "Note: Script assumes program executables are stored in their respective folders in the \"/damos-programs\" directory."

# echo

echo -e "\n" >> ~/.bashrc

echo "export PATH=$PATH:/damos-programs/Cipher/:/damos-programs/Client/:/damos-programs/Server/:/damos-programs/KeystrokeLogging/LinuxLogging/KeyLogger/:/damos-programs/KeystrokeLogging/LinuxLogging/LogProcessor/:/damos-programs/MenuReader/" >> ~/.bashrc

echo

echo 'Note: You may need to close the current terminal window and open a new one for the changes to take effect.'

echo

echo -e "${txtred}Added to PATH." ; tput sgr0

exit 0
