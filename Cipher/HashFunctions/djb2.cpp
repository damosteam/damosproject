
#ifndef DJB2_CPP
#define DJB2_CPP

#include "djb2.h"

unsigned long mDjb2HashKey = 5381;

unsigned long djb2Hash(unsigned char *data)
{
	int index;

	while((index = *data++))
	{
		mDjb2HashKey = ((mDjb2HashKey << 5) + mDjb2HashKey) + index; 
	}

	return mDjb2HashKey;
}

#endif
