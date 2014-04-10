#!/bin/bash

# Author: Daniel Puckowski
# Purpose: Clean all of the build directories for all of the custom DamOS programs and utilities.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Running \"make clean\" in all build directories now..." ; tput sgr0

echo

cd /damos-programs

cd ./Cipher
make clean
cd ..

cd ./Server
make clean
cd ..

cd ./Client
make clean
cd ..

cd ./MenuReader
make clean
cd ..

cd ./KeystrokeLogging/LinuxLogging/KeyLogger
make clean
cd .. ; cd .. ; cd ..

cd ./KeystrokeLogging/LinuxLogging/LogProcessor
make clean
cd .. ; cd .. ; cd ..

echo

echo -e "${txtred}Done cleaning all build directories." ; tput sgr0

exit 0

