
#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include "header.h"
#include "linkedList.cpp"

int readMenuFile(LinkedList<MenuItem*> &menuItemList)
{
  	std::ifstream menuFile(MENU_FILE.c_str());

	std::string line;
	std::string menuItemName;
	std::string menuItemExecutableName;

	bool readExecutableLine = false;

	if(menuFile.is_open())
  	{
		while(getline(menuFile, line))
		{
			if(line.empty() == true && readExecutableLine == true)
			{
				menuItemName = "";
				menuItemExecutableName = "";

				readExecutableLine = false;
			}
			else if(menuItemName.empty() == true)
			{
				menuItemName = line;

				MenuItem* menuItem = new MenuItem(menuItemName);
				menuItemList.insert(menuItem);
			}
			else if(menuItemExecutableName.empty() == true)
			{
				readExecutableLine = true;
				menuItemExecutableName = line;			

				MenuItem* menuItem = menuItemList.getData((menuItemList.getCount() - 1));
				(*menuItem).setExecutableName(menuItemExecutableName);
				menuItemList.setData((menuItemList.getCount() - 1), menuItem);
			}
			else
			{
				MenuItem* menuItem = menuItemList.getData((menuItemList.getCount() - 1));
				(*menuItem).addToDescription(line);
				menuItemList.setData((menuItemList.getCount() - 1), menuItem);
			}
		}

    		menuFile.close();
  	}
  	else
	{
		std::cout << "Unable to open menu file \"" << MENU_FILE
			<< "\" to read menu data. Aborting..." << std::endl;

		return 1;
	}

	return 0;
}


void printMenu(LinkedList<MenuItem*> &menuItemList)
{
	for(int i = 0; i < menuItemList.getCount(); i++)
	{
		MenuItem* menuItem = menuItemList.getData(i);
		
		std::cout << "[" << (i + 1) << "]: " << (*menuItem).getName() << std::endl;

		LinkedList<std::string> description = (*menuItem).getDescription();
		
		for(int n = 0; n < description.getCount(); n++)
		{
			std::cout << description.getData(n) << std::endl; 
		}

		std::cout << std::endl;
	}
}


int getMenuChoice()
{
	std::cout << "Please enter your menu choice: ";

	std::string choiceString;
	getline(std::cin, choiceString);

	int choice = -1;

	stringstream convertStream(choiceString);
	convertStream >> choice;

	return choice;
}


std::string getMenuItemName(LinkedList<MenuItem*> &menuItemList)
{
	std::cout << "Please enter your menu choice: ";

	std::string choiceString;
	getline(std::cin, choiceString);

	int choice = -1;

	stringstream convertStream(choiceString);
	convertStream >> choice;

	choiceString = (*menuItemList.getData((choice - 1))).getName();

	return choiceString;
}


MenuItem* getMenuItem(LinkedList<MenuItem*> &menuItemList)
{
	std::cout << "Please enter your menu choice: ";

	std::string choiceString;
	getline(std::cin, choiceString);

	int choice = -1;

	stringstream convertStream(choiceString);
	convertStream >> choice;

	MenuItem* menuItem = menuItemList.getData((choice - 1));

	return menuItem;
}

#endif
