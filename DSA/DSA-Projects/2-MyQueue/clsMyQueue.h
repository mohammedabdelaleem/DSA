#pragma once

#include <iostream>
#include"clsDblLinkedList.h"
using namespace std;

template<class Type>
class clsMyQueue
{
private:
	clsDblLinkedList<Type>_MyQueue; //Composition

public:
	clsMyQueue(){}
	clsMyQueue(const clsMyQueue& source) = delete;
	clsMyQueue& operator=(const clsMyQueue& source) = delete;
	

	void Push(Type Value)
	{
		_MyQueue.InsertAtEnd(Value);
	}

	Type Pop()
	{
		Type PopedItem = Front();
		_MyQueue.DeleteFirstNode();
		return PopedItem;
	}

	Type Front()
	{
		return _MyQueue[0];
	}

	Type Back()
	{
		return _MyQueue[Size()-1];
	}

	short Size()
	{
		return _MyQueue.Size();
	}

	//1st Extensoin
	Type GetItem(short Index)
	{
		return _MyQueue[Index];
	}

	//2nd Extensoin
	void Reverse()
	{
		_MyQueue.Reverse();
	}

	//3rd Extensoin
	void UpdateItem(short Index, Type NewValue)
	{
		_MyQueue.UpdateItem(Index, NewValue);
	}
	//4th Extensoin
	void InsertAfter(short index, Type Value)
	{
		_MyQueue.InsertAfter(index, Value);
	}
	//5th Extensoin
	void InsertAtFront(Type Value)
	{
		_MyQueue.InsertAtBeginning(Value);
	}
	//6th Extensoin
	void InsertAtBack(Type Value)
	{
		_MyQueue.InsertAtEnd(Value);
	}
	//7th Extensoin
	void Clear()
	{
		_MyQueue.Clear();
	}






	void Print()
	{
		_MyQueue.PrintList();
	}
};

