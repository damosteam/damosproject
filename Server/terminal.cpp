
#ifndef TERMINAL_CPP
#define TERMINAL_CPP

#include "terminal.h"

void printError(const char *message)
{
	printf("\n%s\n", message);

        exit(1);
}


void printProgramInformation()
{
	printf("Program version: %s.\n", PROGRAM_VERSION);
}


void printProgramPID()
{
	printf("Program PID: %d.\n", (int) getpid());
}

#endif
