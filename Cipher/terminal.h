
#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <fstream>
#include <iostream>
#include <sys/types.h>

#include "command.h"
#include "linkedList.h"

using namespace std;

extern bool mProgramMode;
extern bool mVerboseModeEnabled;
extern bool mWhitelistModeEnabled;

extern LinkedList<Command*> mCommands;

void waitForUser();
void createCommands();
void setProgramMode();
void setVerboseMode();
void print(int number);
void clearCommandList();
void printCommandList();
void prinln(int number);
void setWhitelistMode();
void printProgramUsage();
void print(string message);
void print(double decimal);
void println(string message);
void println(double decimal);
void printProgramInformation();
void clearTerminalWithNewlines();
void getCommandInformation(string command);

string getCommandString();

#endif
