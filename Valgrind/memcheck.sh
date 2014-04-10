#!/bin/bash

# Author: Daniel Puckowski
# Date created: 03/25/2014
# Purpose: Check for memory leaks in the custom DamOS programs.
# Usage: ./memcheck.sh
# Platform: Linux/Debian
# Script version: 0.0.2.2
# Date last edited: 04/15/2014

scriptVersion="0.0.2.2"

## Uncomment this to install Valgrind (on Linux/Debian distributions).
# sudo apt-get update
# sudo apt-get install libc6-dbg
# sudo apt-get install valgrind
## If the commands above failed to install Valgrind, try the following:
# sudo apt-get install aptitude
# sudo aptitude install valgrind

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red
txtgrn='\e[0;32m' # Green
txtylw='\e[0;33m' # Yellow
txtblu='\e[0;34m' # Blue
txtpur='\e[0;35m' # Purple
txtcyn='\e[0;36m' # Cyan
txtwht='\e[0;37m' # White

# Bold escape sequence. (For reference here)
# echo -e "\033[1mBold.\033[0m"

echo -e "${txtred}Memory leak test for the Custom DamOS programs and utilities." ; tput sgr0
echo "Script version: $scriptVersion."

echo

# echo 'Note: this script will reference DamOS programs and utilities by their default build name (defined in their respective makefiles). It is also assumed that all of their executables are in the same working directory of this script.'

# Copy DamOS executables to working directory for testing.
echo 'Copying DamOS executables to working directory for testing...'

cd /damos-programs/Valgrind

cp ../Cipher/loe ./loe
cp ../Client/client ./client
cp ../Server/server ./server
cp ../MenuReader/menu ./menu
cp ../KeystrokeLogging/LinuxLogging/KeyLogger/logger ./logger
cp ../KeystrokeLogging/LinuxLogging/LogProcessor/processor ./processor

# echo

echo -e "If you need help with building the custom DamOS programs look for an automatic build script named build-programs.sh. In the directory of the build script run the command: \"$ ./build-programs.sh\" and the programs will be built for you."
 
echo

echo 'The following programs will be tested: ./menu ./loe ./logger ./processor ./server ./client'

read -p 'Print contents of working directory now, to verify? ' -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    ls --color=always -lFa
fi

echo

read -p 'Would you like to stop now? ' -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    exit 0
fi

echo 

echo 'Testing for memory leaks in the custom DamOS programs using Valgrind...'
echo 'Note: This test is not completely determinant of the possible existence of a memory leak.'

echo 

# echo 'Note: As it is currently scripted, this test will require some user interaction. In addition, user knowledge of how to use some of the DamOS programs may be necessary.'

## Just for reference.
# for var in "$@"
# do
#	 echo "Processing argument $var now..."
# done

read -p 'Would you like to remove all previous test reports? ' -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    rm -f valgrindLeakTest*
    echo 'All previous test reports removed from current directory.' 
fi

echo

outputFile=valgrindLeakTest-$(date "+%b_%d_%Y_%H_%M_%S").txt
touch $outputFile

echo "All Valgrind output going to file $outputFile."

# echo 'Creating alias for Valgrind detailed memory leak detector now...'
# alias leak-check='valgrind --leak-check=yes'
# alias leak-check='valgrind --leak-check=full'

echo 'Testing for memory leaks in menu reader utility now...'
echo -e '\nMenu Reader Utility\n' >> $outputFile

echo 'Arguments passed: ./menu'
(valgrind --leak-check=yes ./menu) >> $outputFile 2>&1

echo 'Arguments passed: ./menu menufile.txt'
(valgrind --leak-check=yes ./menu menufile.txt) >> $outputFile 2>&1

echo 'Done testing for memory leaks in menu reader utility.'

echo 'Testing for memory leaks in encryption program now...'
echo -e '\nEncryption Program\n' >> $outputFile

# echo 'Arguments passed: ./loe'
# (valgrind --leak-check=yes ./loe) >> $outputFile 2>&1

echo -e "Arguments passed: ./loe -e inlineKey \"Test in-line encryption.\""
(valgrind --leak-check=yes ./loe -e inlineKey "Test in-line encryption.") >> $outputFile 2>&1

