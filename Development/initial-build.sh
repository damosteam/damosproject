#!/bin/bash

# Author: Daniel Puckowski
# Purpose: This script will automatically build the custom DamOS programs and utilities.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

OS_NAME='DamOS'

echo -e "${txtred}Building custom utilities/programs for ${OS_NAME} now..." ; tput sgr0

echo

startTime=$(date +"%T")

echo 'Making sure proper dependencies are installed...'

sudo apt-get install g++ 

## G++ package for ARM without hard float
# sudo apt-get install gcc-arm-linux-gnueabi

## G++ package for ARM with hard float
# sudo apt-get install gcc-arm-linux-gnueabihf

cd /damos-programs

echo 'Extracting source code from archive...'
./extract-archive.sh
echo 'Done extracting source code.'

echo 'Building Cipher program now...'
cd ./Cipher
echo $(pwd)
make
echo 'Done building Cipher program.'
cd ..

echo 'Building Server program now...'
cd ./Server
echo $(pwd)
make
echo 'Done building Server program.'
cd ..

echo 'Building Client program now...'
cd ./Client
echo $(pwd)
make
echo 'Done building Client program.'
cd ..

echo 'Building Key Logger program now...'
cd ./KeystrokeLogging/LinuxLogging/KeyLogger
echo $(pwd)
make
echo 'Done building Key Logger program.'
cd .. ; cd .. ; cd ..

echo 'Building Log Processor utility now...'
cd ./KeystrokeLogging/LinuxLogging/LogProcessor
echo $(pwd)
make
echo 'Done building Log Processor utility.'
cd .. ; cd .. ; cd ..

echo 'Building Menu Reader utility now...'
cd ./MenuReader
echo $(pwd)
make
echo 'Done building Menu Reader utility.'
cd ..

echo -e "${txtred}Done building custom utilities/programs for ${OS_NAME}." ; tput sgr0

echo "Time started:  ${startTime}."
echo "Time finished: $(date +"%T")."

exit 0
