#include <iostream>
using namespace std;

template<class t>
class SimpleQueue
{
private:
    t *queue=nullptr;
    int size;
    int front,rear;
public:
    SimpleQueue(int size)
    {
        this->size=size;
        front=rear=-1;
        queue=new t[size];
    }
    //////////
    bool isEmpty()
    {
        return(front==-1 && rear==-1);
    }
    /////////////
    bool isFull()
    {
        return(rear==size-1);
    }
    //////////
    void enQueue(t val)
    {
        if(isFull())
        {
            cout<<"Queue is full\n";
            return;
        }
        if(isEmpty())////////////
            front=rear=0;
        else
            rear++;

        queue[rear]=val;
    }
    /////////
    void Display()
    {
        if(isEmpty())
        {
            cout<<"Queue is Empty\n";
            return;
        }
        for(int i=front; i<=rear; i++)
            cout<<queue[i]<<" ";
        cout<<endl;
    }
    ////////
    t Front()
    {
        if(isEmpty())
        {
            cout<<"Queue is Empty\n";
            return -1;
        }
        return queue[front];
    }
    ////////
    t Rear()
    {
        if(isEmpty())
        {
            cout<<"Queue is Empty\n";
            return -1;
        }
        return queue[rear];
    }
    /////////
    t deQueue()
    {
        t key=-1;
        if(isEmpty())
        {
            cout<<"Queue is Empty\n";
            return key;
        }
        if(rear==front)//////////////////
        {
            key=queue[front];
            front=rear=-1;
        }
        else
        {
            key=queue[front];
            front++;
        }
        return key;
    }

};
int main()
{
    SimpleQueue<int>*q1=new SimpleQueue<int>(10);
    q1->enQueue(10);
    q1->enQueue(20);
    q1->enQueue(30);
    //q1->Display();
    cout<<q1->deQueue();
    cout<<q1->deQueue();
    cout<<q1->deQueue();


    return 0;
}
