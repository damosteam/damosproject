
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

#include "node.h"

using namespace std;

template <class T>
class LinkedList
{
    private:
	Node<T>  *mHead;
	Node<T>  *mTail;

        int      mCount;

    protected:

    public:
        LinkedList();

        ~LinkedList();

	T        getHead();
	T        getTail();
        T        getData(int index);
	T        setData(int index, T data);

	int      getCount();
	int      getIndex(T searchData);   

        void     clear();
        void     display();        		
        void     insert(T data);
	void     removeElementAt(int index);

        bool     isEmpty();
        bool     isExist(T searchData);
};

#endif
