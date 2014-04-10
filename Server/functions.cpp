
#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include "header.h"
#include "linkedList.cpp"

const char* NEXT_TASK_QUERY   = "JOB";
const char* BINARY_FILE_QUERY = "BIN";

int 		     mSocketfd;
LinkedList<Client*>* mClientList;

void run(int &newSocketfd, int &portNumber, int &pid,
	socklen_t &clientLength, sockaddr_in &serverAddress, sockaddr_in &clientAddress)
{
	printf("Waiting to accept new clients...\n");

	while(1) 
	{
		LinkedList<std::string> newTaskList = LinkedList<std::string>();
		checkForNewTasks(newTaskList);

		if(newTaskList.isEmpty() == false)
		{
			pushTasksToClients(newTaskList);
		}

        	newSocketfd = accept(mSocketfd, (struct sockaddr*) &clientAddress, &clientLength);
         
		if(newSocketfd < 0)
		{ 
             		printError("Error: failed to accept a client.\n");
		}

	        pid = fork();
         
		if(pid < 0)
		{             		
			printError("Error: could not fork process.\n");
		}
         	else if(pid == 0) 
		{
			readClientIDList(mClientList);
			readTaskLists(mClientList);
			clearClientIDList();

             		close(mSocketfd);

             		processMessage(newSocketfd);
			saveClientListToFile(mClientList);			
			saveTaskListsToFile(mClientList);

			(*mClientList).clear();
			delete mClientList;

			exit(0);
		}
		else
		{
			close(newSocketfd);
		}
        }

	printf("Server no longer accepting new clients.\n");
}


void signalHandler(int signalID)
{
	switch(signalID)
	{
		case SIGTERM:
			shutdownServer();

			break;
		case SIGKILL:
			shutdownServer();

			break;
		case SIGSTOP:
			shutdownServer();

			break;
		default:
			;
	}
}


void shutdownServer()
{
	printf("Server shutting down now...\n");

	close(mSocketfd);

	(*mClientList).clear();
	delete mClientList;
}


void initializeClientList()
{
	mClientList = new LinkedList<Client*>();
}


void processMessage(int &socketfd)
{	
	printf("Processing a new message...\n");

	char  buffer [STREAM_BUFFER_BYTE_COUNT];
	bzero(buffer, STREAM_BUFFER_BYTE_COUNT);
        
	int queryStatus = read(socketfd, buffer, (STREAM_BUFFER_BYTE_COUNT - 1));

        if(queryStatus < 0) 
	{
		printError("Error: failed to read data from socket.\n");
	}

	LinkedList<char*> streamData = LinkedList<char*>();
	streamData.insert(buffer);

	std::stringstream readStream;
	readStream << buffer;

	bool flag = false;
	bool npos = (readStream.str().find(BINARY_FILE_QUERY) == std::string::npos);
	
	if(npos == false)
	{
		int streamLength     = readStream.str().length();
		std::string filename = readStream.str().substr(4, streamLength);

		sendBinaryFile(socketfd, filename);
		flag = true;
	}

	npos = (readStream.str().find(NEXT_TASK_QUERY) == std::string::npos);
	
	if(npos == false && !flag)
	{
		int streamLength     = readStream.str().length();
		std::string clientID = readStream.str().substr(4, streamLength);

		sendNextTask(socketfd, strdup(clientID.c_str()));
		flag = true;
	}		

	if(!flag)
	{
		for(;;)
		{
			char buffer[STREAM_BUFFER_BYTE_COUNT];
			size_t nread = read(socketfd, buffer, (STREAM_BUFFER_BYTE_COUNT - 1));

			if(nread > 0)
			{
				streamData.insert(buffer);
			}
		    
			if(nread < ((unsigned int) STREAM_BUFFER_BYTE_COUNT))
		    	{
				break;
		    	}
		}

		saveDataToFile(streamData);
	}

	printf("Exiting client thread...\n");
	close(socketfd);
}


bool isClientExist(char* &clientID)
{
	//printf("Checking if client is currently registered.\n");

	for(int i = 0; i < (*mClientList).getCount(); i++)
	{
		Client client = *((*mClientList).getData(i));
		
		if(strcmp(client.getClientID(), clientID) == 0)
		{
			return true;
		}
	}

	//printf("Client not currently registered.\n");
	return false;
}


int getClientIndex(char* &clientID)
{
	for(int i = 0; i < (*mClientList).getCount(); i++)
	{
		Client client = *((*mClientList).getData(i));
		
		if(strcmp(client.getClientID(), clientID) == 0)
		{
			return i;
		}
	}

	return -1;
}


void addNewClient(char* &clientID)
{
	if(isClientExist(clientID) == true)
	{
		printf("Client already registered.\n");
		printf("Current client count: %d.\n", (*mClientList).getCount());

		return;
	}

	printf("Adding a new client...\nClient ID: %s.\n", clientID);

	Client* client = new Client(clientID);
	(*mClientList).insert(client);

	printf("Client added to server client list.\n");
	printf("Current client count: %d.\n", (*mClientList).getCount());
}


void pushTasksToClients(LinkedList<std::string> &newTasks)
{
	printf("Pushing new tasks to client queues...\n");

	for(int i = 0; i < (*mClientList).getCount(); i++)
	{
		Client* currentClient = (*mClientList).getData(i);
		printf("Pushing new tasks to queue of client: %s.\n", (*currentClient).getClientID());

		for(int n = 0; n < newTasks.getCount(); n++)
		{
			std::string task = newTasks.getData(n);

			std::size_t found = task.find(" ");
  			if(found != std::string::npos)
			{
				std::string clientID = task.substr((found + 1), task.length());
				char* tempClientID = strdup(clientID.c_str());
	
				if(getClientIndex(tempClientID) == i)
				{
					free(tempClientID);

					task = task.substr(0, (found - 1));
					printf("Adding new task: %s.\n", task.c_str());

					(*currentClient).addNewTask(task);
				}
				else
				{
					free(tempClientID);

					continue;
				}
			}

			printf("Adding new task: %s.\n", task.c_str());

			(*currentClient).addNewTask(task);
		}
	}

	printf("Done pushing new tasks.\n");
}

#endif
