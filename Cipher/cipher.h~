
#ifndef CIPHER_H
#define CIPHER_H

#include "header.h"

const string DEFAULT_CIPHER_TYPE = "xor";

const string VALID_CIPHER_TYPES[] = 
{
	"xor",
	"tea",
	"xtea",
	"xxtea"
};

const int VALID_CIPHER_TYPES_COUNT = 4;

extern string mCipherType;

string getCipherType();

void listValidCipherTypes();
void setCipherType(string cipherType);

bool isValidCipherType(string cipherType);

#endif

