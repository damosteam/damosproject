#!/bin/bash

# Author: Daniel Puckowski
# Purpose: Push the /damos-programs repository to GitHub.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Pushing repository to GitHub now..." ; tput sgr0

sudo git add --all .

echo 'Enter a message for the commit: '
read commitMessage

sudo git commit -m "$commitMessage"
sudo git push -u origin master

echo -e "${txtred}Done pushing repository to GitHub." ; tput sgr0

exit 0
