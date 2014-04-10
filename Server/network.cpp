
#ifndef NETWORK_CPP
#define NETWORK_CPP

#include "network.h"
#include "linkedList.cpp"

const char* READ_BINARY_FILE_MODE = "rb";

void setupServer(int &newSocketfd, int &portNumber, int &pid,
	socklen_t &clientLength, sockaddr_in &serverAddress, sockaddr_in &clientAddress)
{
	printf("Starting up server...\n");

	mSocketfd = socket(AF_INET, SOCK_STREAM, 0);
      
        if(mSocketfd < 0) 
	{
        	printError("Error: could not open socket.\n");
	}

        bzero((char*) &serverAddress, sizeof(serverAddress));

     	serverAddress.sin_family      = AF_INET;
     	serverAddress.sin_addr.s_addr = INADDR_ANY;
     	serverAddress.sin_port        = htons(portNumber);

        if(bind(mSocketfd, (struct sockaddr*) &serverAddress,
        	sizeof(serverAddress)) < 0) 
	{
        	printError("Error: could not bind socket.\n");
	}

	initializeClientList();

	signal(SIGTERM, signalHandler);
	signal(SIGKILL, signalHandler);
	signal(SIGSTOP, signalHandler);

        listen(mSocketfd, 5);
        clientLength = sizeof(clientAddress);

	printf("Server started. Now listening on port: %d.\n", portNumber);
}


void sendBinaryFile(int &socketfd, std::string &filename)
{
	printf("Sending binary file to client...\n");

	FILE *fp;
	fp = fopen(filename.c_str(), READ_BINARY_FILE_MODE);

	int numberOfBytes = 0;

	for(;;)
	{
		char buffer[STREAM_BUFFER_BYTE_COUNT];
	        size_t nread = fread(buffer, sizeof(char), STREAM_BUFFER_BYTE_COUNT, fp);

	        if(nread > 0)
		{
			numberOfBytes += write(socketfd, buffer, nread);
		}
	    
		if(nread < ((unsigned int) STREAM_BUFFER_BYTE_COUNT))
	    	{
			if(feof(fp))
			{
		        	printf("End of binary file reached.\n");
			}
			else if(ferror(fp))
			{
		    		printError("Error: writing to socket failed.\n");
			}
		
			break;
	    	}
	}

	printf("Done sending binary file.\n");
	fclose(fp);
}


void sendNextTask(int &socketfd, char* clientID)
{
	printf("Sending a task to a client...\n");

	if(isClientExist(clientID) == false)
	{
		addNewClient(clientID);
	}
	else 
	{
		std::string nextTask;
		int numberOfBytes = 0;
	
		for(int i = 0; i < (*mClientList).getCount(); i++)
		{
			Client client = *((*mClientList).getData(i));

			if(strcmp(client.getClientID(), clientID) == 0)
			{
				nextTask = client.getNextTask();

				numberOfBytes += write(socketfd, nextTask.c_str(), nextTask.length());
				break;
			}
		}
	}
	
	printf("Done sending a task.\n");
}

#endif
