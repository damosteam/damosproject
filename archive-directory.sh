#!/bin/bash

# Author: Daniel Puckowski
# Purpose: This is a simple script to archive and compress the contents of a directory.
 
## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Archiving current directory now..." ; tput sgr0

echo

tar cvf - . --exclude='archive.tar.gz' | gzip -9 - > archive.tar.gz

echo

echo -e "${txtred}Done." ; tput sgr0

exit 0
