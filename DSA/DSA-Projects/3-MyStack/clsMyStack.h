#pragma once

#include"clsMyQueue.h"

template<class Type>

class clsMyStack:public clsMyQueue<Type>
{

public:
	//clsMyStack() {}
	//clsMyStack(const clsMyStack& source) = delete;
	//clsMyStack& operator=(const clsMyStack& source) = delete;

	void Push(Type Value) // Jsut Overriding 
	{
	clsMyQueue<Type>::_MyList.InsertAtBeginning(Value);
	}

	Type Top()
	{
		return clsMyQueue<Type>::Front();
	}

	Type Bottom()
	{
	    return clsMyQueue<Type>::Back();
	}

};

