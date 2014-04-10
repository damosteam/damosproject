
#ifndef COMMAND_H
#define COMMAND_H

#include <string>

using namespace std;

class Command
{
	private:
		string mCommandString;
		string mInformationString;

	public:
		Command();
		Command(string command, string information);

		string getCommand();
		string getInformation();
};

#endif