#include <iostream>
using namespace std;
template<class Type>
class clsDequeue
{
private:
    Type* _Queue = nullptr;
    int _Size;
    int _Front, _Rear;
public:
    clsDequeue(int size)
    {
        _Size = size;
        _Front = _Rear = -1;
        _Queue = new Type[size];
    }
    //////////
    bool isEmpty()
    {
        return(_Front == -1 && _Rear == -1);
    }
    /////////////
    bool isFull()
    {
        return((_Rear + 1) % _Size == _Front);
    }
    //////////
    void enQueueRear(Type val)
    {
        if (isFull())
        {
            cout << "Queue is full\n";
            return;
        }
        if (isEmpty())
            _Front = _Rear = 0;
        else
            _Rear = (_Rear + 1) % _Size;

        _Queue[_Rear] = val;
    }
    /////////
    bool enQueueFront(Type val)
    {
        if (isFull())
            return false;

        if (isEmpty())
            _Front = _Rear = 0;

        else if (_Front == 0)
            _Front = _Size - 1;

        else
            _Front--;

        _Queue[_Front] = val;
        return true;
    }

    bool deQueueFront()
    {

        if (isEmpty())
        {
            cout << "Queue is Empty\n";
            return false;
        }
        if (_Rear == _Front)//just one element
        {
            _Front = _Rear = -1;
        }
        else
        {
            _Front = (_Front + 1) % _Size;
        }
        return true;
    }

    bool dequeueRear()
    {
        if (isEmpty())
            return false;

        if (_Front == _Rear)//just one element
            _Front = _Rear = -1;

        else if (_Rear == 0)
            _Rear = _Size - 1;

        else
            _Rear--;

        return true;
    }

    /////////
    void Display()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty\n";
            return;
        }
        for (int i = _Front; i != _Rear; i = (i + 1) % _Size)
            cout << _Queue[i] << " ";

        cout << _Queue[_Rear];
        cout << endl;
    }
    ////////
    Type Front()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty\n";
            return -1;
        }
        return _Queue[_Front];
    }
    ////////
    Type Rear()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty\n";
            return -1;
        }
        return _Queue[_Rear];
    }
    /////////
};
int main()
{
    return 0;
}
