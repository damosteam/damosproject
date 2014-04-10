#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <iostream>
#include <sys/types.h>

#include "header.h"
#include "dirent.h"
#include "terminal.h"
#include "linkedList.h"

using namespace std;

void setNewEncryptionKey(string &keyFilename);
void saveEncryptionArgument(string &argument);
void loadEncryptionArgument(string &argument);
void readTeaEncryptionKey(string &keyFilename, uint32_t teaKey[4], bool suppressOutput);

bool isFileEmpty(ifstream &file);
bool removeFile(string &filename);
bool stringEndsWith(string &fullString, string &ending);
bool renameFile(string &currentName, string &targetName);
bool getAllFilesInDirectory(LinkedList<string> &directoryFilenames);
bool readBlacklistFile(LinkedList<string> &blacklistedFiles, bool suppressOutput);
bool readExtensionsBlacklistFile(LinkedList<string> &blacklistedExtensions, bool suppressOutput);

string readEncryptionKey(string &keyFilename, bool suppressOutput);

#endif


