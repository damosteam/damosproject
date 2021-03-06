
#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include "header.h"
#include "linkedList.cpp"

using namespace std;

string getEncryptionKeyFilename()
{
	cout << "Please enter the name of the encryption key file: ";
	
	string encryptionKeyFilename = "";
	getline(cin, encryptionKeyFilename);
	
	return encryptionKeyFilename;
}


bool isBlacklistedFile(LinkedList<string> &blacklistedFiles, string filename)
{
	bool blacklisted = false;

	for(int i = 0; i < blacklistedFiles.getCount(); i++)
	{
		if(blacklistedFiles.getData(i) == filename)
		{
			blacklisted = true;

			break;
		}
	}

	return blacklisted;
}


bool isBlacklistedExtension(LinkedList<string> &blacklistedExtensions, string filename)
{
	bool blacklisted = false;
	string currentExtension;

	for(int i = 0; i < blacklistedExtensions.getCount(); i++)
	{
		currentExtension = blacklistedExtensions.getData(i);

		if(stringEndsWith(filename, currentExtension))
		{
			blacklisted = true;

			break;
		}
	}

	return blacklisted;
}


void parseCommands(string &commandString, LinkedList<string> &commands)
{
	string commandWord = "";

	for(unsigned int i = 0; i < commandString.length(); i++)
	{
		if(commandString[i] == ' ')
		{
			commands.insert(commandWord);

			commandWord = "";
		}
		else 
		{
			commandWord += string(1, commandString[i]);
		}
	}

	commands.insert(commandWord);
}


bool processCommands(LinkedList<string> &commands, LinkedList<string> &blacklistedFiles, LinkedList<string> &blacklistedExtensions)
{
	if(commands.isEmpty() == true)
	{
		return true;
	}
	
	string encryptionKey = "";
	
	while(commands.getCount() > 0)
	{
		string currentCommand  = commands.getData(0);
		int removeCommandCount = 1;

		if(currentCommand == "exit")
		{
			cout << "Leaving advanced shell." << endl;

			commands.removeElementAt(0);

			return false;
		}
		else if(currentCommand == "help")
		{
			printCommandList();
		}
		else if(currentCommand == "-v")
		{
			mVerboseModeEnabled = true;
		}
		else if(currentCommand == "-w")
		{
			mWhitelistModeEnabled = true;
		}
		else if(currentCommand == "-ecf" || currentCommand == "-dcf")
		{
			encryptConfigurationFiles(blacklistedFiles, blacklistedExtensions);
		}
		else if(currentCommand == "-E")
		{
			encryptAllInDirectory(encryptionKey, blacklistedFiles, blacklistedExtensions);
		}
		else if(currentCommand == "-D")
		{
			decryptAllInDirectory(encryptionKey, blacklistedFiles, blacklistedExtensions);
		}
		else if(currentCommand == "-e")
		{
			string cipherText = "";

			if(commands.getCount() > 1)
			{
				string rawText      = commands.getData(1);
				int currentArgument = 2;

				removeCommandCount++;

				if(rawText.find("\"") != std::string::npos)
				{
					while(currentArgument < commands.getCount() 
						  && commands.getData(currentArgument).find("\"")  == std::string::npos)
					{
						rawText += " " + commands.getData(currentArgument);

						currentArgument++;
						removeCommandCount++;
					}

					if(currentArgument < commands.getCount())
					{
						rawText += " " + commands.getData(currentArgument);
						removeCommandCount++;
					}

					rawText = rawText.substr(1, (rawText.length() - 2));
				}

				encryptArgument(encryptionKey, rawText, cipherText);
				
				cout << "Ciphered." << endl;

				saveEncryptionArgument(cipherText);
				return true;
			}
			else
			{
				cout << "Program usage error encountered. Can not proceed. Aborting..." << endl;
				printProgramUsage();

				commands.removeElementAt(0);

				return false;
			}
		}
		else if(currentCommand == "-d")
		{
			string cipherText = "";

			if(commands.getCount() > 1)
			{
				string rawText = "";
				loadEncryptionArgument(rawText);

				remove(TEMPORARY_FILENAME.c_str());

				decryptArgument(encryptionKey, rawText, cipherText);

				cout << cipherText << endl;
			}
			else
			{
				cout << "Program usage error encountered. Can not proceed. Aborting..." << endl;
				printProgramUsage();

				commands.removeElementAt(0);

				return false;
			}
		}
		else if(currentCommand == "-c")
		{
			if(commands.getCount() > 1)
			{
				setCipherType(commands.getData(1));
			
				removeCommandCount++;
			}
		}
		else if(encryptionKey.length() == 0)
		{
			size_t isInlineKey = currentCommand.find(".txt");
			
			if(isInlineKey != string::npos)
			{
				encryptionKey = readEncryptionKey(currentCommand, true);
			}
			else if(isInlineKey == string::npos)
			{
				encryptionKey = currentCommand;
			}
		}
		else
		{
			println("Unknown command \"" + commands.getData(0) + "\". Skipping now...");
		}

		for(int i = 0; i < removeCommandCount; i++)
		{
			commands.removeElementAt(0);
		}
	}

	return true;
}


