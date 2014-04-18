
#ifndef HASH_H
#define HASH_H

#include "header.h"

const string DEFAULT_HASH_TYPE = "djb2";

const string VALID_HASH_TYPES[] = 
{
	"djb2",
	"sdbm",
	"adler32",
	"lookup3",
	"md5"
};

const int VALID_HASH_TYPES_COUNT = 5;

extern string mHashType;

string getHashType();
string hashString(string data, int hashTableSize);

void listValidHashTypes();
void setHashType(string hashType);

bool isValidHashType(string hashType);

#endif

