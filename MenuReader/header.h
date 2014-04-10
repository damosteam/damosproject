
#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <fstream>
#include <iostream>

#include "MenuItem.h"
#include "linkedList.h"

const std::string MENU_FILE = "menu.txt";

int getMenuChoice();
int readMenuFile(LinkedList<MenuItem*> &menuItemList);

void printMenu(LinkedList<MenuItem*> &menuItemList);

MenuItem*   getMenuItem(LinkedList<MenuItem*> &menuItemList);
std::string getMenuItemName(LinkedList<MenuItem*> &menuItemList);

#endif
