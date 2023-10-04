//My Old Code Of Array List Data Structure
#include <iostream>
#include <assert.h>
using namespace std;

//template class
template<class Type>
class ArrayList
{
private:
    Type* _Arr = nullptr;
    short _Size, _Length; // The Whole And Actual Length(Array's Number)
public:
    ///////////////
    ArrayList(short size)//O(_Size)
    {
        _Size = size;
        _Arr = new Type[size]{0};
        _Length = 0;
    }
    //Copy constructor
    ArrayList(const ArrayList& Source) //O(_Size)
    {
        _Size = Source._Size;
        _Length = Source._Length;
        _Arr = new Type[_Size];//O(_Size)
        assert(_Arr != NULL);
        //copying items
        for (short i = 0; i < _Length; i++)
            _Arr[i] = Source._Arr[i];
    }
    //////
    bool Isfull() //O(1)
    {
        return(_Length == _Size);
    }
    ////////////
    bool IsEmpty() //O(1)
    {
        return(_Length == 0);
    }
    ////////////
    void Print() //O(length)
    {
        if (IsEmpty())
        {
            cout << "Empty\n";
            return;
        }
        for (short i = 0; i < _Length; i++)
            cout << _Arr[i] << " ";
        cout << endl;
    }
    //////
    void Append(Type val)
    {
        if (Isfull())
            Expand_Size();

        _Arr[_Length++] = val;
    }
    ///////
    void Insert(short idx, Type val)
    {
        if (Isfull())
            Expand_Size();

        for (short i = _Length; i > idx; i--)
            _Arr[i] = _Arr[i - 1];
        //
        _Arr[idx] = val;
    }
    /////////more important
    void ReplaceAt(short Index, Type Val)
    {
        UserIndexAssertion(Index);
        _Arr[Index] = Val;
    }

    void Expand_Size()// size *= 15
    {
        Type* old = _Arr;
        _Arr = new Type[_Size * 15];//انا هنا هيأت مكان جديد في الheap
        for (short i = 0; i < _Length; i++)
            i[_Arr] = *(old + i);//Bomm

        delete[] old;
        old = nullptr;
    }

    ////////
    void  UserIndexAssertion(short Index)
    {
        assert(Index >= 0 && Index < _Length);
    }
    ////////////
    void Delete(short idx)
    {
        if (IsEmpty())
        {
            cout << "Empty\n";
            return;
        }
        UserIndexAssertion(idx);
        for (short i = idx; i < _Length - 1; i++)
            _Arr[i] = _Arr[i + 1];
        _Length--;
    }
    /////////
    short& operator[](short idx)
    {
        UserIndexAssertion(idx);

        return _Arr[idx];
    }
    /////////assignment operator
    /// Arr4 = Arr1 ==> Arr4.operator=(Arr1)
    void operator=(const ArrayList& source)
    {
        //check if list1=list1 fault from user
        if (this != &source)
        {
            delete[]_Arr;
            _Size = source._Size;
            _Length = source._Length;
            _Arr = new Type[_Size];
            for (short i = 0; i < _Length; i++)
                _Arr[i] = source._Arr[i];
        }
        else
            return;
    }
    //////////////////replace at(idx,val)
    void Set(short idx, Type& val)
    {
        UserIndexAssertion(idx);
        _Arr[idx] = val;
    }
    /////////
    Type Max()
    {
        if (IsEmpty())
        {
            cout << "Empty Array\n";
            return -1;
        }
        Type ma = _Arr[0];
        for (short i = 1; i < _Length; i++)
        {
            if (_Arr[i] > ma)
                ma = _Arr[i];
        }
        return ma;
    }
    ////////////
    Type Min()
    {
        if (IsEmpty())
        {
            cout << "Empty Array\n";
            return -1;
        }
        Type mi = _Arr[0];
        for (short i = 1; i < _Length; i++)
        {
            if (_Arr[i] < mi)
                mi = _Arr[i];
        }
        return mi;
    }
    ///////Sequential search
    short SequentialSearch(Type val)
    {
        if (IsEmpty())
        {
            cout << "Empty Array\n";
            return -1;
        }
        for (short i = 0; i < _Length; i++)
        {
            if (_Arr[i] == val)
                return i;
        }
        return -1;
    }
    //Binary Search-->Worked With A Sorted Array
    short BinarySearch(Type item)
    {
        if (IsEmpty())
        {
            cout << "Array is Empty\n";
            return -1;
        }
        //Binary Search-->Worked With A Sorted Array
        Sort();
        short Left = 0;
        short Right = _Length - 1;
        short Middle = 0;
        while (Left <= Right)
        {
            Middle = Left + (Right - Left) / 2;

            // Check if x is present at mid
            if (_Arr[Middle] == item)
                return Middle;

            // If x greater, ignore left half
            if (_Arr[Middle] < item)
                Left = Middle + 1;

            // If x is smaller, ignore right half
            else
                Right = Middle - 1;
        }

        // if we reach here, then element was
        // not present
        return -1;
    }
    ///////////////////
    void Sort()
    {
        if (IsEmpty())
        {
            cout << "Empty Array\n";
            return;
        }
        for (int i = 0; i < _Length - 1; i++)
            for (int j = 0; j < _Length - 1; j++)
                if (_Arr[j] > _Arr[j + 1])
                {
                    swap(_Arr[j], _Arr[j + 1]);
                }
    }
    //
    void push_Front(Type val)
    {
        Insert(0, val);
    }

    void push_Back(Type val)
    {
        Append(val);
    }
    ///////////
    void PopFront()
    {
        Delete(0);
    }

    void PopBack()
    {
        Delete(_Length-1);
    }
    void right_rotate()
    {
        Type temp = _Arr[_Length - 1];
        for (short i = _Length - 1; i >= 0; i--)
            _Arr[i] = _Arr[i - 1];
        _Arr[0] = temp;
    }
    //
    void right_rotate(short times)
    {
        short newTimes = times % _Length; //Thanks God I Discoverd it Before Watching 
        for (short i = 1; i <= newTimes; i++)
            right_rotate();
    }
    //
    void left_rotate()
    {
        Type temp = _Arr[0];
        for (short i = 0; i < _Length - 1; i++)
            _Arr[i] = _Arr[i + 1];
        _Arr[_Length - 1] = temp;
    }

    void left_rotate(short Times)
    {
        short newTimes = Times % _Length; //Thanks God I Discoverd it Before Watching 
        for (short i = 1; i <= newTimes; i++)
            left_rotate();
    }
    /*each time you find the value, you shift it one step to the left
    Eventually, the values that are queried a lot, will move to the head of array
    It returns the found position, but consider moving it one step to the left*/

    short find_transposition(Type value)
    {
        short check = Search(value);
        if (check == -1)
        {
            cout << "Not Found\n\n";
            return 0;// index 0 in array => means pos 1 in here
        }
        else
        {
            if (check == 0)
                return check;
            else
            {
                swap(_Arr[check], _Arr[check - 1]);
                return check - 1;
            }
        }
    }

};
/*الحم لله رب العالمين*/

//Template Functoin
template<typename Type>
 Type Min(Type Num1, Type Num2)
{
    return (Num1 < Num2) ? Num1 : Num2;
}

int main()
{
    ArrayList<short>arr(10);
    arr.Append( 100);
    arr[0] = 200;
    arr.Print();


    return 0;
}
