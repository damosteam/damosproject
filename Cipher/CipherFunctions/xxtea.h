
#ifndef XXTEA_ENCRYPTION_H
#define XXTEA_ENCRYPTION_H

#define XXTEA_BLOCK_SIZE 8

#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))

#include <stdlib.h>
#include <string.h>

#include <sstream>

#include "../header.h"

extern uint32_t mXxteaKey[4]; 

void xxteaEncrypt(char* data, int dataLength, bool encrypt);
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
