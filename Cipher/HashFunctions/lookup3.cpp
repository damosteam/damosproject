
#ifndef LOOKUP3_CPP
#define LOOKUP3_CPP

#include "lookup3.h"

uint32_t lookup3Hash(const uint32_t *key, size_t length, uint32_t initval) 
{
	uint32_t  a, b, c;
  	const uint8_t  *k;
  	const uint32_t *data32Bit;

  	data32Bit = key;
  	a = b = c = 0xabcdabcd + (((uint32_t)length)<<2) + initval;

  	while(length > 12) 
	{
    		a += *(data32Bit++);
    		b += *(data32Bit++);
    		c += *(data32Bit++);
    
		mix(a,b,c);

	    	length -= 12;
  	}

  	k = (const uint8_t*) data32Bit;

  	switch(length) 
	{
    		case 12: c += ((uint32_t)k[11])<<24;
    		case 11: c += ((uint32_t)k[10])<<16;
    		case 10: c += ((uint32_t)k[9])<<8;
    		case 9 : c += k[8];
    		case 8 : b += ((uint32_t)k[7])<<24;
    		case 7 : b += ((uint32_t)k[6])<<16;
    		case 6 : b += ((uint32_t)k[5])<<8;
    		case 5 : b += k[4];
    		case 4 : a += ((uint32_t)k[3])<<24;
    		case 3 : a += ((uint32_t)k[2])<<16;
    		case 2 : a += ((uint32_t)k[1])<<8;
    		case 1 : a += k[0];
             		break;
    		case 0 : return c;
  	}
  
	final(a, b, c);
  		
	return c;
}

#endif
