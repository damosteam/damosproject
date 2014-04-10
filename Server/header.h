
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <ctime>
#include <sstream>
#include <fstream>

#include "file.h"
#include "Client.h"
#include "network.h"
#include "terminal.h"  
#include "linkedList.h"

extern const char* PROGRAM_VERSION; 

extern int 		    mSocketfd;
extern LinkedList<Client*>* mClientList;

bool isClientExist(char* &clientID);

void shutdownServer();
void initializeClientList();
void signalHandler(int signalID);
void addNewClient(char* &clientID);
void processMessage(int &socketfd);
int getClientIndex(char* &clientID);
void pushTasksToClients(LinkedList<std::string> &newTasks);
void run(int &newSocketfd, int &portNumber, int &pid,
	socklen_t &clientLength, sockaddr_in &serverAddress, sockaddr_in &clientAddress);

#endif
