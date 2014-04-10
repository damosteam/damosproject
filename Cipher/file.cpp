
#ifndef FILE_CPP
#define FILE_CPP

#include "file.h"
#include "linkedList.cpp"

using namespace std;

string readEncryptionKey(string &keyFilename, bool suppressOutput)
{
	string   encryptionKey = "";
	ifstream encryptionKeyFile(keyFilename.c_str());
	
	if(encryptionKeyFile.is_open() == true)
	{
		getline(encryptionKeyFile, encryptionKey);
    
		encryptionKeyFile.close();
		
		if(suppressOutput == false)
		{
			cout << "Existing encryption key read from file \"" + keyFilename + "\" successfully." << endl;
		}
	}
	else
	{
		if(suppressOutput == false)
		{
			cout << "Unable to open/find encryption key file with name of \"" + keyFilename + "\" to read existing key. Aborting..." << endl;
		}
	}
	
	return encryptionKey;
}


void setNewEncryptionKey(string &keyFilename)
{
	cout << "Please enter a new encryption key: ";
	
	string   encryptionKey = "";
	ofstream encryptionKeyFile(keyFilename.c_str());

	getline(cin, encryptionKey);
	
	if(encryptionKeyFile.is_open() == true)
	{
		encryptionKeyFile << encryptionKey << endl;
		
		encryptionKeyFile.close();
		
		cout << "New encryption key saved to file \"" + keyFilename + "\" successfully." << endl;
	}
	else
	{
		cout << "Unable to open/find encryption key file with name of \"" + keyFilename + "\" to save new key. Aborting..." << endl;
	}
}


bool isFileEmpty(ifstream &file)
{
    return (file.peek() == ifstream::traits_type::eof());
}


bool renameFile(string &currentName, string &targetName)
{
	if(rename(currentName.c_str(), targetName.c_str()) != 0)
	{
		println("Unable to rename file \"" + currentName + "\".");
		println("Please rename the file manually from");
		println("\"" + currentName + "\" to \"" + targetName + "\".");
						
		return false;
	}
	else
	{
		println("Renaming of file \"" + currentName + "\" was successful.");

		return true;
	}
}


bool removeFile(string &filename)
{
	if(remove(filename.c_str()) != 0)
	{
		println("Unable to delete file \"" + filename + "\".");
		println("Please remove the file manually, then rename the file");
		println("\"" + filename + "\"_tmp to \"" + filename + "\".");
						
		return false;
	}
	else
	{
		println("File \"" + filename + "\"_tmp was removed successfully.");

		return true;
	}
}


bool getAllFilesInDirectory(LinkedList<string> &directoryFilenames)
{
	DIR           *directoryPath;
	struct dirent *directoryContent;
	
	println("Attempting to open current directory to read contents.");
	directoryPath = opendir("./");
	
	if(directoryPath != NULL)
	{
		println("Reading directory contents now.");
		
		while((directoryContent = readdir(directoryPath)))
		{
			if(directoryContent->d_name == NULL)
			{
				continue;
			}

			directoryFilenames.insert(directoryContent->d_name);
		}
	}
	else
	{
		cout << "An error was encountered. Program could not open current directory to get list of files. Aborting..." << endl;
		
		closedir(directoryPath);

		return false;
	}

	closedir(directoryPath);

	return true;
}


bool readBlacklistFile(LinkedList<string> &blacklistedFiles, bool suppressOutput)
{
	string   line = "";
	ifstream blacklistFile(BLACKLIST_FILENAME.c_str());
	
	if(blacklistFile.is_open() == true)
	{
		while(getline(blacklistFile, line))
		{
			if(line.empty() == false)
			{
				blacklistedFiles.insert(line);
			}
		}

		blacklistFile.close();
		
		if(suppressOutput == false)
		{
			cout << "Blacklisted files read from \"" + BLACKLIST_FILENAME + "\" successfully." << endl;
		}
	}
	else
	{
		if(suppressOutput == false)
		{
			cout << "Unable to open/find blacklist file with name of \"" + BLACKLIST_FILENAME + "\" to blacklist files. Aborting..." << endl;
		}

		return false;
	}

	return true;
}


bool readExtensionsBlacklistFile(LinkedList<string> &blacklistedExtensions, bool suppressOutput)
{
	string   line = "";
	ifstream blacklistExtensionsFile(EXTENSIONS_BLACKLIST_FILENAME.c_str());
	
	if(blacklistExtensionsFile.is_open() == true)
	{
		while(getline(blacklistExtensionsFile, line))
		{
			if(line.empty() == false)
			{
				blacklistedExtensions.insert(line);
			}
		}

		blacklistExtensionsFile.close();
		
		if(suppressOutput == false)
		{
			cout << "Blacklisted extensions read from \"" + EXTENSIONS_BLACKLIST_FILENAME + "\" successfully." << endl;
		}
	}
	else
	{
		if(suppressOutput == false)
		{
			cout << "Unable to open/find extensions blacklist file with name of \"" + EXTENSIONS_BLACKLIST_FILENAME + "\" to blacklist extensions. Aborting..." << endl;
		}

		return false;
	}

	return true;
}


bool stringEndsWith(string &fullString, string &ending)
{
    if(fullString.length() >= ending.length()) 
	{
        return (0 == fullString.compare((fullString.length() - ending.length()), ending.length(), ending));
    } 
	else 
	{
        return false;
    }
}


void loadEncryptionArgument(string &argument)
{	
	ifstream currentFile(TEMPORARY_FILENAME.c_str());
	char     currentChar;

	argument = "";

	if(currentFile.is_open() == true)
	{ 
		if(isFileEmpty(currentFile))
		{
			currentFile.close();
		}
		else
		{
			while(currentFile.get(currentChar)) 
			{
				argument += string(1, currentChar);
			}
		}
	}

	currentFile.close();
}


void saveEncryptionArgument(string &argument)
{	
	ofstream currentFile(TEMPORARY_FILENAME.c_str());

	if(currentFile.is_open() == true)
	{ 
		for(unsigned int i = 0; i < argument.length(); i++)
		{
			currentFile << argument[i];
		}
	}

	currentFile.close();
}


void readTeaEncryptionKey(string &keyFilename, uint32_t teaKey[4], bool suppressOutput)
{
	ifstream encryptionKeyFile(keyFilename.c_str());
	
	if(encryptionKeyFile.is_open() == true)
	{
		string keyPart;
		
		getline(encryptionKeyFile, keyPart);   		
		teaKey[0] = lexicalCast<uint32_t>(keyPart);
		
		getline(encryptionKeyFile, keyPart);    		
		teaKey[1] = lexicalCast<uint32_t>(keyPart);

		getline(encryptionKeyFile, keyPart);    		
		teaKey[2] = lexicalCast<uint32_t>(keyPart);

		getline(encryptionKeyFile, keyPart);    		
		teaKey[3] = lexicalCast<uint32_t>(keyPart);

		encryptionKeyFile.close();
		
		if(suppressOutput == false)
		{
			cout << "Existing encryption key read from file \"" + keyFilename + "\" successfully." << endl;
		}
	}
	else
	{
		if(suppressOutput == false)
		{
			cout << "Unable to open/find encryption key file with name of \"" + keyFilename + "\" to read existing key. Aborting..." << endl;
		}
	}
}

#endif
