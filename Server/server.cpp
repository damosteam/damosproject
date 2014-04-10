
#ifndef SERVER_CPP
#define SERVER_CPP

#include "header.h"
#include "linkedList.cpp"

const char* PROGRAM_VERSION = "0.0.1.3";

int main(int argc, char *argv[])
{
	if(argc < 2) 
        {
        	printError("Error: no port number defined.\n");
      	}

	printProgramInformation();
	printProgramPID();
	
	int newSocketfd, portNumber = atoi(argv[1]), pid;
     	socklen_t clientLength;
        struct sockaddr_in serverAddress, clientAddress;

	setupServer(newSocketfd, portNumber, pid,
		clientLength, serverAddress, clientAddress);
        run(newSocketfd, portNumber, pid,
		clientLength, serverAddress, clientAddress);

	shutdownServer();

	return 0; 
}

#endif

