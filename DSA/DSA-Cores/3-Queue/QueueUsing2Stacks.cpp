#include <iostream>
using namespace std;

/*
Steps:
    1-Make 2 Stacks.
    2-Enqueue In The First Stack.
    3-Dequeue Steps: 1-Pop The Whole Elements From The First Stack into The Second , 2-Pop The Top From The Second , 3-Pop The Whole Elements From The Second Stack into The First  .
    4-Display By A Counter From 0 To Top1;
*/



class clsQueue
{
private:
    int top1, top2;
    int size;
    int* Stack1 = nullptr;
    int* Stack2 = nullptr;
public:
    clsQueue(int size)
    {
        this->size = size;
        top1 = top2 = -1;
        Stack1 = new int[size];
        Stack2 = new int[size];
    }
    //Stack 1 fun()s
    bool isEmpty1()
    {
        return(top1 == -1);
    }
    //
    bool isFull1()
    {
        return (top1 == size - 1);
    }
    //
    void push1(int val)
    {
        if (isFull1())
        {
            cout << "Queue OverFlow\n";
            return;
        }
        //else
        Stack1[++top1] = val;
    }
    //
    int pop1()
    {
        int val = -1;
        if (isEmpty1())
            return val;

        else
            val = Stack1[top1];
        top1--;

        return val;
    }
    //
    //Stack 2 fun()s
    bool isEmpty2()
    {
        return(top2 == -1);
    }
    //
    bool isFull2()
    {
        return (top2 == size - 1);
    }
    //
    void push2(int val)
    {
        if (isFull2())
        {
            cout << "Queue OverFlow\n";
            return;
        }
        //else
        Stack2[++top2] = val;
    }
    //
    int pop2()
    {
        int val = -1;
        if (isEmpty2())
            return val;

        else
            val = Stack2[top2];
        top2--;

        return val;
    }
    ////*//////////
    void enQueue(int val)
    {
        push1(val);
    }
    ////*////
    void deQueue()
    {
        while (!isEmpty1())
            push2(pop1());

        pop2();

        while (!isEmpty2())
            push1(pop2());
    }
    ////*//////
    void display()
    {
        if (isEmpty1())
        {
            cout << "Queue UnderFlow\n";
            return;
        }

        for (int i = 0; i <= top1; i++)
            cout << Stack1[i] << " ";
        cout << endl;
    }
} q1(10);

int main()
{
    q1.enQueue(10);
    q1.enQueue(20);
    q1.enQueue(30);
    q1.enQueue(40);
    q1.deQueue();
    q1.deQueue();
    q1.enQueue(10);

    q1.display();
    return 0;
}
