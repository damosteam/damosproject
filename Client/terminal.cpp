
#ifndef TERMINAL_CPP
#define TERMINAL_CPP

#include "terminal.h"

void printError(const char *message)
{
	printf("\n%s\n", message);

        exit(1);
}

#endif

