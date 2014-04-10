
#ifndef SDBM_CPP
#define SDBM_CPP

#include "sdbm.h"

unsigned long sbdmHash(unsigned char *data)
{
	int           index;
	unsigned long hash = 0;
	
	while((index = *data++))
	{
		hash = index + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

#endif
