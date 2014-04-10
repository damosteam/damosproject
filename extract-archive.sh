#!/bin/bash

# Author: Daniel Puckowski
# Purpose: This script will extract and decompress files stored in an archive named "archive.tar.gz".

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Extracting archive \"archive.tar.gz\" now..." ; tput sgr0

echo

tar -zxvf archive.tar.gz

echo

echo -e "$txtred}Done." ; tput sgr0

exit 0
