
#ifndef FILE_CPP
#define FILE_CPP

#include "file.h"
#include "linkedList.cpp"

const char* CLIENT_LIST_FILENAME      = "clientid.txt";
const char* NEW_TASK_LIST_FILENAME    = "tasklist.txt";
const char* CLIENT_TASK_LIST_FILENAME = "clienttasks.txt";

void saveDataToFile(LinkedList<char*> &data)
{
	printf("Saving client data to file...\n");

	std::ofstream file;

	time_t currentTime = time(0);

	struct tm* tmValue = gmtime(&currentTime);
	char buffer[32] = "";	
    	strftime(buffer, sizeof(buffer), "%c", tmValue);

	file.open(buffer);

	if(file.is_open())
	{
		for(int i = 0; i < data.getCount(); i++)
		{
			file << data.getData(i);
			file << std::endl;
		}	
	
		file.close();
	}

	printf("Done saving client data to file.\n");
}


void saveClientIDToFile(char* clientID)
{
	printf("Saving client ID information to file...\n");

	std::ofstream file;

	file.open(CLIENT_LIST_FILENAME, fstream::in | fstream::app);

	if(file.is_open())
	{
		file << std::string(clientID);
		file << std::endl;
	
		file.close();
	}

	printf("Done saving client information.\n");
}


void readClientIDList(LinkedList<Client*>* &clientList)
{
	printf("Reading client ID information from file...\n");

	std::ifstream file;

	file.open(CLIENT_LIST_FILENAME);

	if(file.is_open())
	{
		std::string line;

		while(file.eof() == false)
		{
			getline(file, line);

			if(line.empty() == true)
			{
				continue;
			}

			char* clientID;
			clientID = strdup(line.c_str());
	
			printf("Read client ID: %s\n", clientID);

			Client* client = new Client(clientID);
			(*clientList).insert(client);
			
			//free(clientID);
		}
	
		file.close();
	}

	printf("Done reading client information.\n");
}


void saveClientListToFile(LinkedList<Client*>* &clientList)
{
	printf("Saving client list information to file...\n");

	std::ofstream file;

	file.open(CLIENT_LIST_FILENAME);

	if(file.is_open())
	{
		for(int i = 0; i < (*clientList).getCount(); i++)
		{
			Client* client = (*clientList).getData(i);

			printf("Saving client ID %d: %s\n", i, (*client).getClientID());

			file << (*client).getClientID();
			file << std::endl;
		}
	
		file.close();
	}

	printf("Done saving client list information.\n");
}


void clearClientIDList()
{
	std::ofstream file;

	file.open(CLIENT_LIST_FILENAME, std::ofstream::in | std::ofstream::trunc);
	file.close();
}


void clearTaskList()
{
	std::ofstream file;

	file.open(NEW_TASK_LIST_FILENAME, std::ofstream::in | std::ofstream::trunc);
	file.close();
}


void checkForNewTasks(LinkedList<std::string> &newTaskList)
{
	printf("Checking for new tasks on file...\n");

	std::ifstream file;

	file.open(NEW_TASK_LIST_FILENAME);

	if(file.is_open())
	{
		std::string line;

		while(file.eof() == false)
		{
			getline(file, line);

			if(line.empty() == true)
			{
				continue;
			}

			printf("Read new task: %s.\n", line.c_str());

			newTaskList.insert(line);
		}
	
		file.close();
	}

	clearTaskList();
	printf("Done checking for new tasks.\n");
}


void saveTaskListsToFile(LinkedList<Client*>* &clientList)
{
	printf("Saving client task lists to file...\n");

	std::ofstream file;

	file.open(CLIENT_TASK_LIST_FILENAME);

	if(file.is_open())
	{
		LinkedList<std::string> taskList;

		for(int i = 0; i < (*clientList).getCount(); i++)
		{
			Client* client = (*clientList).getData(i);

			printf("Saving task list of client with ID %d: %s\n", 
				i, (*client).getClientID());

			file << (*client).getClientID();
			file << std::endl;

			taskList = (*client).getTaskList();

			file << taskList.getCount();
			file << std::endl;

			for(int n = 0; n < taskList.getCount(); n++)
			{
				file << taskList.getData(n);
				file << std::endl;
			}
		}
	
		file.close();
	}

	printf("Done saving client task lists.\n");
}


void readTaskLists(LinkedList<Client*>* &clientList)
{
	printf("Reading client task lists from file...\n");

	std::ifstream file;

	file.open(CLIENT_TASK_LIST_FILENAME);

	if(file.is_open())
	{
		int currentTask = -1, totalTasks = -1;

		std::string 		line;
		std::string		clientID;
		LinkedList<std::string> taskList;

		while(file.eof() == false)
		{
			getline(file, line);

			if(line.empty() == true)
			{
				continue;
			}

			if(clientID.empty() == true)
			{
				clientID = line;

				printf("Reading task list for client with ID: %s\n.", clientID.c_str());
			}
			else if(totalTasks == -1)
			{
				currentTask = 0;
				std::istringstream(line) >> totalTasks;
			}
			else if(currentTask < totalTasks)
			{
				char* tempClientID = strdup(clientID.c_str());
				int clientIndex = getClientIndex(tempClientID);
				free(tempClientID);
	
				if(clientIndex == -1)
				{
					currentTask++;
					
					continue;	
				}


				Client* client = (*clientList).getData(clientIndex);
				(*client).addNewTask(line);
				(*clientList).setData(clientIndex, client);
	
				currentTask++;
			}
			else
			{
				clientID = "";	
				currentTask = -1;
				totalTasks = -1;
			}
		}
	
		file.close();
	}

	printf("Done reading client task lists.\n");
}

#endif
