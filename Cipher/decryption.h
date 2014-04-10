
#ifndef DECRYPTION_H
#define DECRYPTION_H

#include "header.h"

void decryptArgument(string &encryptionKey, string &rawText, string &processedText);
void decryptStream(string &encryptionKey, ifstream &currentFile, ofstream &decryptedOutput);

int decryptConfigurationFiles(LinkedList<string> &blacklistedFiles, LinkedList<string> &blacklistedExtensions);
int decryptFile(string currentFilename, LinkedList<string> &blacklistedFiles, LinkedList<string> &blacklistedExtensions);
int decryptAllInDirectory(string &encryptionKey, LinkedList<string> &blacklistedFiles, LinkedList<string> &blacklistedExtensions);

#endif
