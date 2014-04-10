#!/bin/bash

# Author: Daniel Puckowski
# Purpose: This script will install required dependencies for the custom DamOS programs and utilites.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo 'Installing all dependencies for the custom DamOS programs and utilites now...'

echo

echo -e "${txtred}Note: This script will try to install dependencies for several different
system architectures at once. Expect to see some failure-to-install messages." ; tput sgr0

echo 

echo -e "${txtred}Additional notice: This script was written for a Debian Linux based distribution.
It is not guaranteed that all dependencies will be properly installed for every Linux distribution." ; tput sgr0

echo

echo 'Dependency list: aptitude, g++, g++-arm-linux-gnueabi, g++-arm-linux-gnueabihf, libc6-dbg, valgrind, acpi, coreutils'

echo

read -p 'Ready to proceed? ' -n 1 -r
if [[ $REPLY =~ ^[Nn]$ ]]
then
    echo
    exit 0
fi

echo 

sudo apt-get update
sudo apt-get upgrade

## Front-end to the Advanced Packaging Tool (APT)
sudo apt-get install aptitude

## Make utility
sudo apt-get install make

## G++, a *nix-based C++ compiler
sudo apt-get install g++

## G++, a *nix-based C++ compiler for ARM systems without hard float
sudo apt-get install g++-arm-linux-gnueabi

## G++, a *nix-based C++ compiler for ARM systems with hard float
sudo apt-get install g++-arm-linux-gnueabihf

## Dependency for memory debugging tool Valgrind
sudo apt-get install libc6-dbg

## Memory debugging tool Valgrind
sudo apt-get install valgrind

## Memory debugging tool Valgrind 
sudo aptitude install valgrind

## Advanced Configuration and Power Interface (ACPI) utility
sudo apt-get install acpi

## Coreutils installed to ensure we may use the shred utility.
## Shred can be used to securely delete files and devices.
sudo apt-get install coreutils

echo 'Suggested optional packages: tmux, lynx, vim'

echo

read -p 'Install additional (optional) packages? ' -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    
    ## Graphical text editor gedit
    # sudo apt-get install gedit

    ## Terminal multiplexer tmux 
    sudo apt-get install tmux

    ## Text-based web browser Lynx
    sudo apt-get install lynx

    ## Vim, the popular vi clone text editor
    sudo apt-get install vim
fi

echo -e "${txtred}Done installing dependencies." ; tput sgr0

echo

exit 0
