
#ifndef XTEA_ENCRYPTION_CPP
#define XTEA_ENCRYPTION_CPP

#include "xtea.h"

uint32_t mXteaKey[4] =
{
	0xFDA5,
	0xD54E,
	0xFC00,
	0xB55A
}; 


template <typename T1, typename T2>
T1 lexicalCast(const T2 &data)
{
	T1 convertedData;

	std::stringstream stringStream;
	stringStream << data;
	stringStream >> convertedData;

	return convertedData;
}

template uint32_t lexicalCast<uint32_t>(const std::string &data);


void xteaEncryptBlock(uint32_t v[2], uint32_t const key[4]) 
{
    	uint32_t v0 = v[0], v1 = v[1], sum = 0, delta = 0x9E3779B9;

    	for(uint32_t i = 0; i < XTEA_ENCRYPTION_ROUNDS; i++) 
	{
        	v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
        	sum += delta;
        	v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
    	}

    	v[0] = v0; v[1] = v1;
}


void xteaDecryptBlock(uint32_t v[2], uint32_t const key[4]) 
{
    	uint32_t v0 = v[0], v1 = v[1], delta = 0x9E3779B9, sum = (delta * XTEA_ENCRYPTION_ROUNDS);

    	for(uint32_t i = 0; i < XTEA_ENCRYPTION_ROUNDS; i++) 
	{
        	v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum>>11) & 3]);
        	sum -= delta;
        	v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
    	}

    	v[0] = v0; v[1] = v1;
}


void charToBinaryString(char &character, std::string &binaryString)
{
    	for(int i = 7; i >= 0; --i)
    	{
        	character & (1 << i) ? binaryString += "1" : binaryString += "0";
    	}
}


void binaryStringToChar(std::string &binaryString, char &character)
{
	character = strtol(binaryString.c_str(), 0, 2);
}


void xteaEncrypt(char* data, int dataLength, bool encrypt)
{
	for(int i = 0; i < (dataLength / XTEA_BLOCK_SIZE); i++)
    	{
		if(encrypt == true)
		{
			xteaEncryptBlock((uint32_t*)(data + (i * XTEA_BLOCK_SIZE)), mXteaKey);
		}
       		else if(encrypt == false)
		{
			xteaDecryptBlock((uint32_t*)(data + (i * XTEA_BLOCK_SIZE)), mXteaKey);
		}
    	}
}


void xteaEncryptString(std::string &rawText, std::string &encryptedText)
{
	char* processedText;

	for(uint32_t i = 0; i < rawText.length(); i++)
	{
		std::string binaryString;
		charToBinaryString(rawText[i], binaryString);

		processedText = strdup(binaryString.c_str());
		xteaEncrypt(processedText, 9, true); 

		encryptedText += std::string(processedText, 8);
		//free(processedText);
	}
}


void xteaDecryptString(std::string &rawText, std::string &decryptedText)
{
	char* processedText;

	while(rawText.length() > 0)	
	{
		std::string nextBlock = rawText.substr(0, 8);
		processedText = &nextBlock[0]; 

		xteaEncrypt(processedText, 9, false);

		std::string binaryString = std::string(processedText);
		//free(processedText);

		char decryptedValue;
		binaryStringToChar(binaryString, decryptedValue);

		decryptedText += decryptedValue;

		if(rawText.length() > 8)
		{
			rawText = rawText.substr(8, rawText.length());
		}
		else
		{
			break;
		}
	}
}


void xteaEncryptArgument(string &encryptionKey, string &rawText, string &processedText)
{
	xteaEncryptString(rawText, processedText);
}


void xteaEncryptStream(string &encryptionKey, ifstream &currentFile, ofstream &encryptedOutput)
{
	char currentChar;
	string encryptedText;
	string temp;

        int count = 0;

	while(currentFile.get(currentChar)) 
	{
		count++;

		temp = string(1, currentChar);

		xteaEncryptString(temp, encryptedText);
		temp ="";

		encryptedOutput << encryptedText;
		encryptedText = "";
	}
}


void xteaDecryptArgument(string &encryptionKey, string &rawText, string &processedText)
{
	xteaDecryptString(rawText, processedText);
}


void xteaDecryptStream(string &encryptionKey, ifstream &currentFile, ofstream &decryptedOutput)
{
	char currentChar;
	string decryptedText;
	string temp;

        int count = 0;

	while(currentFile.get(currentChar)) 
	{
		count++;

		temp = temp + string(1, currentChar);

		if(temp.length() == 8)
		{
			xteaDecryptString(temp, decryptedText);
			temp = "";

			decryptedOutput << decryptedText;
			decryptedText = "";
		}
	}
}

#endif
