#pragma once

#include"clsDblLinkedList.h"

template<class Type>
class clsMyQueue
{
protected:
	clsDblLinkedList<Type>_MyList; //Composition

public:
	/*clsMyQueue(){}
	clsMyQueue(const clsMyQueue& source) = delete;
	clsMyQueue& operator=(const clsMyQueue& source) = delete;
	*/

	void Push(Type Value)
	{
		_MyList.InsertAtEnd(Value);
	}

	Type Pop()
	{
		Type PopedItem = Front();
		_MyList.DeleteFirstNode();
		return PopedItem;
	}

	Type Front()
	{
		return _MyList[0];
	}

	Type Back()
	{
		return _MyList[Size()-1];
	}

	short Size()
	{
		return _MyList.Size();
	}

	//1st Extensoin
	Type GetItem(short Index)
	{
		return _MyList[Index];
	}

	//2nd Extensoin
	void Reverse()
	{
		_MyList.Reverse();
	}

	//3rd Extensoin
	void UpdateItem(short Index, Type NewValue)
	{
		_MyList.UpdateItem(Index, NewValue);
	}
	//4th Extensoin
	void InsertAfter(short index, Type Value)
	{
		_MyList.InsertAfter(index, Value);
	}
	//5th Extensoin
	void InsertAtFront(Type Value)
	{
		_MyList.InsertAtBeginning(Value);
	}
	//6th Extensoin
	void InsertAtBack(Type Value)
	{
		_MyList.InsertAtEnd(Value);
	}
	//7th Extensoin
	void Clear()
	{
		_MyList.Clear();
	}






	void Print()
	{
		_MyList.PrintList();
	}
};

