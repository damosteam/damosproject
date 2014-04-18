
#ifndef HASH_CPP
#define HASH_CPP

#include "hash.h"

using namespace std;

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


void hashString(char* data, unsigned int hashTableSize)
{
	string hashedData = "";

	if(mHashType == "djb2")
	{
		//unsigned long hash = djb2Hash(data);

		//hashedData = ;
	}
	else if(mHashType == "sdbm")
	{
		//unsigned long hash = sbdmHash(data);

		//hashedData = ;
	}
	else if(mHashType == "adler32")
	{
		//uint32_t hash = adler32Hash(data, strlen(data));

		//hashedData = ; 
	}
	else if(mHashType == "lookup3")
	{
		unsigned int hashAddress;
		unsigned int initialValue;

		initialValue = 12321;

		//hashAddress = lookup3Hash(data, strlen(data), initialValue);	
		
		//return (hashAddress % hashTableSize);
	}
}

#endif
