
#ifndef CLIENT_C
#define CLIENT_C

#include "header.h"

const char* PROGRAM_VERSION = "0.0.1.2";

int main(int argc, char *argv[])
{
	createBackgroundProcess();
	initializeClientID();
	
	processArguments(argc, argv);

        return 0;
}

#endif
