
#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "linkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
    mHead = NULL;
    mTail = NULL;

    mCount = 0;
}


template <class T>
LinkedList<T>::~LinkedList()
{
    Node<T> *tempNode, *toBeDeleted;

    if(mHead != NULL)
    {
	tempNode = mHead;

	while(tempNode != NULL)
	{
	    toBeDeleted = tempNode;
	    tempNode = tempNode->mNext;
	    toBeDeleted->mNext = NULL;

	    delete toBeDeleted;
        }
    }

    mHead = NULL;
    mTail = NULL;
    mCount = 0;
}


template <class T>
int LinkedList<T>::getCount()
{
    return mCount;
}


template <class T>
T LinkedList<T>::getData(int index)
{
    if(index > (mCount - 1))
    {
	return NULL;
    }

    Node<T> *tempNode = NULL; 
	
    tempNode = mHead;
    for(int i = 0; i < index; i++)
    {
        tempNode = tempNode->mNext;
    }

    return tempNode->mData;
}


template <class T>
T LinkedList<T>::setData(int index, T data)
{
    if(index > (mCount - 1))
    {
	return NULL;
    }

    Node<T> *tempNode = NULL;

    tempNode = mHead;
    for(int i = 0; i < index; i++)
    {
        tempNode = tempNode->mNext;
    }

    tempNode->mData = data;

    return data;
}


template <class T>
void LinkedList<T>::clear()
{
    while(mCount > 0)
    {
	removeElementAt(0);
    }

    mHead = NULL;
    mTail = NULL;
    mCount = 0;
}


template <class T>
void LinkedList<T>::display()
{
    Node<T> *tempNode;

    if(mHead == NULL)
    {
        cout << "The list is empty. " << endl;
    
	return;
    }

    tempNode = mHead;
    while(tempNode != NULL)
    {
        cout << tempNode->mData;
	cout << " ";
        
        tempNode = tempNode->mNext;
    }

    cout << endl;
}


template <class T>
int LinkedList<T>::getIndex(T searchData)
{
	int index = -1;
	Node<T> *tempNode = NULL;

        tempNode = mHead;
        for(int i = 0; i < mCount; i++)
	{
		if(tempNode->mData == searchData)
		{
			index = i;
			break;
		}

        	tempNode = tempNode->mNext;
	}

	return index;
}


template <class T>
T LinkedList<T>::getHead()
{
	return mHead;
}


template <class T>
T LinkedList<T>::getTail()
{
	return mTail;
}


template <class T>
void LinkedList<T>::insert(T newData)
{
    Node<T> *newNode = NULL;

    newNode = new Node<T>(newData);

    if(mHead == NULL)
    {
        mHead = newNode;
        mTail = newNode;
    }
    else
    {
	mTail->mNext = newNode;
	mTail = newNode;
    }

    mCount++;
}


template <class T>
bool LinkedList<T>::isEmpty()
{
    return (mHead == NULL);
}


template <class T>
bool LinkedList<T>::isExist(T searchData)
{
	bool found = false;
	Node<T> *tempNode = NULL;

        tempNode = mHead;
        for(int i = 0; i < mCount; i++)
	{
		if(tempNode->mData == searchData)
		{
			found = true;
			break;
		}

        	tempNode = tempNode->mNext;
	}

        return found;
}


template <class T>
void LinkedList<T>::removeElementAt(int index)
{
    if(index < 0 || index >= mCount)
    {
	return;
    }
	
    Node<T> *tempNode = NULL, *oneBefore = NULL, *toBeDeleted = NULL;
    int j = 0;
	
    if(isEmpty() == false)
    {
        if(index == 0)
        {
            toBeDeleted = mHead;
            mHead = mHead->mNext;
            toBeDeleted->mNext = NULL;
        }
        else if(index == (mCount - 1))
        {
            toBeDeleted = mTail;
            for(oneBefore = mHead, j = 0; j < (index - 1); j++)
	    {
                oneBefore = oneBefore->mNext;
	    }

            oneBefore->mNext = NULL;
            mTail = oneBefore;
        }
        else
        {
            tempNode = mHead;
            for(j = 0; j < index; j++)
            {
                oneBefore = tempNode;
                tempNode = tempNode->mNext;
            }

            toBeDeleted = tempNode;
            oneBefore->mNext = tempNode->mNext;
            toBeDeleted->mNext = NULL;
        }
		
        delete toBeDeleted;
		
        mCount--;
    }
}

#endif
