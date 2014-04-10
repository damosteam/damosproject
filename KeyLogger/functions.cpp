
#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include "header.h"

void signalHandler(int signal)
{
	delete mKeyLogger;

	exit(0);
}

#endif
