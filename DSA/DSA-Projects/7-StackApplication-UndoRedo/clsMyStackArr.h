#pragma once
#include"clsMyQueueArr.h"
template<class Type>

class clsMyStackArr:public clsMyQueueArr<Type>
{

public:

	void Push(Type Value) // Jsut Overriding 
	{
		clsMyQueueArr<Type>::_MyArr.InsertAtBeginning(Value);
	}

	Type Top()
	{
		return clsMyQueueArr<Type>::Front();
	}

	Type Bottom()
	{
		return clsMyQueueArr<Type>::Back();
	}

};

