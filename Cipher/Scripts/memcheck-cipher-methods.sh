#!/bin/bash

# Author: Daniel Puckowski
# Purpose: Check for memory leaks in the cipher methods of the custom DamOS Cipher program.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red
txtgrn='\e[0;32m' # Green
txtylw='\e[0;33m' # Yellow
txtblu='\e[0;34m' # Blue
txtpur='\e[0;35m' # Purple
txtcyn='\e[0;36m' # Cyan
txtwht='\e[0;37m' # White

# Bold escape sequence. (For reference here)
# echo -e "\033[1mBold.\033[0m"

echo -e "${txtred}Memory leak test for the cipher methods of the custom DamOS Cipher program." ; tput sgr0

cd /damos-programs/Cipher/Scripts
cp /damos-programs/Cipher/loe ./loe

echo

echo 'Testing for memory leaks in the cipher methods using Valgrind...'
echo 'Note: This test is not completely determinant of the possible existence of a memory leak.'

echo 

read -p 'Would you like to remove all previous test reports? ' -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    rm -f valgrindLeakTest*
    echo 'All previous test reports removed from current directory.' 
fi

echo

outputFile=valgrindLeakTest-$(date "+%b_%d_%Y_%H_%M_%S").txt
touch $outputFile

echo "All Valgrind output going to file $outputFile."

echo 'Testing for memory leaks in the xor cipher method now...'

echo -e "Arguments passed: ./loe inlineKey1 -e \"Hello world!\""
(valgrind --leak-check=full --show-reachable=yes ./loe inlineKey1 -e \"Hello world!\") >> $outputFile 2>&1

echo -e "Arguments passed: ./loe inlineKey1 -d \"Hello world!\""
(valgrind --leak-check=full --show-reachable=yes ./loe inlineKey1 -d) >> $outputFile 2>&1

echo 'Done testing for memory leaks in the xor cipher method.'

echo 'Testing for memory leaks in the tea cipher method now...'

echo -e "Arguments passed: ./loe inlineKey1 -c tea -e \"Hello world!\""
(valgrind --leak-check=full --show-reachable=yes ./loe inlineKey1 -c tea -e \"Hello world!\") >> $outputFile 2>&1

echo -e "Arguments passed: ./loe inlineKey1 -c tea -d \"Hello world!\""
(valgrind --leak-check=full --show-reachable=yes ./loe inlineKey1 -c tea -d) >> $outputFile 2>&1

echo 'Done testing for memory leaks in the tea cipher method.'

echo 'Testing for memory leaks in the xtea cipher method now...'

echo -e "Arguments passed: ./loe inlineKey1 -c xtea -e \"Hello world!\""
(valgrind --leak-check=full --show-reachable=yes ./loe inlineKey1 -c xtea -e \"Hello world!\") >> $outputFile 2>&1

echo -e "Arguments passed: ./loe inlineKey1 -c xtea -d \"Hello world!\""
(valgrind --leak-check=full --show-reachable=yes ./loe inlineKey1 -c xtea -d) >> $outputFile 2>&1

echo 'Done testing for memory leaks in the xtea cipher method.'

echo 'Testing for memory leaks in the xxtea cipher method now...'

echo -e "Arguments passed: ./loe inlineKey1 -c xxtea -e \"Hello world!\""
(valgrind --leak-check=full --show-reachable=yes ./loe inlineKey1 -c xxtea -e \"Hello world!\") >> $outputFile 2>&1

echo -e "Arguments passed: ./loe inlineKey1 -c xxtea -d \"Hello world!\""
(valgrind --leak-check=full --show-reachable=yes ./loe inlineKey1 -c xxtea -d) >> $outputFile 2>&1

echo 'Done testing for memory leaks in the xxtea cipher method.'

echo 'Done testing for memory leaks in the cipher methods of the custom DamOS Cipher program.'
echo "To review the report, refer to the following file: ./$outputFile"

echo 

echo -e "Optionally, enter Y to \"more\" the report now."

read -p 'Review test results? ' -n 1 -r
if [[ $REPLY =~ ^[Yy]$ ]]
then
    echo
    more ./$outputFile
fi

echo

echo -e "${txtred}Test complete." ; tput sgr0

rm -f ./loe

exit 0