void runAdvancedShell()
{
	LinkedList<string> commands = LinkedList<string>();

	LinkedList<string> blacklistedFiles = LinkedList<string>();
	bool foundBlacklistFile = readBlacklistFile(blacklistedFiles, false);

	if(foundBlacklistFile == false)
	{
		cout << "Alert! No blacklist file was found. To prevent irreversible damage to files, this program " << 
			    "will halt execution now." << endl;

		return;
	}

	LinkedList<string> blacklistedExtensions = LinkedList<string>();
	bool foundExtensionsFile = readExtensionsBlacklistFile(blacklistedExtensions, false);

	if(foundExtensionsFile == false)
	{
		cout << "Alert! No extensions blacklist file was found. To prevent irreversible damage to files, this program " << 
				"will halt execution now." << endl;

		return;
	}

	clearTerminalWithNewlines();

	bool isProcessing = true;

	while(isProcessing)
	{
		string commandString = getCommandString();
		parseCommands(commandString, commands);

		isProcessing = processCommands(commands, blacklistedFiles, blacklistedExtensions);
		
		commands.clear();
	}
}


void run()
{
	createCommands();

	printProgramInformation();

	string encryptionKeyFilename = getEncryptionKeyFilename();
	
	if(encryptionKeyFilename == RESET_ENCRYPTION_KEY_CODE)
	{
		cout << "You are about to set a new encryption key for the program." << endl;
		
		encryptionKeyFilename = getEncryptionKeyFilename();
		setNewEncryptionKey(encryptionKeyFilename);
	}
	else if(encryptionKeyFilename == ADVANCED_USER_SHELL_CODE 
		    || encryptionKeyFilename == ADVANCED_USER_SHELL_CODE.substr(0, 4))
	{
		runAdvancedShell();

		cout << "Program done executing." << endl;
		waitForUser();

		clearCommandList();

		return;
	}
	
	string encryptionKey = readEncryptionKey(encryptionKeyFilename, false);
	
	if(encryptionKey.empty())
	{
		cout << "An error was encountered. No encryption key was loaded by the program." << endl;
		cout << "Program unable to proceed. Aborting..." << endl;
	}
	else
	{
		LinkedList<string> blacklistedFiles = LinkedList<string>();
		bool foundBlacklistFile = readBlacklistFile(blacklistedFiles, false);

		if(foundBlacklistFile == false)
		{
			cout << "Alert! No blacklist file was found. To prevent irreversible damage to files, this program " << 
				    "will halt execution now." << endl;
		}

		LinkedList<string> blacklistedExtensions = LinkedList<string>();
		bool foundExtensionsFile = readExtensionsBlacklistFile(blacklistedExtensions, false);

		if(foundExtensionsFile == false)
		{
			cout << "Alert! No extensions blacklist file was found. To prevent irreversible damage to files, this program " << 
					"will halt execution now." << endl;
		}

		if(foundBlacklistFile && foundExtensionsFile)
		{
			setProgramMode();
			setWhitelistMode();
			setVerboseMode();

			if(mProgramMode == PROGRAM_MODE_DECRYPTION)
			{
				decryptAllInDirectory(encryptionKey, blacklistedFiles, blacklistedExtensions);
			}
			else if(mProgramMode == PROGRAM_MODE_ENCRYPTION)
			{
				encryptAllInDirectory(encryptionKey, blacklistedFiles, blacklistedExtensions);
			}
		}
	}
	
	cout << "Program done executing." << endl;
	waitForUser();

	clearCommandList();
}


void run(int argc, char *argv[])
{
	createCommands();

	string commandString        = "";
	LinkedList<string> commands = LinkedList<string>();

	LinkedList<string> blacklistedFiles = LinkedList<string>();
	bool foundBlacklistFile = readBlacklistFile(blacklistedFiles, true);

	if(foundBlacklistFile == false)
	{
		cout << "Aborted." << endl;

		clearCommandList();

		return;
	}

	LinkedList<string> blacklistedExtensions = LinkedList<string>();
	bool foundExtensionsFile = readExtensionsBlacklistFile(blacklistedExtensions, true);

	if(foundExtensionsFile == false)
	{
		cout << "Aborted." << endl;

		clearCommandList();

		return;
	}

	for(int i = 1; i < argc; i++)
	{
		commandString += argv[i];

		if((i + 1) < argc)
		{
			commandString += " ";
		}
	}

	parseCommands(commandString, commands);
	processCommands(commands, blacklistedFiles, blacklistedExtensions);
		
	commands.clear();
	clearCommandList();
}

#endif
