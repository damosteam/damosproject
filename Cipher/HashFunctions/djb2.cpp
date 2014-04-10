
#ifndef DJB2_CPP
#define DJB2_CPP

#include "djb2.h"

string djb2Hash(string data)
{
	const unsigned char* formattedData = reinterpret_cast<const unsigned char*>(data.c_str());

	unsigned long djb2Hash = formattedDjb2Hash(formattedData);

	std::string hashedData;
	std::stringstream sstream;
	
	sstream << djb2Hash;
	sstream >> hashedData;

	return hashedData;
}


unsigned long formattedDjb2Hash(const unsigned char *data)
{
	int index;
	unsigned long djb2Hash = 5381;

	while((index = *data++))
	{
		djb2Hash = ((djb2Hash << 5) + djb2Hash) + index; 
	}

	return djb2Hash;
}

#endif
