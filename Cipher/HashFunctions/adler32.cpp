
#ifndef ADLER32_CPP
#define ADLER32_CPP

#include "adler32.h"

uint32_t adler32Hash(const void *data, size_t sizeOfData)
{
	const uint8_t *buffer = (const uint8_t*) data;

	uint32_t k1 = 1;
	uint32_t k2 = 0;

	for(size_t n = 0; n < sizeOfData; n++)
	{
		k1 = (k1 + buffer[n]) % 65521;
		k2 = (k2 + k1) % 65521;
	}

	return (k2 << 16) | k1;
}

#endif
