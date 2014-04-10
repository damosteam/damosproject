
#ifndef CIPHER_CPP
#define CIPHER_CPP

#include "cipher.h"

string mCipherType = DEFAULT_CIPHER_TYPE;

string getCipherType()
{
	return mCipherType;
}


void listValidCipherTypes()
{
	cout << "The valid cipher types are: " << endl;

	for(int i = 0; i < VALID_CIPHER_TYPES_COUNT; i++)
	{
		cout << (i + 1) << ": " << VALID_CIPHER_TYPES[i] << endl;
	}
}


void setCipherType(string cipherType)
{
	if(isValidCipherType(cipherType) == true)
	{
		mCipherType = cipherType;
	}
	else
	{
		cout << "Error: invalid cipher type specified." << endl;

		listValidCipherTypes();
	}
}


bool isValidCipherType(string cipherType)
{
	for(int i = 0; i < VALID_CIPHER_TYPES_COUNT; i++)
	{
		if(cipherType == VALID_CIPHER_TYPES[i])
		{
			return true;
		} 
	}

	return false;
}

#endif
