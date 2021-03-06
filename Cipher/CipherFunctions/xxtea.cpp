
#ifndef XXTEA_ENCRYPTION_CPP
#define XXTEA_ENCRYPTION_CPP

#include "xxtea.h"

uint32_t mXxteaKey[4] =
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


void xxteaEncrypt(char* data, int dataLength, bool encrypt)
{
	for(int i = 0; i < (dataLength / XXTEA_BLOCK_SIZE); i++)
    	{
		if(encrypt == true)
		{
			xxteaEncryptBlock((uint32_t*)(data + (i * XXTEA_BLOCK_SIZE)), 2, mXxteaKey);
		}
       		else if(encrypt == false)
		{
			xxteaDecryptBlock((uint32_t*)(data + (i * XXTEA_BLOCK_SIZE)), -2, mXxteaKey);
		}
    	}
}


/** According to Needham and Wheeler:
  *
  * xxteaEncryptBlock will encode or decode n words as a single block where n > 1
  *
  *	-> v is the n word data vector
  *     -> k is the 4 word key
  *     -> n is negative for decoding
  *     -> if n is zero result is 1 and no coding or decoding takes place, otherwise the result is zero
  *     -> assumes 32 bit 'long' and same endian coding and decoding
  */
void xxteaEncryptBlock(uint32_t v[2], int numberOfWords, uint32_t const key[4])
{
	uint32_t y, z, sum;
    	unsigned p, rounds, e;

    	if(numberOfWords > 1) 
	{          
      		rounds = 6 + (52 / numberOfWords);
      		sum = 0;
      		z = v[(numberOfWords - 1)];
      		
		do 
		{
        		sum += DELTA;
        		e = (sum >> 2) & 3;
        
			for(p = 0; p < (numberOfWords - 1); p++) 
			{
          			y = v[(p + 1)]; 
          			z = v[p] += MX;
        		}

        		y = v[0];
        		z = v[(numberOfWords - 1)] += MX;
      		} while(--rounds);
	} 
	else if(numberOfWords < -1) 
	{  
      		numberOfWords = -numberOfWords;
      		rounds = 6 + (52 / numberOfWords);
      		sum = (rounds * DELTA);
      		y = v[0];
      
		do 
		{
        		e = (sum >> 2) & 3;
        
			for(p = (numberOfWords - 1); p > 0; p--) 
			{
          			z = v[(p - 1)];
          			y = v[p] -= MX;
        		}
        
			z = v[(numberOfWords - 1)];
		        y = v[0] -= MX;
		} while((sum -= DELTA) != 0);
	}
}


/** According to Needham and Wheeler:
  *
  * xxteaEncryptBlock will encode or decode n words as a single block where n > 1
  *
  *	-> v is the n word data vector
  *     -> k is the 4 word key
  *     -> n is negative for decoding
  *     -> if n is zero result is 1 and no coding or decoding takes place, otherwise the result is zero
  *     -> assumes 32 bit 'long' and same endian coding and decoding
  */
void xxteaDecryptBlock(uint32_t v[2], int numberOfWords, uint32_t const key[4])
{
	uint32_t y, z, sum;
    	unsigned p, rounds, e;

    	if(numberOfWords > 1) 
	{          
      		rounds = 6 + (52 / numberOfWords);
      		sum = 0;
      		z = v[(numberOfWords - 1)];
      		
		do 
		{
        		sum += DELTA;
        		e = (sum >> 2) & 3;
        
			for(p = 0; p < (numberOfWords - 1); p++) 
			{
          			y = v[(p + 1)]; 
          			z = v[p] += MX;
        		}

        		y = v[0];
        		z = v[(numberOfWords - 1)] += MX;
      		} while(--rounds);
	} 
	else if(numberOfWords < -1) 
	{  
      		numberOfWords = -numberOfWords;
      		rounds = 6 + (52 / numberOfWords);
      		sum = (rounds * DELTA);
      		y = v[0];
      
		do 
		{
        		e = (sum >> 2) & 3;
        
			for(p = (numberOfWords - 1); p > 0; p--) 
			{
          			z = v[(p - 1)];
          			y = v[p] -= MX;
        		}
        
			z = v[(numberOfWords - 1)];
		        y = v[0] -= MX;
		} while((sum -= DELTA) != 0);
	}
}


/**void charToBinaryString(char &character, std::string &binaryString)
{
	for(int i = 7; i >= 0; --i)
    	{
        	character & (1 << i) ? binaryString += "1" : binaryString += "0";
    	}
}


void binaryStringToChar(std::string &binaryString, char &character)
{
	character = strtol(binaryString.c_str(), 0, 2);
}*/


void xxteaEncryptString(std::string &rawText, std::string &encryptedText)
{
	char* processedText;

	for(uint32_t i = 0; i < rawText.length(); i++)
	{
		std::string binaryString;
		charToBinaryString(rawText[i], binaryString);

		processedText = strdup(binaryString.c_str());
		xxteaEncrypt(processedText, 9, true); 

		encryptedText += std::string(processedText, 8);
		//free(processedText);
	}
}


void xxteaDecryptString(std::string &rawText, std::string &decryptedText)
{
	char* processedText;

	while(rawText.length() > 0)	
	{
		std::string nextBlock = rawText.substr(0, 8);
		processedText = &nextBlock[0]; 

		xxteaEncrypt(processedText, 9, false); 

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


void xxteaEncryptArgument(string &encryptionKey, string &rawText, string &processedText)
{
	xxteaEncryptString(rawText, processedText);
}


void xxteaDecryptArgument(string &encryptionKey, string &rawText, string &processedText)
{
	xxteaDecryptString(rawText, processedText);
}


void xxteaEncryptStream(string &encryptionKey, ifstream &currentFile, ofstream &encryptedOutput)
{
	char currentChar;
	string encryptedText;
	string temp;

        int count = 0;

	while(currentFile.get(currentChar)) 
	{
		count++;

		temp = string(1, currentChar);

		xxteaEncryptString(temp, encryptedText);
		temp ="";

		encryptedOutput << encryptedText;
		encryptedText = "";
	}
}


void xxteaDecryptStream(string &encryptionKey, ifstream &currentFile, ofstream &decryptedOutput)
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
			xxteaDecryptString(temp, decryptedText);
			temp = "";

			decryptedOutput << decryptedText;
			decryptedText = "";
		}
	}
}

#endif
