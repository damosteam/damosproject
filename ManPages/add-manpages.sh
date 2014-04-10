#!/bin/bash

# Author: Daniel Puckowski
# Purpose: This script will automatically add manpages for custom DamOS programs and utilites to a system.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Adding manpages to system for custom DamOS programs and utilities..." ; tput sgr0

echo

echo 'Adding the following manpages: cipher, server, client, logger, processor, reader'

sudo cp ./cipher.1 /usr/share/man/man1/cipher.1
sudo chmod 0644 /usr/share/man/man1/cipher.1

sudo cp ./server.1 /usr/share/man/man1/server.1
sudo chmod 0644 /usr/share/man/man1/server.1

sudo cp ./client.1 /usr/share/man/man1/client.1
sudo chmod 0644 /usr/share/man/man1/client.1

sudo cp ./logger.1 /usr/share/man/man1/logger.1
sudo chmod 0644 /usr/share/man/man1/logger.1

sudo cp ./processor.1 /usr/share/man/man1/processor.1
sudo chmod 0644 /usr/share/man/man1/processor.1

sudo cp ./reader.1 /usr/share/man/man1/reader.1
sudo chmod 0644 /usr/share/man/man1/reader.1

echo

echo -e "${txtred}Done adding manpages to system." ; tput sgr0
