
#ifndef NETWORK_H
#define NETWORK_H

#include "header.h"

extern const char* READ_BINARY_FILE_MODE;

const int STREAM_BUFFER_BYTE_COUNT = 512;  

void sendNextTask(int &socketfd, char* clientID);
void sendBinaryFile(int &socketfd, std::string &filename);
void setupServer(int &newSocketfd, int &portNumber, int &pid,
	socklen_t &clientLength, sockaddr_in &serverAddress, sockaddr_in &clientAddress);

#endif
