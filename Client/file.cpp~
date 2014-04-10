
#ifndef FILE_CPP
#define FILE_CPP

#include "file.h"

const char* CLIENT_ID_FILENAME = "localid.txt";

std::string mClientID;

bool isFileExist(const char *filename) 
{
	struct stat buffer;   
	return (stat(filename, &buffer) == 0); 
}


int createClientIDFile()
{
	std::ofstream idFile;
	idFile.open(CLIENT_ID_FILENAME);

	struct stat buffer; 

	if(idFile.is_open())
	{
		idFile << &buffer << std::endl;
		idFile.close();
	}
	else
	{
		return -1;
	}
	
	return 0;
}


int readClientIDFile()
{
	std::ifstream idFile;
	idFile.open(CLIENT_ID_FILENAME);

	std::string tempID;

	if(idFile.is_open())
	{
		getline(idFile, tempID);
		idFile.close();

		//mClientID = strdup(tempID.c_str());
		mClientID = tempID;
	}
	else
	{
		return -1;
	}

	return 0;
}

#endif
