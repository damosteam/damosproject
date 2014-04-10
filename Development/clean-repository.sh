#!/bin/bash

# Author: Daniel Puckowski
# Purpose: Clean the /damos-programs repository before pushing to GitHub.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Cleaning repository now..." ; tput sgr0

echo

sudo /damos-programs/Development/make-clean-all.sh

echo

cd /damos-programs
sudo rm -f *~ .*~

cd Cipher
sudo rm -f *~ .*~

cd CipherFunctions
sudo rm -f *~ .*~
cd ..

cd HashFunctions
sudo rm -f *~ .*~
cd ..

cd Scripts
sudo rm -f *~ .*~
cd ..

cd ..

cd CipherTesting
sudo rm -f *~ .*~

cd 'Project Gutenberg eBooks'
sudo rm -f *~ .*~
cd ..

cd ..

cd Client
sudo rm -f *~ .*~
cd ..

cd KeystrokeLogging
sudo rm -f *~ .*~

cd LinuxLogging
sudo rm -f *~ .*~

cd KeyLogger
sudo rm -f *~ .*~
cd ..

cd LogProcessor
sudo rm -f *~ .*~
cd ..

cd ..

cd WindowsLogging
sudo rm -f *~ .*~
cd ..

cd ..

cd ManPages
sudo rm -f *~ .*~
cd ..

cd MenuReader
sudo rm -f *~ .*~
cd ..

cd Server
sudo rm -f *~ .*~
cd ..

cd Valgrind
sudo rm -f *~ .*~
cd ..

cd Development
sudo rm -f *~ .*~
cd ..

cd System
sudo rm -f *~ .*~
cd ..

echo -e "${txtred}Done cleaning repository." ; tput sgr0

exit 0




