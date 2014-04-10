
#ifndef MENU_ITEM_CPP
#define MENU_ITEM_CPP

#include "MenuItem.h"
#include "linkedList.cpp"

MenuItem::MenuItem()
{
	mName = "";
	mExecutableName = "";
	mDescription = LinkedList<std::string>();
}


MenuItem::MenuItem(std::string name)
{
	mName = name;
	mExecutableName = "";
	mDescription = LinkedList<std::string>();
}


MenuItem::MenuItem(std::string name, std::string executableName)
{
	mName = name;
	mExecutableName = executableName;
	mDescription = LinkedList<std::string>();
}


MenuItem::~MenuItem()
{
	mDescription.clear();
}


std::string MenuItem::getName()
{
	return mName;
}


std::string MenuItem::getExecutableName()
{
	return mExecutableName;
}


LinkedList<std::string> MenuItem::getDescription()
{
	return mDescription;
}


void MenuItem::setExecutableName(std::string executableName)
{
	mExecutableName = executableName;
}


void MenuItem::addToDescription(std::string &moreInformation)
{
	mDescription.insert(moreInformation);
}

#endif
