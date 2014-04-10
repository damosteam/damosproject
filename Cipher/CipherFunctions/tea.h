
#ifndef TEA_ENCRYPTION_H
#define TEA_ENCRYPTION_H

#define TEA_BLOCK_SIZE 8

#include <stdlib.h>
#include <string.h>

#include "../header.h"

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
