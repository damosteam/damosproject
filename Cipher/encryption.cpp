
#ifndef ENCRYPTION_CPP
#define ENCRYPTION_CPP

#include "encryption.h"
#include "linkedList.cpp"

using namespace std;

int encryptFile(string currentFilename, LinkedList<string> &blacklistedFiles, LinkedList<string> &blacklistedExtensions)
{
	println("Encrypting/decrypting file \"" + currentFilename + "\" now...");

	int errorCount = 0;

	if(isBlacklistedFile(blacklistedFiles, currentFilename) == true)
	{
		println("File \"" + currentFilename + "\" is blacklisted. Skipping...");

		return errorCount;
	}
	else if(isBlacklistedExtension(blacklistedExtensions, currentFilename) == true)
	{
		if(mWhitelistModeEnabled == false)
		{
			println("Extension of file \"" + currentFilename + "\" is blacklisted. Skipping...");

			return errorCount;
		}
	}
	else if(isBlacklistedExtension(blacklistedExtensions, currentFilename) == false)
	{
		if(mWhitelistModeEnabled == true)
		{
			println("Extension of file \"" + currentFilename + "\" isn't whitelisted. Skipping...");

			return errorCount;
		}
	}

	string encryptionKey = CONFIGURATION_ENCRYPTION_KEY;

	ifstream currentFile(currentFilename.c_str());

	string outputFilename = (currentFilename + "_tmp");
	ofstream encryptedOutput(("~" + currentFilename).c_str());
		
	if(currentFile.is_open() == true)
	{ 
		if(isFileEmpty(currentFile))
		{
			currentFile.close();
			encryptedOutput.close();

			println("File \"" + currentFilename + "\" is empty. Skipping now...");
		}
		else if(encryptedOutput.is_open() == true)
		{
			encryptStream(encryptionKey, currentFile, encryptedOutput);

			currentFile.close();
			encryptedOutput.close();
					
			println("File \"" + currentFilename + "\" encrypted/decrypted successfully.");
			println("Output sent to file \"" + outputFilename + "\".");
					
			println("Deleting old copy of file now.");
					
			if(removeFile(currentFilename) == false)
			{
				errorCount++;
			}
			else
			{
				println("Old copy of file successfully deleted.");
				println("Renaming encrypted/decrypted file to original filename.");
						
				if(renameFile(outputFilename, currentFilename) == false)
				{
					errorCount++;
				}
			}
		}
		else
		{
			println("Unable to create a temporary file \"" + outputFilename + "\" for output. Aborting...");
					
			errorCount++;
		}
	}
	else
	{
		println("Unable to open file \"" + currentFilename + "\" for encryption/decryption. Aborting...");
				
		errorCount++;
	}

	cout << "Done encrypting/decrypting file." << endl;
	cout << "Process completed with: " << errorCount << " encryption/decryption errors." << endl;
	
	return errorCount;
}


int encryptConfigurationFiles(LinkedList<string> &blacklistedFiles, LinkedList<string> &blacklistedExtensions)
{
	println("Preparing to encrypt/decrypt configuration files now.");

	int errorCount = 0;

	errorCount += encryptFile(ENCRYPTION_KEY_FILENAME, blacklistedFiles, blacklistedExtensions);
	errorCount += encryptFile(BLACKLIST_FILENAME, blacklistedFiles, blacklistedExtensions);
	errorCount += encryptFile(EXTENSIONS_BLACKLIST_FILENAME, blacklistedFiles, blacklistedExtensions);

	println("Done encrypting/decrypting configuration files.");
	
	print("Process completed with: ");
	print(errorCount);
	println(" encryption/decryption errors.");
	
	return errorCount;
}


