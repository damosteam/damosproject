
/**  Project LOE also supports the XTEA block cipher, which is described as the following (from 
  *  Wikipedia):
  *  	In cryptography, XTEA (eXtended TEA) is a block cipher designed to correct weaknesses in TEA. 
  *	The cipher's designers were David Wheeler and Roger Needham of the Cambridge Computer 
  *	Laboratory, and the algorithm was presented in an unpublished technical report in 1997 (Needham 
  *	and Wheeler, 1997). It is not subject to any patents. Like TEA, XTEA is a 64-bit block Feistel 
  *	network with a 128-bit key and a suggested 64 rounds. Several differences from TEA are apparent, 
  *	including a somewhat more complex key-schedule and a rearrangement of the shifts, XORs, and 
  *	additions.
  *
  *     Presented along with XTEA was a variable-width block cipher termed Block TEA, which uses the 
  *	XTEA round function, but Block TEA applies it cyclically across an entire message for several   
  *	iterations. Because it operates on the entire message, Block TEA has the property that it does 
  *	not need a mode of operation. An attack on the full Block TEA was described in (Saarinen, 1998),
  *     which also details a weakness in Block TEA's successor, XXTEA.
  */

#ifndef XTEA_ENCRYPTION_H
#define XTEA_ENCRYPTION_H

#define XTEA_BLOCK_SIZE 8

#include <stdlib.h>
#include <string.h>

#include <sstream>

#include "header.h"

/**  The recommended value for ENCRYPTION_ROUNDS is 32. Each iteration of the XTEA encipher loop 
  *  performs two Feistel-network rounds. This provides the suggested 64 rounds.
  */
const  uint32_t XTEA_ENCRYPTION_ROUNDS = 32; 

extern uint32_t mXteaKey[4]; 

void xteaEncrypt(char* data, int dataLength, bool encrypt);
void xteaEncryptBlock(uint32_t v[2], uint32_t const key[4]);
void xteaDecryptBlock(uint32_t v[2], uint32_t const key[4]);
void charToBinaryString(char &character, std::string &binaryString);
void binaryStringToChar(std::string &binaryString, char &character);
void xteaEncryptString(std::string &rawText, std::string &encryptedText);
void xteaDecryptString(std::string &rawText, std::string &decryptedText);
void xteaEncryptArgument(string &encryptionKey, string &rawText, string &processedText);
void xteaDecryptArgument(string &encryptionKey, string &rawText, string &processedText);
void xteaEncryptStream(string &encryptionKey, ifstream &currentFile, ofstream &encryptedOutput);
void xteaDecryptStream(string &encryptionKey, ifstream &currentFile, ofstream &decryptedOutput);

template <typename T1, typename T2>
T1 lexicalCast(const T2 &data);

#endif
