#include <iostream>
#include <iomanip>
using namespace std;

//template<class t>
struct item
{
    int value;
    int pri;
};

//template<class t>
class priorityQueue
{
private:
    item* queue;
    int size;
    int front, rear;
public:
    priorityQueue(int size)
    {
        this->size = size;
        front = rear = -1;
        queue = new item[size];
    }
    //////////
    bool isEmpty()
    {
        return(front == -1 && rear == -1);
    }
    /////////////
    bool isFull()
    {
        return((rear + 1) % size == front);
    }
    //////////
    void enQueue(int val, int p)
    {
        if (isFull())
        {
            cout << "Queue is full\n";
            return;
        }
        if (isEmpty())//it will be the first element , we won't need to sort
        {
            front = rear = 0;
            queue[rear].value = val;
            queue[rear].pri = p;
        }
        else
        {
            rear = (rear + 1) % size;
            queue[rear].value = val;
            queue[rear].pri = p;

            insertionSort();
        }
    }
    /////
    void insertionSort()
    {
        item temp;
        for (int i = 1; i <= rear; i++)
        {
            temp = queue[i];//both are the same datatype
            int j = i - 1;

            while (j >= 0 && temp.pri < queue[j].pri)
            {
                queue[j + 1] = queue[j];
                j--;
            }
            queue[j + 1] = temp;
        }
    }
    /////////
    void Display()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty\n";
            return;
        }
        for (int i = front; i != rear; i = (i + 1) % size)
            cout << setw(15)<<left<<"Queue's Value: " << queue[i].value << setw(5) << left<<" ->" << "Queue's priority: " << queue[i].pri << "\n";

        cout << setw(15) << left << "Queue's Value: " << queue[rear].value << setw(5) << left << " ->"<<"Queue's priority: " << queue[rear].pri << "\n";
        cout << endl;
    }
    ////////
    int Front()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty\n";
            return -1;
        }
        return queue[front].value;
    }
    ////////
    int Rear()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty\n";
            return -1;
        }
        return queue[rear].value;
    }
    /////////
    bool deQueue()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty\n";
            return false;
        }
        int x = -1;
        if (rear == front)
        {
            x = queue[front].value;
            front = rear = -1;
        }
        else
        {
            x = queue[front].value;
            front = (front + 1) % size;
        }
        return true;
    }

};
int main()
{
    priorityQueue* q1 = new priorityQueue(10);
    q1->enQueue(150, 4);
    q1->enQueue(10, 2);
    q1->enQueue(150, 1);
    q1->enQueue(100, 3);
    q1->enQueue(30, 41);
    q1->enQueue(80, 0);

    q1->Display();
    return 0;
}
