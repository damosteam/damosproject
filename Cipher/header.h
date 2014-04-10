
#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>

#include <string>
#include <fstream>
#include <iostream>
#include <sys/types.h>

#include "file.h"
#include "cipher.h"
#include "dirent.h"
#include "terminal.h"
#include "linkedList.h"
#include "encryption.h"
#include "decryption.h"

#include "HashFunctions/djb2.h"
#include "HashFunctions/sdbm.h"
#include "HashFunctions/adler32.h"
#include "HashFunctions/lookup3.h"

#include "CipherFunctions/xor.h"
#include "CipherFunctions/tea.h"
#include "CipherFunctions/xtea.h"
#include "CipherFunctions/xxtea.h"

using namespace std;

const string PROJECT_NAME    = "Low Overhead Encryption (LOE)";
const string PROJECT_AUTHOR  = "Daniel Puckowski";
const string PROGRAM_VERSION = "0.0.3.6";
const string LAST_UPDATE     = "04/13/2014";

const string RESET_ENCRYPTION_KEY_CODE     = "\\new";
const string CONFIGURATION_ENCRYPTION_KEY  = "local";
const string ADVANCED_USER_SHELL_CODE	   = "\\advanced";

const string ENCRYPTION_KEY_FILENAME       = "key.txt";
const string BLACKLIST_FILENAME            = "blacklist.txt";
const string EXTENSIONS_BLACKLIST_FILENAME = "extensions.txt";
const string TEMPORARY_FILENAME	           = "temporary.txt";

const int    PROGRAM_MODE_DECRYPTION       = 0;
const int    PROGRAM_MODE_ENCRYPTION       = 1;
const int    TERMINAL_DISPLAYED_ROWS	   = 24;

void run();
void runAdvancedShell();
void run(int argc, char *argv[]);
void parseCommands(string &commandString, LinkedList<string> &commands);

bool isBlacklistedFile(LinkedList<string> &blacklistedFiles, string filename);
bool isBlacklistedExtension(LinkedList<string> &blacklistedExtensions, string filename);
bool processCommands(LinkedList<string> &commands, LinkedList<string> &blacklistedFiles, LinkedList<string> &blacklistedExtensions);

string getEncryptionKeyFilename();

#endif
