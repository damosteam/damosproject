
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <netdb.h>
#include <signal.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <string>
#include <fstream>
#include <iostream>

#include "file.h"
#include "network.h"
#include "terminal.h"
#include "linkedList.h"

extern const char* PROGRAM_VERSION;
extern const char* DEFAULT_SHELL_VARIABLE;

const int   JOB_CHECKIN_DECISECONDS  = 1200;
const int   DATABASE_ENTRY_CAPACITY  = 100;
const int   STREAM_BUFFER_BYTE_COUNT = 512;
const long  DAEMON_SLEEP_NANOSECONDS = 100000000;  

int executeTask(std::string taskName);

void sleep();
void initializeClientID();
void setupBackgroundProcess();
void createBackgroundProcess();
void resetEnvironmentVariable();
void signalHandler(int signalID);
void run(int port, char *inetAddress);
void processArguments(int &argc, char *argv[]);
void checkInToServer(int &port, char* inetAddress);
void getEnvironmentVariable(std::string &currentValue);
void sendDatabaseContents(int &port, char *inetAddress);

#endif
