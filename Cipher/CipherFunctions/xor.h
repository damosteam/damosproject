
#ifndef XOR_H
#define XOR_H

#include "../header.h"

using namespace std;

void xorEncryptArgument(string &encryptionKey, string &rawText, string &processedText);
void xorEncryptStream(string &encryptionKey, ifstream &currentFile, ofstream &encryptedOutput);

void xorDecryptArgument(string &encryptionKey, string &rawText, string &processedText);
void xorDecryptStream(string &encryptionKey, ifstream &currentFile, ofstream &decryptedOutput);

#endif
