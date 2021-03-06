
#ifndef DECRYPTION_CPP
#define DECRYPTION_CPP

#include "decryption.h"
#include "linkedList.cpp"

int decryptFile(string currentFilename, LinkedList<string> &blacklistedFiles, LinkedList<string> &blacklistedExtensions)
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
	ofstream decryptedOutput(("~" + currentFilename).c_str());

	if(currentFile.is_open() == true)
	{ 
		if(isFileEmpty(currentFile))
		{
			currentFile.close();
			decryptedOutput.close();

			println("File \"" + currentFilename + "\" is empty. Skipping now...");
		}
		else if(decryptedOutput.is_open() == true)
		{
			decryptStream(encryptionKey, currentFile, decryptedOutput);
			
			currentFile.close();
			decryptedOutput.close();
					
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


int decryptConfigurationFiles(LinkedList<string> &blacklistedFiles, LinkedList<string> &blacklistedExtensions)
{
	println("Preparing to encrypt/decrypt configuration files now.");

	int errorCount = 0;

	errorCount += decryptFile(ENCRYPTION_KEY_FILENAME, blacklistedFiles, blacklistedExtensions);
	errorCount += decryptFile(BLACKLIST_FILENAME, blacklistedFiles, blacklistedExtensions);
	errorCount += decryptFile(EXTENSIONS_BLACKLIST_FILENAME, blacklistedFiles, blacklistedExtensions);

	println("Done encrypting/decrypting configuration files.");
	
	print("Process completed with: ");
	print(errorCount);
	println(" encryption/decryption errors.");
	
	return errorCount;
}


int decryptAllInDirectory(string &encryptionKey, LinkedList<string> &blacklistedFiles, LinkedList<string> &blacklistedExtensions)
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
		ofstream decryptedOutput(outputFilename.c_str());
			
		if(currentFile.is_open() == true)
		{ 
			if(isFileEmpty(currentFile))
			{
				currentFile.close();
				decryptedOutput.close();

				println("File \"" + currentFilename + "\" is empty. Skipping now...");

				continue;
			}
			else if(decryptedOutput.is_open() == true)
			{
				decryptStream(encryptionKey, currentFile, decryptedOutput);
			
				currentFile.close();
				decryptedOutput.close();
					
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


void decryptArgument(string &encryptionKey, string &rawText, string &processedText)
{
	if(mCipherType == "xor")
	{
		xorDecryptArgument(encryptionKey, rawText, processedText);
	}
	else if(mCipherType == "tea")
	{
		teaDecryptArgument(encryptionKey, rawText, processedText);
	}
	else if(mCipherType == "xtea")
	{
		xteaDecryptArgument(encryptionKey, rawText, processedText);
	}
	else if(mCipherType == "xxtea")
	{
		xxteaDecryptArgument(encryptionKey, rawText, processedText);
	}
}


void decryptStream(string &encryptionKey, ifstream &currentFile, ofstream &decryptedOutput)
{
	if(mCipherType == "xor")
	{
		xorDecryptStream(encryptionKey, currentFile, decryptedOutput);
	}
	else if(mCipherType == "tea")
	{
		teaDecryptStream(encryptionKey, currentFile, decryptedOutput);
	}
	else if(mCipherType == "xtea")
	{
		xteaDecryptStream(encryptionKey, currentFile, decryptedOutput);
	}
	else if(mCipherType == "xxtea")
	{
		xxteaDecryptStream(encryptionKey, currentFile, decryptedOutput);
	}
}

#endif
