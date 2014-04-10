
#ifndef FILE_H
#define FILE_H

#include <fstream>

#include "header.h"
#include "Client.h"
#include "linkedList.h"

extern const char* CLIENT_LIST_FILENAME;
extern const char* NEW_TASK_LIST_FILENAME;
extern const char* CLIENT_TASK_LIST_FILENAME;

void clearTaskList();
void clearClientIDList();
void saveClientIDToFile(char* clientID);
void saveDataToFile(LinkedList<char*> &data);
void readTaskLists(LinkedList<Client*>* &clientList);
void readClientIDList(LinkedList<Client*>* &clientList);
void saveTaskListsToFile(LinkedList<Client*>* &clientList);
void saveClientListToFile(LinkedList<Client*>* &clientList);
void checkForNewTasks(LinkedList<std::string> &newTaskList);

#endif
