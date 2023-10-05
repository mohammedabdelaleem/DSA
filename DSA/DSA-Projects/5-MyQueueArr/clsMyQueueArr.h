#pragma once

#include"clsDynamicArray.h"

template<class Type>
class clsMyQueueArr
{
protected:
	clsDynamicArray<Type>_MyArr;

public:


	void Push(Type Value)
	{
		_MyArr.InsertAtEnd(Value);
	}

	Type Pop()
	{
		Type PopedItem = _MyArr[0];
		_MyArr.DeleteFirstItem();
		return PopedItem;
	}

	Type Front()
	{
		return _MyArr[0];
	}

	Type Back()
	{
		return _MyArr[Size() - 1];
	}

	short Size()
	{
		return _MyArr.Size();
	}

	//1st Extensoin
	Type GetItem(short Index) //if unreal index it will return a garbage value
	{
		return _MyArr[Index];
	}

	Type& operator[](short index)
	{
		return _MyArr[index];
	}

	//2nd Extensoin
	void Reverse()
	{
		_MyArr.Reverse();
	}

	//3rd Extensoin
	void UpdateItem(short Index, Type NewValue)
	{
		_MyArr.SetItem(Index, NewValue);
	}
	//4th Extensoin
	void InsertAfter(short index, Type Value)
	{
		_MyArr.InsertAfter(index, Value);
	}
	//5th Extensoin
	void InsertAtFront(Type Value)
	{
		_MyArr.InsertAtBeginning(Value);
	}
	//6th Extensoin
	void InsertAtBack(Type Value)
	{
		_MyArr.InsertAtEnd(Value);
	}
	//7th Extensoin
	void Clear()
	{
		_MyArr.Clear();
	}

	void Print()
	{
		_MyArr.PrintList();
	}

};

