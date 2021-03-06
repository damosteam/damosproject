#!/bin/bash

# Author: Daniel Puckowski
# Date (last edit): 04/13/2014
# Purpose: This is a simple Bash script to test de/encryption of files in a directory.

## Color map for script text.
txtblk='\e[0;30m' # Black - Regular
txtred='\e[0;31m' # Red
txtgrn='\e[0;32m' # Green
txtylw='\e[0;33m' # Yellow
txtblu='\e[0;34m' # Blue
txtpur='\e[0;35m' # Purple
txtcyn='\e[0;36m' # Cyan
txtwht='\e[0;37m' # White

echo "Copying test files to current directory..."

cp /damos-programs/Cipher/loe ./loe

cp ./"Project Gutenberg eBooks"/"A Tale of Two Cities.txt" .
cp ./"Project Gutenberg eBooks"/"Complete Works of William Shakespeare.txt" .
cp ./"Project Gutenberg eBooks"/"Essays of Montaigne.txt" .
cp ./"Project Gutenberg eBooks"/"Grimms' Fairy Tales.txt" .
cp ./"Project Gutenberg eBooks"/"Heart of Darkness.txt" .
cp ./"Project Gutenberg eBooks"/"Jungle Book.txt" .
cp ./"Project Gutenberg eBooks"/"Leviathan.txt" .
cp ./"Project Gutenberg eBooks"/"Siddhartha.txt" .
cp ./"Project Gutenberg eBooks"/"The Illiad.txt" .
cp ./"Project Gutenberg eBooks"/"The Odyssey.txt" .
cp ./"Project Gutenberg eBooks"/"The Republic.txt" .
cp ./"Project Gutenberg eBooks"/"Treasure Island.txt" .

echo "Done copying test files to current directory."
echo

startTime=$(date +"%s")
readableStartTime=$(date +"%T")

# Encrypt all of the original files...
echo "Encrypting contents of directory using xor cipher..."
./loe -v key.txt -E

# Now decrypt the encrypted files...
echo "Decrypting contents of directory using xor cipher..."
./loe -v key.txt -D

endTime=$(date +"%s")
readableEndTime=$(date +"%T")

echo

# Check our eBooks for any de/encryption failures...
echo "Testing en/decrypted files against original copies now..."
echo

if cmp -s ./"Grimms' Fairy Tales.txt" ./"Project Gutenberg eBooks"/"Grimms' Fairy Tales.txt"; then
	echo -e "Grimms' Fairy Tales.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "Grimms' Fairy Tales.txt${txtred}" Fail ; tput sgr0
fi

if cmp -s ./"A Tale of Two Cities.txt" ./"Project Gutenberg eBooks"/"A Tale of Two Cities.txt"; then
	echo -e "A Tale of Two Cities.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "A Tale of Two Cities.txt${txtred}" Fail ; tput sgr0
fi

if cmp -s ./"Complete Works of William Shakespeare.txt" ./"Project Gutenberg eBooks"/"Complete Works of William Shakespeare.txt"; then
	echo -e "Complete Works of William Shakespeare.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "Complete Works of William Shakespeare.txt${txtred}" Fail ; tput sgr0
fi

if cmp -s ./"Essays of Montaigne.txt" ./"Project Gutenberg eBooks"/"Essays of Montaigne.txt"; then
	echo -e "Essays of Montaigne.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "Essays of Montaigne.txt${txtred}" Fail ; tput sgr0
fi

if cmp -s ./"Heart of Darkness.txt" ./"Project Gutenberg eBooks"/"Heart of Darkness.txt"; then
	echo -e "Heart of Darkness.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "Heart of Darkness.txt${txtred}" Fail ; tput sgr0
fi

if cmp -s ./"Jungle Book.txt" ./"Project Gutenberg eBooks"/"Jungle Book.txt"; then
	echo -e "Jungle Book.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "Jungle Book.txt${txtred}" Fail ; tput sgr0
fi

if cmp -s ./"Leviathan.txt" ./"Project Gutenberg eBooks"/"Leviathan.txt"; then
	echo -e "Leviathan.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "Leviathan.txt${txtred}" Fail ; tput sgr0
fi

if cmp -s ./"Siddhartha.txt" ./"Project Gutenberg eBooks"/"Siddhartha.txt"; then
	echo -e "Siddhartha.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "Siddhartha.txt${txtred}" Fail ; tput sgr0
fi

if cmp -s ./"The Illiad.txt" ./"Project Gutenberg eBooks"/"The Illiad.txt"; then
	echo -e "The Illiad.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "The Illiad.txt${txtred}" Fail ; tput sgr0
fi

if cmp -s ./"The Odyssey.txt" ./"Project Gutenberg eBooks"/"The Odyssey.txt"; then
	echo -e "The Odyssey.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "The Odyssey.txt${txtred}" Fail ; tput sgr0
fi

if cmp -s ./"The Republic.txt" ./"Project Gutenberg eBooks"/"The Republic.txt"; then
	echo -e "The Republic.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "The Republic.txt${txtred}" Fail ; tput sgr0
fi

if cmp -s ./"Treasure Island.txt" ./"Project Gutenberg eBooks"/"Treasure Island.txt"; then
	echo -e "Treasure Island.txt${txtgrn}" Success ; tput sgr0
else
	echo -e "Treasure Island.txt${txtred}" Fail ; tput sgr0
fi

echo

echo "Time started:  ${readableStartTime}."
echo "Time finished: ${readableEndTime}."

echo

echo "Amount of data en/decrypted:    10.847 MB"
echo "Total amount of data processed: 21.694 MB"

echo

diff=$(($endTime-$startTime))

# echo "Time elapsed: $(($diff / 60)) minutes and $(($diff % 60)) seconds."
echo -e "${txtred}Cipher rate: 21.694 MB / $(($diff / 60)) minute(s) and $(($diff % 60)) second(s)." ; tput sgr0

echo -e "${txtred}Test complete." ; tput sgr0
echo

rm -f *_tmp

rm -f ./"A Tale of Two Cities.txt" 
rm -f ./"Complete Works of William Shakespeare.txt" 
rm -f ./"Essays of Montaigne.txt" 
rm -f ./"Grimms' Fairy Tales.txt" 
rm -f ./"Heart of Darkness.txt" 
rm -f ./"Jungle Book.txt" 
rm -f ./"Leviathan.txt" 
rm -f ./"Siddhartha.txt" 
rm -f ./"The Illiad.txt" 
rm -f ./"The Odyssey.txt" 
rm -f ./"The Republic.txt" 
rm -f ./"Treasure Island.txt"

rm -f ./loe

exit 0
