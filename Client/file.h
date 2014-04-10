
#ifndef FILE_H
#define FILE_H

#include "header.h"

extern const char* CLIENT_ID_FILENAME;

extern std::string mClientID;

bool isFileExist(const char *filename);

int readClientIDFile();
int createClientIDFile();

#endif
