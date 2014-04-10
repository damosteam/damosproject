
#ifndef XTEA_ENCRYPTION_H
#define XTEA_ENCRYPTION_H

#define XTEA_BLOCK_SIZE 8

#include <stdlib.h>
#include <string.h>

#include <sstream>

#include "../header.h"

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
