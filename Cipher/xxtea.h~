
/**  Project LOE also supports the XXTEA block cipher, which is described as the following (from 
  *  Wikipedia):
  *  	In cryptography, Corrected Block TEA (often referred to as XXTEA) is a block cipher designed to 
  *	correct weaknesses in the original Block TEA.
  *
  *	XXTEA is vulnerable to a chosen-plaintext attack requiring 259 queries and negligible work. See 
  *	cryptanalysis below.
  *
  *	The cipher's designers were Roger Needham and David Wheeler of the Cambridge Computer  
  *	Laboratory, and the algorithm was presented in an unpublished technical report in October 1998  
  *	(Wheeler and Needham, 1998). It is not subject to any patents.
  *
  *	Formally speaking, XXTEA is a consistent incomplete source-heavy heterogeneous UFN (unbalanced 
  *	Feistel network) block cipher. XXTEA operates on variable-length blocks that are some arbitrary  
  *	multiple of 32 bits in size (minimum 64 bits). The number of full cycles depends on the block 
  *	size, but there are at least six (rising to 32 for small block sizes). The original Block TEA 
  *	applies the XTEA round function to each word in the block and combines it additively with its 
  *	leftmost neighbour. Slow diffusion rate of the decryption process was immediately exploited to 
  *	break the cipher. Corrected Block TEA uses a more involved round function which makes use of   
  *	both immediate neighbours in processing each word in the block.
  *
  *	XXTEA is likely to be more efficient than XTEA for longer messages.
  *
  *	Needham & Wheeler make the following comments on the use of Block TEA:
  *
  *     For ease of use and general security the large block version is to be preferred when applicable 
  *	for the following reasons.
  *
  *	1.) A single bit change will change about one half of the bits of the entire block, leaving no 
  *	place where the changes start.
  *	2.) There is no choice of mode involved.
  *	3.) Even if the correct usage of always changing the data sent (possibly by a message number) is 
  *	employed, only identical messages give the same result and the information leakage is minimal.
  *	4.) The message number should always be checked as this redundancy is the check against a random 
  *	message being accepted.
  *	5.) Cut and join attacks do not appear to be possible.
  *	6.) If it is not acceptable to have very long messages, they can be broken into chunks say of 60 
  *	words and chained analogously to the methods used for DES.
  *
  *	However, due to the incomplete nature of the round function, two large ciphertexts of 53 or more 
  *	32-bit words identical in all but 12 words can be found by a simple brute-force collision search 
  *	requiring 296−N memory, 2N time and 2N+296−N chosen plaintexts, in other words with a total 
  *	time*memory complexity of 296, which is actually 2wordsize*fullcycles/2 for any such cipher. It 
  *	is currently unknown if such partial collisions pose any threat to the security of the cipher. 
  *	Eight full cycles would raise the bar for such collision search above complexity of parallel 
  *	brute-force attacks.
  *
  *	The unusually small size of the XXTEA algorithm would make it a viable option in situations 
  *	where there are extreme constraints e.g. legacy hardware systems (perhaps embedded) where the 
  *	amount of available RAM is minimal.
  */

#ifndef XXTEA_ENCRYPTION_H
#define XXTEA_ENCRYPTION_H

#define XXTEA_BLOCK_SIZE 8

#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))

#include <stdlib.h>
#include <string.h>

#include <sstream>

#include "header.h"

extern uint32_t mXxteaKey[4]; 

void xxteaEncrypt(char* data, int dataLength, bool encrypt);
//void charToBinaryString(char &character, std::string &binaryString);
//void binaryStringToChar(std::string &binaryString, char &character);
void xxteaEncryptString(std::string &rawText, std::string &encryptedText);
void xxteaDecryptString(std::string &rawText, std::string &decryptedText);
void xxteaEncryptBlock(uint32_t v[2], int numberOfWords, uint32_t const key[4]);
void xxteaDecryptBlock(uint32_t v[2], int numberOfWords, uint32_t const key[4]);
void xxteaEncryptArgument(string &encryptionKey, string &rawText, string &processedText);
void xxteaDecryptArgument(string &encryptionKey, string &rawText, string &processedText);
void xxteaEncryptStream(string &encryptionKey, ifstream &currentFile, ofstream &encryptedOutput);
void xxteaDecryptStream(string &encryptionKey, ifstream &currentFile, ofstream &decryptedOutput);

template <typename T1, typename T2>
T1 lexicalCast(const T2 &data);

#endif