echo -e "Arguments passed: ./loe -d inlineKey \"Test in-line encryption.\""
(valgrind --leak-check=yes ./loe -d inlineKey "Test in-line encryption.") >> $outputFile 2>&1

## Only uncomment the following two lines if the working directory is properly configured
## for full-directory encryption using the DamOS encryption program.
# echo 'Arguments passed: ./loe -D inlineKey'
# (valgrind --leak-check=yes ./loe -D inlineKey) >> $outputFile 2>&1

echo -e "Arguments passed: ./loe -e key.txt \"Test in-line encryption.\""
(valgrind --leak-check=yes ./loe -e key.txt "Test in-line encryption.") >> $outputFile 2>&1

echo 'Done testing for memory leaks in encryption program.'

echo 'Testing for memory leaks in keystroke logger utility now...'
echo -e '\nLinux Keystroke Logger Utility\n' >> $outputFile

echo 'Arguments passed: ./logger'
(valgrind --leak-check=yes ./logger) >> $outputFile 2>&1

echo 'Arguments passed: ./logger /dev/input/event2'
(valgrind --leak-check=yes ./logger /dev/input/event2) >> $outputFile 2>&1

echo 'Arguments passed: ./logger /dev/input/event2 logFile.txt'
(valgrind --leak-check=yes ./logger /dev/input/event2 logFile.txt) >> $outputFile 2>&1

echo 'Done testing for memory leaks in keystroke logger utility.'

echo 'Testing for memory leaks in keystroke log processor utility now...'
echo -e '\nLinux Keystroke Log Processor Utility\n' >> $outputFile

echo 'Arguments passed: ./processor'
(valgrind --leak-check=yes ./processor) >> $outputFile 2>&1

echo 'Arguments passed: ./processor log.txt'
(valgrind --leak-check=yes ./processor log.txt) >> $outputFile 2>&1

echo 'Done testing for memory leaks in keystroke log processor utility.'

echo 'Testing for memory leaks in server program now...'
echo -e '\nServer Program\n' >> $outputFile

echo 'Arguments passed: ./server'
(valgrind --leak-check=yes ./server) >> $outputFile 2>&1

echo 'Arguments passed: ./server 127.0.0.1'
(valgrind --leak-check=yes ./server 127.0.0.1) >> $outputFile 2>&1

# echo 'Arguments passed: ./server 127.0.0.1 &'
# (valgrind --leak-check=yes ./server 127.0.0.1 &) >> $outputFile 2>&1

echo 'Done testing for memory leaks in server program.'

echo 'Testing for memory leaks in client program now...'
echo -e '\nClient Program\n' >> $outputFile

echo 'Arguments passed: ./client'
(valgrind --leak-check=yes ./client) >> $outputFile 2>&1

echo 'Arguments passed: ./client 127.0.0.1'
(valgrind --leak-check=yes ./client 127.0.0.1) >> $outputFile 2>&1

echo 'Arguments passed: ./client 127.0.0.1 5555'
(valgrind --leak-check=yes ./client 127.0.0.1 5555) >> $outputFile 2>&1

# echo 'Arguments passed: ./client 127.0.0.1 5556 &'
# (valgrind --leak-check=yes ./client 127.0.0.1 5556 &) >> $outputFile 2>&1

echo 'Done testing for memory leaks in client program.'

echo

echo 'Done testing for memory leaks in the custom DamOS programs and utilities.'
echo "To review the report, refer to the following file: ./$outputFile"

echo 

echo -e "Optionally, enter Y to \"more\" the report now."

read -p 'Review test results? ' -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    more ./$outputFile
fi

echo

echo -e "Note: It is recommended to run the command \"$ ps aux\" now. This is to check for any DamOS programs that may still be running in the background after the test. They will need to be manually killed (kill -9 PID)."

read -p 'List running processes now? ' -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    ps aux
fi

echo

# Remove DamOS executables after testing.
echo 'Removing DamOS executables from working directory...'

rm -f ./loe
rm -f ./client
rm -f ./server
rm -f ./menu
rm -f ./logger
rm -f ./processor

# Generated while testing Client program.
rm -f ./localid.txt

echo -e "${txtred}Test complete." ; tput sgr0

exit 0
