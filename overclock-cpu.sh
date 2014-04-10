#!/bin/bash

# Author: Daniel Puckowski
# Purpose: This script will overclock the CPU of an oDroid U3.
 
## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Setting scaling_max_freq to 1.920 GHz..." ; tput sgr0
echo 1920000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq
echo "Done."

exit 0
