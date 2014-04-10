
#ifndef HASH_CPP
#define HASH_CPP

#include "hash.h"

string mHashType = DEFAULT_HASH_TYPE;

string getHashType()
{
	return mHashType;
}


void listValidHashTypes()
{
	cout << "The valid hash types are: " << endl;

	for(int i = 0; i < VALID_HASH_TYPES_COUNT; i++)
	{
		cout << (i + 1) << ": " << VALID_HASH_TYPES[i] << endl;
	}
}


void setHashType(string hashType)
{
	if(isValidHashType(hashType) == true)
	{
		mHashType = hashType;
	}
	else
	{
		cout << "Error: invalid hash type specified." << endl;

		listValidHashTypes();
	}
}


bool isValidHashType(string hashType)
{
	for(int i = 0; i < VALID_HASH_TYPES_COUNT; i++)
	{
		if(hashType == VALID_HASH_TYPES[i])
		{
			return true;
		} 
	}

	return false;
}

#endif
