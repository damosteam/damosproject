
/**  Project LOE also supports the TEA block cipher, which is described as the following (from Wikipedia):
  *  	In cryptography, the Tiny Encryption Algorithm (TEA) is a block cipher notable for its simplicity of description and implementation,  
  *	typically a few lines of code. It was designed by David Wheeler and Roger Needham of the Cambridge Computer Laboratory; it was first presented
  *     at the Fast Software Encryption workshop in Leuven in 1994, and first published in the proceedings of that workshop.
  *     The cipher is not subject to any patents.
  */

#ifndef TEA_ENCRYPTION_H
#define TEA_ENCRYPTION_H

#define TEA_BLOCK_SIZE 8

#include <stdlib.h>
#include <string.h>

#include "header.h"

using namespace std;

const  uint32_t TEA_ENCRYPTION_ROUNDS = 32; 

extern uint32_t mTeaKey[4]; 

void teaEncryptBlock(uint32_t* v, uint32_t* k);
void teaDecryptBlock(uint32_t* v, uint32_t* k);
void teaEncrypt(char* data, int dataLength, bool encrypt);
void teaEncryptString(std::string &rawText, std::string &encryptedText);
void teaDecryptString(std::string &rawText, std::string &decryptedText);
void teaEncryptArgument(string &encryptionKey, string &rawText, string &processedText);
void teaDecryptArgument(string &encryptionKey, string &rawText, string &processedText);
void teaEncryptStream(string &encryptionKey, ifstream &currentFile, ofstream &encryptedOutput);
void teaDecryptStream(string &encryptionKey, ifstream &currentFile, ofstream &decryptedOutput);

#endif
