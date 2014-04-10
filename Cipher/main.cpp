/*  Low Overhead Encryption (Project LOE)
 *  Author: Daniel Puckowski
 *
 *  Project LOE makes use of a XOR cipher, which is described as the following (from Wikipedia):
 *	In cryptography, the simple XOR cipher is a type of additive cipher, an encryption algorithm that operates according to the principles:
 *		A ^ 0 = A,
 *		A ^ A = 0,
 *		(A ^ B) ^ C = A ^ (B ^ C),
 *		(B ^ A) ^ A = B ^ 0 = B,
 *	where ^ denotes the exclusive disjunction (XOR) operation. This operation is sometimes called modulus 2 addition 
 *	(or subtraction, which is identical). With this logic, a string of text can be encrypted by applying the bitwise 
 *	XOR operator to every character using a given key. To decrypt the output, merely reapplying the XOR 
 *	function with the key will remove the cipher.

 *  Date (last edit): 04/13/2014
 *  Source code version: 0.0.3.6 
 *  Uses only standard C++ libraries (with dirent.h as an exception, however, the dirent.h implementation used is
 *  platform independent) and supports command-line use only.
 */

#include <iostream>

#include "header.h"
#include "stdlib.h"

using namespace std;

int main(int argc, char *argv[])
{
	if(argc > 1)
	{
		run(argc, argv);
	}
	else if(argc == 1)
	{
		run();
	}

	return EXIT_SUCCESS;
}
