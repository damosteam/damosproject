#!/bin/bash

# Author: Daniel Puckowski
# Purpose: Pull the damosproject repository at GitHub to system.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Pulling the \"damosproject\" repository (master branch) to system now..." ; tput sgr0

sudo git remote add origin https://github.com/damosteam/damosproject.git
sudo git pull origin master

echo -e "${txtred}Done pulling repository." ; tput sgr0

exit 0
