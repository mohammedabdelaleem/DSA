#include <iostream>
#include <assert.h>
#include <cstring>
#include <fstream>

#define null NULL
using namespace std;
class Node
{
public:
    int data;
    Node*next;
    Node*prev;
    //Default Constructor
    Node(int data=0)
    {
        data=0;
        next=prev=NULL;
    }

  /*  //prametrised Constructor
    Node(int data)
    {
        this->data=data;
        this->next=NULL;
        this->prev=NULL;
    }*/

    //Destructor
    ~Node()
    {
       cout<<"Destroyed data "<<data<<" at address "<<this <<endl;
    }
};

class doublyLinkedList
{
private:
    int length=0;//to know number of nodes
    Node*front,*tail;
public:
    doublyLinkedList() {}
    doublyLinkedList(const doublyLinkedList&source)=delete;
    //doublyLinkedList &operator=(const doublyLinkedList&source)=delete;

    ~doublyLinkedList()
    {
   while(tail)//  || front ya [Strong SWE]
   {
       Node*temp=tail->prev;
       delete tail ;
       tail=temp;
   }
    }
    void insertFirst(int data)
    {
        Node*newNode=new Node(data);
        if(length==0)
        {
            front=tail=newNode;
           // newNode->next=newNode->prev=null;//By default => null
        }
        else
        {
            newNode->next=front;
            newNode->prev=null;
            front->prev=newNode;///////////
            front=newNode;
        }
        length++;
    }

    void insertLast(int data)
    {
        Node*newNode=new Node(data);
        if(length==0)
        {
            front=tail=newNode;
            //newNode->next=newNode->prev=null;//By default => null
        }
        else
        {
            newNode->next=null;
            newNode->prev=tail;
            tail->next=newNode;
            tail=newNode;
        }
        length++;
    }

    void isnertAt(int pos,int val)
    {
        if(pos<0 || pos>length)
        {
            cout<<"ERROR: position not found\a\n";
            return;
        }
        else
        {
            if(pos==0)
            {
                insertFirst(val);
            }
            else if(pos==length)/////
            {
                insertLast(val);
            }
            else
            {
                Node*newNode=new Node(val);
                Node*temp=front;

                for(int i=1; i<pos; i++)
                    temp=temp->next;

                newNode->next=temp->next;
                newNode->prev=temp;
                temp->next->prev=newNode;
                temp->next=newNode;//focus on ordering operations

                length++;
            }
        }
    }

    /////////////////
    Node*GetNode(int idx)
    {
        if(idx>length || idx<0)
        {
            return null;
        }
        int c=0;
        for(Node*current=front; current; current=current->next)
        {
            if(c++ ==idx)
                return current;
        }
        return nullptr;
    }

    ///////////
    void addAfter(int N_val,int val)
    {
        int idx=Search(N_val);
        if(idx==-1)
        {
            cout<<"\a";
            return;
        }
        Node*temp=GetNode(idx);

        Node*newNode=new Node(val);

        newNode->next=temp->next;
        newNode->prev=temp;
        temp->next=newNode;
        length++;
    }
    //////////
    void insert_2be_sort(int val)
    {
        if(!length || val<=front->data)
            insertFirst(val);

        else if(val>=tail->data)
            insertLast(val);

        else
        {
            for(Node*cur=front,*prev ; cur ; prev=cur, cur=cur->next)
            {
                if(cur->data>=val)
                {
                    addAfter(prev->data, val);
                    break;
                }
            }
        }
    }
    //////
     int Search(int item)
    {
        int idx=-1;

        if(length==0)
            return idx;
        else if(front->data==item)
            return 0;//because of idx
        else if(tail->data==item)
            return length-1;
        else
        {
            Node*temp=front->next;//i provide one step  && modify the idx value
            while(temp->next!=null)
            {
                idx++;
                if(temp->data==item)
                {
                    return idx+1;
                }

                temp=temp->next;
            }
        }
        idx=-1;
        return idx;
    }
    ///////////

void Link(Node*first,Node*second)
{
    if(first)
        first->next=second;

    if(second)
        second->prev=first;
}
//////
void delete_node(Node*n)
{
    Link(n->prev,n->next);
    delete n;
    length--;
}
//////
Node*DeleteAndLink(Node*cur)
{
    /*
Given a node, connect its previous and next, and then delete it
○ Return the previous node
*/
    if(cur==front)
    {
        deleteFirst();
        return null;
    }
    Node*ret=cur->prev;
    Link(cur->prev,cur->next);
    delete_node(cur);
    return ret;
}

    void deleteFirst()
    {
        if(length==0)
        {
            cout<<"ERROR: position not found\a\n";
            return;
        }
        if(length==1)
        {
            free(front);
            front=tail=null;
        }
        else
        {
            Node*temp=front;
            front=front->next;
            front->prev=null;
            delete temp;
        }
        length--;
    }

    void deleteLast()
    {
        if(length==0)
        {
            cout<<"ERROR: position not found\a\n";
            return;
        }
        if(length==1)
        {
            free(front);
            front=tail=null;
        }
        else
        {
            //جامد
            Node*temp=tail;
            tail=tail->prev;
            tail->next=null;
            delete temp;
        }
        length--;
    }

    void deleteAt(int pos)
    {
        if(length==0)
        {
            cout<<"ERROR:Empty Linked List\a\n";
            return;
        }
        if(pos<0 || pos>length)
        {
            cout<<"ERROR: position not found\a\n";
            return;
        }

        if(pos==0)
        {
            deleteFirst();
        }
        else if(pos==length)
        {
            deleteLast();
        }
        else
        {
            Node*temp=front;
          //  Node*ptemp=null;

            for(int i=1; i<=pos; i++)
            {
                //ptemp=temp;
                temp=temp->next;
            }
            temp->prev->next=temp->next;
            temp->next->prev=temp->prev;
            delete temp;
            length--;
        }
    }

    void Delete(int item)
    {
        int idx=Search(item);
        if(idx>=0 && idx<length)
        {
       Node*temp=GetNode(idx);
       DeleteAndLink(temp);
        }
        /*
        if(length==0)
        {
            cout<<"ERROR: Empty Linked List\a\n";
            return;
        }

        if(front->data==item)
            deleteFirst();

        else if(tail->data==item)
            deleteLast();

        else
        {
            Node*temp=front;
            while(temp!=null && temp->data!=item)
            {
                temp=temp->next;
            }
            if(temp==null)
            {
                cout<<"item "<<item<<" not found\a\n";
                return;
            }
            else
            {
                temp->prev->next=temp->next;
                temp->next->prev=temp->prev;
                delete temp;
                length--;
            }
        }*/
    }
