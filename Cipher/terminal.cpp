
#ifndef TERMINAL_CPP
#define TERMINAL_CPP

#include "header.h"
#include "terminal.h"
#include "linkedList.cpp"

using namespace std;

bool mProgramMode;
bool mVerboseModeEnabled;
bool mWhitelistModeEnabled;

LinkedList<Command*> mCommands = LinkedList<Command*>();

void createCommands()
{
	Command *command;

	command = new Command("-e", "Use this command to encrypt text input from the terminal or from a script.");
	mCommands.insert(command);

	command = new Command("-d", "Use this command to decrypt text input from the terminal or from a script.");
	mCommands.insert(command);

	command = new Command("-E", "Use this command to encrypt every file inside the directory of this utility.");
	mCommands.insert(command);

	command = new Command("-D", "Use this command to decrypt every file inside the directory of this utility.");
	mCommands.insert(command);

	command = new Command("-v", "Use this command to enable verbose output mode.");
	mCommands.insert(command);

	command = new Command("-w", "Use this command to use the blacklist file as a whitelist instead.");
	mCommands.insert(command);

	command = new Command("-ecf", "Use this command to encrypt program configuration files.");
	mCommands.insert(command);

	command = new Command("-dcf", "Use this command to decrypt program configuration files.");
	mCommands.insert(command);
}


void printCommandList()
{
	cout << "Command list: " << endl;

	Command *command;

	for(int i = 0; i < mCommands.getCount(); i++)
	{
		command = mCommands.getData(i);

		cout << "[" << (i + 1) << "] " << command->getCommand() << endl;
		getCommandInformation(command->getCommand());
	}
}


void getCommandInformation(string command)
{
	for(int i = 0; i < mCommands.getCount(); i++)
	{
		if(mCommands.getData(i)->getCommand() == command)
		{
			Command *command = mCommands.getData(i);

			cout << "Command information: " << endl;
			cout << command->getInformation() << endl;

			break;
		}
	}
}


void clearCommandList()
{
	//mCommands.clear();

	while(mCommands.getCount() > 0)
	{
		Command* command = mCommands.getData(0);
		delete command;

		mCommands.removeElementAt(0);
	}
}


void waitForUser()
{
	cout << "Please press Enter to continue...";
	
	string waiting = "";
	getline(cin, waiting);
}


void clearTerminalWithNewlines()
{
	for(int i = 0; i < TERMINAL_DISPLAYED_ROWS; i++)
	{
		cout << endl;
	}
}


string getCommandString()
{
	cout << ":";

	string commandString;
	getline(cin, commandString);

	return commandString;
}


void print(string message)
{
	if(mVerboseModeEnabled == true)
	{
		cout << message;
	}
}


void println(string message)
{
	if(mVerboseModeEnabled == true)
	{
		cout << message << endl;
	}
}


void print(int number)
{
	if(mVerboseModeEnabled == true)
	{
		cout << number;
	}
}


void prinln(int number)
{
	if(mVerboseModeEnabled == true)
	{
		cout << number << endl;
	}
}


void print(double decimal)
{
	if(mVerboseModeEnabled == true)
	{
		cout << decimal;
	}
}


void println(double decimal)
{
	if(mVerboseModeEnabled == true)
	{
		cout << decimal << endl;
	}
}


void printProgramInformation()
{
	/* cout << "This is a XOR file encryption program." << endl; */
	cout << "Project name: "    << PROJECT_NAME    << "." << endl;
	cout << "Project author: "  << PROJECT_AUTHOR  << "." << endl;
	cout << "Program version: " << PROGRAM_VERSION << "." << endl;
	cout << "Last update: "     << LAST_UPDATE     << "." << endl;
	cout << endl;
}


void printProgramUsage()
{
	cout << "Program usage: loe.exe <KEY FILE> <OPERATION>" << endl;
	cout << "Operations: -e (encrypt)" << endl;
	cout << "            -d (decrypt)" << endl;
	cout << "            -E (encrypt directory)" << endl;
	cout << "            -D (decrypt directory)" << endl;
	cout << "Additional arguments: -v (verbose output)" << endl;
	cout << "                      -w (whitelist mode)" << endl;
	cout << "                      -ecf (encrypt configuration files)" << endl;
	cout << "                      -dcf (decrypt configuration files)" << endl;
	cout << "For additional information see README.txt in program directory." << endl;
	cout << endl;
}


void setProgramMode()
{
	cout << "Would to like to encrypt or decrypt the files within the current directory?" << endl;
	cout << "Note: the current directory is the folder that contains this program's executable." << endl;
	
	while(true)
	{
		cout << "Please enter \"d\" (decrypt) or \"e\" (encrypt): ";
		
		string input = "";
		getline(cin, input);
		
		if(input == "d" || input == "decrypt" || input == "D")
		{
			mProgramMode = false;
			
			cout << "Program mode set to: decryption." << endl;
			
			break;
		}
		else if(input == "e" || input == "encrypt" || input == "E")
		{
			mProgramMode = true;
			
			cout << "Program mode set to: encryption." << endl;
			
			break;
		}
		else
		{
			cout << "Sorry! That is not a valid choice. Try again." << endl;
			
			continue;
		}
	}
}


void setVerboseMode()
{
	cout << "Would you like to enable verbose output during encryption/decryption?" << endl;

	while(true)
	{
		cout << "Please enter \"y\" or \"n\": ";
		
		string input = "";
		getline(cin, input);
		
		if(input == "y" || input == "yes" || input == "Y")
		{
			mVerboseModeEnabled = true;
			
			cout << "Verbose output enabled." << endl;
			
			break;
		}
		else if(input == "n" || input == "no" || input == "N")
		{
			mVerboseModeEnabled = false;
			
			cout << "Verbose output disabled." << endl;
			
			break;
		}
		else
		{
			cout << "Sorry! That is not a valid choice. Try again." << endl;
			
			continue;
		}
	}
}


void setWhitelistMode()
{
	cout << "Would you like to use the blacklist file as a whitelist, instead?" << endl;

	while(true)
	{
		cout << "Please enter \"y\" or \"n\": ";
		
		string input = "";
		getline(cin, input);
		
		if(input == "y" || input == "yes" || input == "Y")
		{
			mWhitelistModeEnabled = true;
			
			cout << "Whitelist mode enabled." << endl;
			
			break;
		}
		else if(input == "n" || input == "no" || input == "N")
		{
			mWhitelistModeEnabled = false;
			
			cout << "Whitelist mode disabled." << endl;
			
			break;
		}
		else
		{
			cout << "Sorry! That is not a valid choice. Try again." << endl;
			
			continue;
		}
	}
}

#endif
