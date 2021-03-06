
#ifndef NETWORK_CPP
#define NETWORK_CPP

#include "network.h"

const char* READ_BINARY_FILE        = "-rb";
const char* EXECUTE_NEW_TASK	    = "-et";
const char* WRITE_BINARY_FILE_MODE  = "wb";

const std::string NEXT_TASK_QUERY   = "JOB ";
const std::string BINARY_FILE_QUERY = "BIN ";

void readBinaryFile(int &port, char *inetAddress, std::string filename)
{
	std::cout << "Recieving file \"" << filename << "\" from " << inetAddress 
		<< " at port " << port << " now..." << std::endl;
 
        int socketfd = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in sa_dst;
        memset(&sa_dst, 0, sizeof(struct sockaddr_in));

        sa_dst.sin_family      = AF_INET;
        sa_dst.sin_port        = htons(port);
        sa_dst.sin_addr.s_addr = inet_addr(inetAddress);

        int success = connect(socketfd, (struct sockaddr*) &sa_dst, sizeof(struct sockaddr));
        
	if(success < 0)
	{
		printError("Error: could not connect to socket.\n");
	}

	std::string binaryFileQuery = BINARY_FILE_QUERY + filename;
	printf("Sending query: %s.\n", binaryFileQuery.c_str());
	success = write(socketfd, binaryFileQuery.c_str(), binaryFileQuery.length());

	FILE *fp;
	fp = fopen(filename.c_str(), WRITE_BINARY_FILE_MODE);

	for(;;)
	{
		char buffer[STREAM_BUFFER_BYTE_COUNT];
        	size_t nread = read(socketfd, buffer, STREAM_BUFFER_BYTE_COUNT);

	    	if(nread > 0)
		{
			fwrite(buffer, nread, 1, fp);
		}

	    	if(nread < ((unsigned int) STREAM_BUFFER_BYTE_COUNT))
	    	{
			if (feof(fp))
			{
		    		printf("Reached end of binary file.\n");
			}
			else if (ferror(fp))
			{
		    		printError("Error: failed reading data from socket.\n");
			}

			break;
	    	}
	}

	fclose(fp);
	
	std::cout << "Recieved file \"" << filename << "\" successfully." << std::endl;
	close(socketfd);
}


void sendStringData(int &port, char *inetAddress, std::string data)
{
	std::cout << "Sending data to " << inetAddress << " at port " << port 
		<< " now..." << std::endl;
 
        int socketfd = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in sa_dst;
        memset(&sa_dst, 0, sizeof(struct sockaddr_in));

        sa_dst.sin_family      = AF_INET;
        sa_dst.sin_port        = htons(port);
        sa_dst.sin_addr.s_addr = inet_addr(inetAddress);

        int success = connect(socketfd, (struct sockaddr*) &sa_dst, sizeof(struct sockaddr));
        
	if(success < 0)
	{
		printError("Error: could not connect to socket.\n");
	}

	success = write(socketfd, data.c_str(), data.length());
	
	std::cout << "Data sent successfully." << std::endl;
	close(socketfd);
}


void receiveNextTask(int &port, char *inetAddress, char *clientID, std::string &nextTask)
{
	std::cout << "Recieving next task from " << inetAddress << " at port " 
		<< port << " now..." << std::endl;
 
        int socketfd = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in sa_dst;
        memset(&sa_dst, 0, sizeof(struct sockaddr_in));

        sa_dst.sin_family      = AF_INET;
        sa_dst.sin_port        = htons(port);
        sa_dst.sin_addr.s_addr = inet_addr(inetAddress);

        int success = connect(socketfd, (struct sockaddr*) &sa_dst, sizeof(struct sockaddr));
        
	if(success < 0)
	{
		printError("Error: could not connect to socket.\n");
	}

	std::string nextTaskQuery = NEXT_TASK_QUERY + string(clientID);
	printf("Sending query: %s.\n", nextTaskQuery.c_str());
	success = write(socketfd, nextTaskQuery.c_str(), nextTaskQuery.length());

	for(;;)
	{
		char buffer[STREAM_BUFFER_BYTE_COUNT];
        	size_t nread = read(socketfd, buffer, STREAM_BUFFER_BYTE_COUNT);

	    	if(nread > 0)
		{
			nextTask += string(buffer, nread);
		}

	    	if(nread < ((unsigned int) STREAM_BUFFER_BYTE_COUNT))
	    	{
		    	//printf("Full response received.\n");

			break;
	    	}
	}

	std::cout << "Recieved next task successfully." << std::endl;
	close(socketfd);
}

#endif
