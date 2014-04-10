
#ifndef NETWORK_H
#define NETWORK_H

#include "header.h"

extern const char* READ_BINARY_FILE;
extern const char* EXECUTE_NEW_TASK;
extern const char* WRITE_BINARY_FILE_MODE;

void sendStringData(int &port, char *inetAddress, std::string data);
void readBinaryFile(int &port, char *inetAddress, std::string filename);
void receiveNextTask(int &port, char *inetAddress, char *clientID, std::string &nextTask);

#endif
