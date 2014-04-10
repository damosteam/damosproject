
#ifndef TEA_ENCRYPTION_CPP
#define TEA_ENCRYPTION_CPP

#include "tea.h"

using namespace std;

uint32_t mTeaKey[4] =
{
	0xFDA5,
	0xD54E,
	0xFC00,
	0xB55A
}; 


void teaEncryptBlock(uint32_t* v, uint32_t* k) 
{
	uint32_t v0 = v[0], v1 = v[1], sum = 0, i;          
    	uint32_t delta = 0x9e3779b9;                  
    	uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3]; 
    	
	for(i = 0; i < TEA_ENCRYPTION_ROUNDS; i++) 
	{                     
        	sum += delta;
        	v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        	v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    	} 
                                          
    	v[0] = v0; v[1] = v1;
}
 

void teaDecryptBlock(uint32_t* v, uint32_t* k) 
{
	uint32_t v0 = v[0], v1 = v[1], sum = 0xC6EF3720, i;  
    	uint32_t delta = 0x9e3779b9;                     
    	uint32_t k0 = k[0], k1 = k[1], k2 = k[2], k3 = k[3];  
    
	for(i = 0; i < TEA_ENCRYPTION_ROUNDS; i++) 
	{                      
        	v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        	v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        	sum -= delta;
    	}
                                              
    	v[0] = v0; v[1] = v1;
}


void teaEncrypt(char* data, int dataLength, bool encrypt)
{
	for(int i = 0; i < (dataLength / TEA_BLOCK_SIZE); i++)
    	{
		if(encrypt == true)
		{
			teaEncryptBlock((uint32_t*)(data + (i * TEA_BLOCK_SIZE)), mTeaKey);
		}
       		else if(encrypt == false)
		{
			teaDecryptBlock((uint32_t*)(data + (i * TEA_BLOCK_SIZE)), mTeaKey);
		}
    	}
}


void teaEncryptString(std::string &rawText, std::string &encryptedText)
{
	char* processedText;

	for(uint32_t i = 0; i < rawText.length(); i++)
	{
		std::string binaryString;
		charToBinaryString(rawText[i], binaryString);

		processedText = strdup(binaryString.c_str());
		teaEncrypt(processedText, 9, true); 

		encryptedText += std::string(processedText, 8);

		//free(processedText);
	}
}


void teaDecryptString(std::string &rawText, std::string &decryptedText)
{
	char* processedText;

	while(rawText.length() > 0)	
	{
		std::string nextBlock = rawText.substr(0, 8);
		processedText = &nextBlock[0]; 

		teaEncrypt(processedText, 9, false);

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


void teaEncryptArgument(string &encryptionKey, string &rawText, string &processedText)
{
	teaEncryptString(rawText, processedText);
}


void teaEncryptStream(string &encryptionKey, ifstream &currentFile, ofstream &encryptedOutput)
{
	char currentChar;
	string encryptedText;
	string temp;

        int count = 0;

	while(currentFile.get(currentChar)) 
	{
		count++;

		temp = string(1, currentChar);

		teaEncryptString(temp, encryptedText);
		temp ="";

		encryptedOutput << encryptedText;
		encryptedText = "";
	}
}


void teaDecryptArgument(string &encryptionKey, string &rawText, string &processedText)
{
	teaDecryptString(rawText, processedText);
}


void teaDecryptStream(string &encryptionKey, ifstream &currentFile, ofstream &decryptedOutput)
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
			teaDecryptString(temp, decryptedText);
			temp = "";

			decryptedOutput << decryptedText;
			decryptedText = "";
		}
	}
}

#endif
