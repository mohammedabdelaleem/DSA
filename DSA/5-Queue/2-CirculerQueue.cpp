#include <iostream>
using namespace std;

template<class Type>
class circularQueue
{
private:
    Type* _Queue = nullptr;
    int _Size;
    int _Front, _Rear;
public:
    circularQueue(int size=0)
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
    void enQueue(Type val)
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
    bool dnQueue()
    {

        if (isEmpty())
        {
            cout << "Queue is Empty\n";
            return false;
        }
        if (_Rear == _Front)//Only One Element
        {
            _Front = _Rear = -1;
        }
        else
        {
            _Front = (_Front + 1) % _Size;
        }
        return true;
    }

};
int main()
{
    circularQueue<int>cq(4);
    cq.enQueue(10);
    cq.enQueue(20);
    cq.enQueue(30);
    cq.enQueue(40);
    cq.dnQueue();
    cq.enQueue(50);

    cq.Display();
    return 0;
}
