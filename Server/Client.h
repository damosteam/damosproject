
#ifndef CLIENT_H
#define CLIENT_H

#include <string.h>
#include <stdlib.h>

#include <string>

#include "linkedList.h"

class Client
{
	private:
		char*                   mClientID;
		LinkedList<std::string> mTaskList;

	public:
		Client();
		Client(char* clientID);
	
		~Client();		

		void setClientID(char* clientID);
		void addNewTask(std::string newTask);

		char*       		getClientID();		
		std::string 		getNextTask();
		LinkedList<std::string> getTaskList();		
};

#endif
