#pragma once

#include"clsMyStackArr.h"

class clsMyString
{
private:

	clsMyStackArr<string>_UNDO;
	clsMyStackArr<string>_REDO;
	string _Value;

public:

	void Set(string Value)
	{
		_UNDO.Push(_Value);
		_Value = Value;
	}

	string Get()
	{
		return _Value;
	}

	__declspec(property(get = Get, put = Set))string Value;

	/*
	 Look : _UNDO-Stack => M1 M2 M3 M4  CurrentValue=M5

	 After Undo :
	 _REDO-Stack => M5   CurrentValue=M4  _UNDO-Stack => M1 M2 M3

	 After Redo :
		 _REDO => Empty   CurrentValue=M5  _UNDO => M1 M2 M3 M4
	*/

	void Undo()
	{
		if(!_UNDO.IsEmpty())
		{
			_REDO.Push(_Value);
			_Value = _UNDO.Pop();	
		}
	}

	void Redo()
	{
		if (!_REDO.IsEmpty())
		{
			_UNDO.Push(_Value);
			_Value =_REDO.Pop();
		}
	}

};