int encryptAllInDirectory(string &encryptionKey, LinkedList<string> &blacklistedFiles, LinkedList<string> &blacklistedExtensions)
{
	cout << "Preparing to encrypt/decrypt current directory now." << endl;
	
	int errorCount = 0;
	
	LinkedList<string> directoryFilenames = LinkedList<string>();

	if(getAllFilesInDirectory(directoryFilenames) == false)
	{
		return 0;
	}

	for(int j = 0; j < directoryFilenames.getCount(); j++)
	{
		string currentFilename = directoryFilenames.getData(j); 

		if(isBlacklistedFile(blacklistedFiles, currentFilename) == true)
		{
			println("File \"" + currentFilename + "\" is blacklisted. Skipping...");

			continue;
		}
		else if(isBlacklistedExtension(blacklistedExtensions, currentFilename) == true)
		{
			if(mWhitelistModeEnabled == false)
			{
				println("Extension of file \"" + currentFilename + "\" is blacklisted. Skipping...");

				continue;
			}
		}
		else if(isBlacklistedExtension(blacklistedExtensions, currentFilename) == false)
		{
			if(mWhitelistModeEnabled == true)
			{
				println("Extension of file \"" + currentFilename + "\" isn't whitelisted. Skipping...");

				continue;
			}
		}

		println("Encrypting/decrypting file \"" + currentFilename + "\" now...");
		ifstream currentFile(currentFilename.c_str());

		string outputFilename = (currentFilename + "_tmp");
		ofstream encryptedOutput(outputFilename.c_str());
			
		if(currentFile.is_open() == true)
		{ 
			if(isFileEmpty(currentFile))
			{
				currentFile.close();
				encryptedOutput.close();

				println("File \"" + currentFilename + "\" is empty. Skipping now...");

				continue;
			}
			else if(encryptedOutput.is_open() == true)
			{
				encryptStream(encryptionKey, currentFile, encryptedOutput);
			
				currentFile.close();
				encryptedOutput.close();
					
				println("File \"" + currentFilename + "\" encrypted/decrypted successfully.");
				println("Output sent to file \"" + outputFilename + "\".");
					
				println("Deleting old copy of file now.");
					
				if(removeFile(currentFilename) == false)
				{
					errorCount++;
					
					continue;
				}
				else
				{
					println("Old copy of file successfully deleted.");
					println("Renaming encrypted/decrypted file to original filename.");
						
					if(renameFile(outputFilename, currentFilename) == false)
					{
						errorCount++;
					}
				}
			}
			else
			{
				println("Unable to create a temporary file \"" + outputFilename + "\" for output. Aborting...");
					
				errorCount++;
					
				continue;
			}
		}
		else
		{
			println("Unable to open file \"" + currentFilename + "\" for encryption/decryption. Aborting...");
				
			errorCount++;
				
			continue;
		}
	}
	
	cout << "Done encrypting/decrypting current directory." << endl;
	cout << "Process completed with: " << errorCount << " encryption/decryption errors." << endl;
	
	return errorCount;
}

void encryptArgument(string &encryptionKey, string &rawText, string &processedText)
{
	if(mCipherType == "xor")
	{
		xorEncryptArgument(encryptionKey, rawText, processedText);
	}
	else if(mCipherType == "tea")
	{
		teaEncryptArgument(encryptionKey, rawText, processedText);
	}
	else if(mCipherType == "xtea")
	{
		xteaEncryptArgument(encryptionKey, rawText, processedText);
	}
	else if(mCipherType == "xxtea")
	{
		xxteaEncryptArgument(encryptionKey, rawText, processedText);
	}
}


void encryptStream(string &encryptionKey, ifstream &currentFile, ofstream &encryptedOutput)
{
	if(mCipherType == "xor")
	{
		xorEncryptStream(encryptionKey, currentFile, encryptedOutput);
	}
	else if(mCipherType == "tea")
	{
		teaEncryptStream(encryptionKey, currentFile, encryptedOutput);
	}
	else if(mCipherType == "xtea")
	{
		xteaEncryptStream(encryptionKey, currentFile, encryptedOutput);
	}
	else if(mCipherType == "xxtea")
	{
		xxteaEncryptStream(encryptionKey, currentFile, encryptedOutput);
	}
}

#endif
