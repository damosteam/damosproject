
#ifndef CLIENT_CPP
#define CLIENT_CPP

#include "Client.h"
#include "linkedList.cpp"

Client::Client()
{
	mClientID = NULL;
	mTaskList = LinkedList<std::string>();
}


Client::Client(char* clientID)
{
	mClientID = clientID;
	mTaskList = LinkedList<std::string>();
}

	
Client::~Client()
{
	mTaskList.clear();
	mClientID = NULL;
}		


void Client::setClientID(char* clientID)
{
	if(clientID == NULL || strlen(clientID) == 0)
	{
		return;
	}

	mClientID = clientID;
}


void Client::addNewTask(std::string newTask)
{
	if(newTask.empty() == true)
	{
		return;
	}

	mTaskList.insert(newTask);
}


char* Client::getClientID()
{
	return mClientID;
}
		

std::string Client::getNextTask()
{
	if(mTaskList.isEmpty() == true)
	{
		return "";
	}

	std::string nextTask = mTaskList.getData(0);

	mTaskList.removeElementAt(0);
	return nextTask;
}


LinkedList<std::string> Client::getTaskList()
{
	return mTaskList;
}

#endif

