
#ifndef SDBM_CPP
#define SDBM_CPP

#include "sdbm.h"

string sdbmHash(string data)
{
	const unsigned char* formattedData = reinterpret_cast<const unsigned char*>(data.c_str());

	unsigned long sdbmHash = formattedSdbmHash(formattedData);

	std::string hashedData;
	std::stringstream sstream;
	
	sstream << sdbmHash;
	sstream >> hashedData;

	return hashedData;
}


unsigned long formattedSdbmHash(const unsigned char *data)
{
	int index;
	unsigned long hash = 0;
	
	while((index = *data++))
	{
		hash = index + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

#endif
