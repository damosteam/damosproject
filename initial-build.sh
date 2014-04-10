#!/bin/bash

# Author: Daniel Puckowski
# Purpose: This script will automatically build the custom DamOS programs and utilities.

OS_NAME='DamOS'

echo "Building custom utilities/programs for ${OS_NAME}..."

startTime=$(date +"%T")

echo 'Making sure proper dependencies are installed...'

sudo apt-get install g++ 

## G++ package for ARM without hard float
# sudo apt-get install gcc-arm-linux-gnueabi

## G++ package for ARM with hard float
# sudo apt-get install gcc-arm-linux-gnueabihf

echo 'Extracting source code from archive...'
./extract.sh
echo 'Done extracting source code.'

echo 'Building cipher program now...'
cd ./Cipher
echo $(pwd)
make
echo 'Done building cipher program.'
cd ..

echo 'Building server program now...'
cd ./Server
echo $(pwd)
make
echo 'Done building server program.'
cd ..

echo 'Building client program now...'
cd ./Client
echo $(pwd)
make
echo 'Done building client program.'
cd ..

echo 'Building keylogger program now...'
cd ./KeyLogger
echo $(pwd)
make
echo 'Done building keylogger program.'
cd ..

echo 'Building log-processor utility now...'
cd ./LogProcessor
echo $(pwd)
make
echo 'Done building log-processor utility.'
cd ..

echo 'Building menu reader utility now...'
cd ./MenuReader
echo $(pwd)
make
echo 'Done building menu reader utility.'
cd ..

echo "Done building custom utilities/programs for ${OS_NAME}."

echo "Time started:  ${startTime}."
echo "Time finished: $(date +"%T")."

exit 0
