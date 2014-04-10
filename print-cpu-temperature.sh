#!/bin/bash

# Author: Daniel Puckowski
# Purpose: This script will print system CPU temperature information for monitoring purposes.
 
# ACPI (Advanced Configuration and Power Interface) is an open industry specification co-developed by 
# Hewlett-Packard, Intel, Microsoft, Phoenix, and Toshiba.

# ACPI establishes industry-standard interfaces enabling OS-directed configuration, power management, 
# and thermal management of mobile, desktop, and server platforms.

# When first published in 1996, ACPI evolved an existing collection of power management BIOS code, 
# Advanced Power Management (APM) application programming interfaces (APIs), PNPBIOS APIs, and 
# Multiprocessor Specification (MPS) tables into a well-defined power management and configuration 
# interface specification.

# The specification enables new power management technologies to evolve independently in operating 
# systems and hardware while ensuring that they continue to work together.

# Uncomment the next line if you do not already have 'acpi' currently installed.
# sudo apt-get install acpi

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red

echo -e "${txtred}Current CPU temperature information: " ; tput sgr0
acpi -t

echo 

## oDroid specific CPU frequency and temperature readout below.
# watch "echo -n 'Hostname: ' && hostname && echo -n 'CPU Frequency: ' \
# && echo $((`sudo cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq` /1000))'Mhz' \
# && echo -n 'TEMP: ' && sudo cat /sys/devices/platform/tmu/temperature"

echo 'Note: If using an oDroid...'
echo 'Do not push the CPU temperature past 105 degrees Celsius. Since the operating temperature range for LPDDR2 RAM is ~95 degrees Celsius, it is recommended that you keep the CPU temperature at or below 90 degrees Celsius.'

echo 

exit 0
