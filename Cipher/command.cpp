
#ifndef COMMAND_CPP
#define COMMAND_CPP

#include "command.h"

using namespace std;

Command::Command()
{
	mCommandString     = "-?";
	mInformationString = "??";
}


Command::Command(string command, string information)
{
	mCommandString     = command;
	mInformationString = information;
}


string Command::getCommand()
{
	return mCommandString;
}


string Command::getInformation()
{
	return mInformationString;
}

#endif