
#ifndef MAIN_CPP
#define MAIN_CPP

#include "header.h"
#include "linkedList.cpp"

int main(int argc, char** argv)
{
	LinkedList<MenuItem*> menuItemList = LinkedList<MenuItem*>();

	std::string returnType = "";

	if(argc > 1)
	{
		returnType = argv[1];
	}

	if(readMenuFile(menuItemList) == 0)
	{
		printMenu(menuItemList);

		if(returnType.empty() == true || returnType.compare("-i"))
		{
			int menuChoice = getMenuChoice();

			std::cout << menuChoice << std::endl;
		}
		else if(returnType.compare("-n"))
		{
			std::cout << getMenuItemName(menuItemList) << std::endl;
		}
		else if(returnType.compare("-e"))
		{
			std::cout << (*getMenuItem(menuItemList)).getExecutableName() << std::endl;
		}
	}

	menuItemList.clear();
}

#endif
