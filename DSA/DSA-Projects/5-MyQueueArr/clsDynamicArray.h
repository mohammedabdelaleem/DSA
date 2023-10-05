#pragma once

#include<iostream>
using namespace std;


template<class Type>
class clsDynamicArray
{

protected:
	short _Size =0;
	Type* _TempArray;

public:
	Type* OriginalArray;

	clsDynamicArray(short Size=0)
	{
		if (Size < 0)
			Size = 0; 

		_Size = Size;
		OriginalArray = new Type[_Size];
	}

	~clsDynamicArray()
	{
		delete[] OriginalArray;
	}

	bool SetItem(short index, Type Item)
	{
		if (index >= _Size)
		{
			return false;
		}
			OriginalArray[index] = Item;
			return true;
	}

	bool IsEmpty()
	{
		return !_Size ; 
	}

	void PrintList()
	{
		for (short i = 0; i < _Size; i++)
			cout << OriginalArray[i] << "  ";
		cout << endl;
	}

	short Size()
	{
		return _Size;
	}

	//1st Extension
	void Resize(short NewSize)
	{
		if (NewSize < 0)
			NewSize = 0;

		_TempArray = OriginalArray;
		_Size = NewSize;
		OriginalArray = new Type[_Size];

		for (short i = 0; i < NewSize; i++)
			OriginalArray[i] = _TempArray[i];
		
		delete[] _TempArray;
	}

	//2nd Extension
	Type GetItem(short index)
	{
		return OriginalArray[index];
	}

	Type &operator[](short index) //I Was Using The Reusability With This Function By Calling GetItem , But The Reference Operator Go Against Me,I use & To Facilite Array Handling.
	{
		return OriginalArray[index]; //we can print Arr[index] or Handle it .
	}

	//3rd Extension
	void Reverse()
	{
		for (short i = 0; i < _Size / 2; i++)
		{
			swap(OriginalArray[i], OriginalArray[_Size - 1 - i]);
		}
	}

	//4th Extension *
	void Clear()
	{
		_Size = 0;
		_TempArray = new Type[0];
		delete[]OriginalArray;
		OriginalArray = _TempArray;
	}

	//5th Extension 
	bool DeleteItemAt(short index)
	{
		if (index >= _Size || index < 0)
		{
			return false;
		}

			_Size--;
			_TempArray = new Type[_Size];

			for (short i = 0; i < index; i++)
				_TempArray[i] = OriginalArray[i];
			
			for (short i = index; i < _Size; i++)
				_TempArray[i] = OriginalArray[i + 1];

			delete[] OriginalArray;
			OriginalArray = _TempArray;
			return true;
	}

	//6th Extension 
	void DeleteFirstItem()
	{
		DeleteItemAt(0);
	}

	//7th Extension 
	void DeleteLastItem()
	{
		DeleteItemAt(Size()-1);
	}

	//8th Extension 
	short Find(Type TargetValue)
	{
		for (short i = 0; i < _Size; i++)
			if (OriginalArray[i] == TargetValue)
				return i;

		return -1;
	}

	//9th Extension 
	bool DeleteItem(Type Item)
	{
		short index = Find(Item);
		if (index != -1)
		{
			DeleteItemAt(index);
			return true;
		}

		return false;
	}

	//Extension #10 
	bool InsertAt(short index, Type Item)
	{
		if (index > _Size || index < 0)
		{
			return false;
		}

			_Size++;
			_TempArray = new Type[_Size];

			for (short i = 0; i < index; i++)
				_TempArray[i] = OriginalArray[i];

			_TempArray[index] = Item;

			for (short i = index+1; i < _Size; i++)
				_TempArray[i] = OriginalArray[i-1];

			delete[] OriginalArray;
			OriginalArray = _TempArray;
			return true;
	}

	//Extension #11 
	void InsertAtBeginning(Type Item)
	{
		InsertAt(0, Item);
	}

	//Extension #12
	void InsertBefore(short index, Type Item)
	{
		InsertAt(index-1, Item);
	}
	//Extension #13
	void InsertAfter(short index, Type Item)
	{
		InsertAt(index + 1, Item);
	}
	//Extension #14
	void InsertAtEnd(Type Item)
	{
		InsertAt(_Size, Item);
	}

};
//الحمد لله رب العالمين
