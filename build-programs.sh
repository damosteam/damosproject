#!/bin/bash

# Author: Daniel Puckowski
# Purpose: Build the custom DamOS programs using make and g++.

OS_NAME='DamOS'

echo "Building custom utilities/programs for ${OS_NAME}..."

startTime=$(date +"%T")

echo 'Building cipher program now...'
cd ./Cipher
echo $(pwd)
make clean
make
echo 'Done building cipher program.'
cd ..

echo 'Building server program now...'
cd ./Server
echo $(pwd)
make clean
make
echo 'Done building server program.'
cd ..

echo 'Building client program now...'
cd ./Client
echo $(pwd)
make clean
make
echo 'Done building client program.'
cd ..

echo 'Building keylogger program now...'
cd ./KeyLogger
echo $(pwd)
make clean
make
echo 'Done building keylogger program.'
cd ..

echo 'Building log-processor utility now...'
cd ./LogProcessor
echo $(pwd)
make clean
make
echo 'Done building log-processor utility.'
cd ..

echo 'Building menu reader utility now...'
cd ./MenuReader
echo $(pwd)
make clean
make
echo 'Done building menu reader utility.'
cd ..

echo "Done building custom utilities/programs for ${OS_NAME}."

echo "Time started:  ${startTime}."
echo "Time finished: $(date +"%T")."

exit 0
