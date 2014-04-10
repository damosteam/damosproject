#!/bin/bash

# Author: Daniel Puckowski
# Purpose: Test the four cipher methods of the custom DamOS Cipher program.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red
txtgrn='\e[0;32m' # Green
txtylw='\e[0;33m' # Yellow
txtblu='\e[0;34m' # Blue
txtpur='\e[0;35m' # Purple
txtcyn='\e[0;36m' # Cyan
txtwht='\e[0;37m' # White

echo -e "${txtred}Testing the four cipher methods of the custom DamOS Cipher program now..." ; tput sgr0
echo

cd /damos-programs/Cipher/Scripts
cp /damos-programs/Cipher/loe ./loe

echo -e "${txtylw}Testing xor cipher..." ; tput sgr0
echo -e "Input: \"Hello world!\""

encryptedResult=`./loe inlineKey1 -e \"Hello world!\"`

echo -e "Inline encryption result: $encryptedResult"

decryptedResult=`./loe inlineKey1 -d $encryptedResult`

echo -e "Inline decryption result: $decryptedResult"

echo
echo -e "Input: \"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789.\""

encryptedResult=`./loe inlineKey1 -e \"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789.\"`

echo -e "Inline encryption result: $encryptedResult"

decryptedResult=`./loe inlineKey1 -d $encryptedResult`

echo -e "Inline decryption result: $decryptedResult"

echo -e "${txtylw}Done testing xor cipher." ; tput sgr0 
echo

echo -e "${txtylw}Testing tea cipher..." ; tput sgr0
echo -e "Input: \"Hello world!\""

encryptedResult=`./loe inlineKey1 -c tea -e \"Hello world!\"`

echo -e "Inline encryption result: $encryptedResult"

decryptedResult=`./loe inlineKey1 -c tea -d $encryptedResult`

echo -e "Inline decryption result: $decryptedResult"

echo
echo -e "Input: \"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789.\""

encryptedResult=`./loe inlineKey1 -c tea -e \"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789.\"`

echo -e "Inline encryption result: $encryptedResult"

decryptedResult=`./loe inlineKey1 -c tea -d $encryptedResult`

echo -e "Inline decryption result: $decryptedResult"

echo -e "${txtylw}Done testing tea cipher." ; tput sgr0
echo

echo -e "${txtylw}Testing xtea cipher..." ; tput sgr0
echo -e "Input: \"Hello world!\""

encryptedResult=`./loe inlineKey1 -c xtea -e \"Hello world!\"`

echo -e "Inline encryption result: $encryptedResult"

decryptedResult=`./loe inlineKey1 -c xtea -d $encryptedResult`

echo -e "Inline decryption result: $decryptedResult"

echo
echo -e "Input: \"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789.\""

encryptedResult=`./loe inlineKey1 -c xtea -e \"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789.\"`

echo -e "Inline encryption result: $encryptedResult"

decryptedResult=`./loe inlineKey1 -c xtea -d $encryptedResult`

echo -e "Inline decryption result: $decryptedResult"

echo -e "${txtylw}Done testing xtea cipher." ; tput sgr0
echo

echo -e "${txtylw}Testing xxtea cipher..." ; tput sgr0
echo -e "Input: \"Hello world!\""

encryptedResult=`./loe inlineKey1 -c xxtea -e \"Hello world!\"`

echo -e "Inline encryption result: $encryptedResult"

decryptedResult=`./loe inlineKey1 -c xxtea -d $encryptedResult`

echo -e "Inline decryption result: $decryptedResult"

echo
echo -e "Input: \"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789.\""

encryptedResult=`./loe inlineKey1 -c xxtea -e \"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789.\"`

echo -e "Inline encryption result: $encryptedResult"

decryptedResult=`./loe inlineKey1 -c xxtea -d $encryptedResult`

echo -e "Inline decryption result: $decryptedResult"

echo -e "${txtylw}Done testing xxtea cipher." ; tput sgr0
echo

echo -e "${txtred}Finished all testing." ; tput sgr0
echo

rm -f ./loe

exit 0
