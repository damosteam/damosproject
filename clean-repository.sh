#!/bin/bash

#
#

echo -e "Cleaning repository now..."

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

echo -e "Done cleaning repository."

exit 0




