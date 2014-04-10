
#ifndef MAIN_CPP
#define MAIN_CPP

#include "header.h"

int main(int argc, char **argv)
{
	KeyLogProcessor *keyLogProcessor;

  	keyLogProcessor = new KeyLogProcessor(argc, argv);
  	keyLogProcessor->processKeyLogFile();

	delete keyLogProcessor;
}

#endif
