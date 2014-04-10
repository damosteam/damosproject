
Low Overhead Encryption Program
Project LOE

Author: Daniel Puckowski

Program usage: loe.exe <KEY FILE> <OPERATION> 
Operations: 

-e Use this argument to encrypt text passed to this program via a terminal or script. 
-d Use this argument to decrypt text passed to this program via a terminal or script.
-E Use this argument to encrypt every file within the directory of this executable.
-D Use this argument to decrypt every file within the directory of this executable.
	
Additional arguments: 

-v Enables verbose mode. The program will provide more specific information to the terminal about the operation that is currently executing.
-w Enables whitelist mode. Using this mode will make the program treat the blacklist file as a whitelist file instead to determine which files to encrypt/decrypt and which files to ignore.
-ecf Encrypt the configuration files using a predetermined encryption key defined in the program source.
-dcf Decrypt the configuration files using a predetermined encryption key defined in the program source.

Example usage: 

loe.exe key.txt -e "I want to encrypt this text."
loe.exe key.txt -v -w -D
./loe inlineKey0xFF99 -e OneWordToEncrypt
./loe key.txt -dcf -e "Testing encryption." -ecf

Usage notes: Order matters! The program will interpret commands from left to right. Therefore, if you need to unencrypt configuration files before you use them, make sure the command "-dcf" appears before any encryption/decryption operation such as "-e".

Program Configuration
 
Inside the directory of this program's executable must be the following files:

key.txt Specifies the "key" to use for encryption/decryption. The entire key must be on one line (first line in file). The key may contain spaces and does not need to be wrapped in quotes.

blacklist.txt This file specifies files the program is to ignore when encrypting/decrypting the directory. In order for the program to operate correctly a few filenames must be specified within the file, where each filename gets its own line in the file. Here are the filenames required to start:

.
..
key.txt
loe.exe (or whatever you have named this program's executable)
blacklist.txt
extensions.txt
				 
Note: The filenames above are not required (and should actually be removed) if you intend to
encrypt the directory using the blacklist as a whitelist file only (with the -w argument).
Manage the names in this file accordingly. Failing to do so may cause irreversible damage to files.
				 
extensions.txt This file specifies file extensions the program is to ignore when encrypting/decrypting the directory. The format of this file is similar to the format of the blacklist file. Each extension gets its own line in the file. An example would look like:
.bat
.sh
				  
Always configure this program and test it using a copy of a directory you eventually intend to encrypt.
This way you ensure you have configured all the appropriate files for your scenario without causing
irreversible damage to any of your original files. 
