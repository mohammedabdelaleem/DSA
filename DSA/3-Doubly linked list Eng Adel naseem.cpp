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

    void display()
    {
            Node*temp=front;
            if(temp==null)
            {
                cout<<"Empty Linked List\a\n";
                return;
            }

            cout<<"Elements : ";
            while(temp!=null)
            {
                cout<<temp->data<<" ";
                temp=temp->next;
            }
            cout<<endl;
        }

    void displayReverse()
    {
        Node*temp=tail;
        if(temp==null)
        {
            cout<<"Empty Linked List\a\n";
            return;
        }

        cout<<"Elements : ";
        while(temp!=null)
        {
            cout<<temp->data<<" ";
            temp=temp->prev;
        }
        cout<<endl;
    }

    int getLength()
    {
        return length;
    }

    void destroy(){//////////////////
        if(length==0)
        {
            cout<<"Empty Linked List...cannot destroy\a\n";
            return;
        }

                Node*temp;
        while(front!=null)//front not temp ********************************
        {
            temp=front;
            front=front->next;
            delete temp;
        }
        tail=null;
        length=0;
        cout<<"Destroyed successfully\n\a";
    }

    void delete_all_nodes_with_key(int value)
    {
        if(!length)
        {
            cout<<"ERROR : Empty Linked list\a\n";
            return;
        }
        insertFirst(-value);//insert dummy value - value no overflow

        for(Node*cur=front; cur;)
        {
            if(cur->data==value)
            {
                cur=DeleteAndLink(cur);
                if(!cur->next)
                    tail=cur;
            }
            else
                cur=cur->next;
        }
        deleteFirst();
        debug_verify_data_integrity();
    }

    //data integrity
    debug_verify_data_integrity()
    {
        if(length==0)
        {
            assert(front==null);
            assert(tail==null);
        }
        else
        {
            assert(front!=null);
            assert(tail!=null);

            if(length==1)
                assert(front==tail);

            else
            {
                assert(front!=tail);
                assert(!tail->next);
            }
        }
        int idx=0;
        Node*temp=front;
        while(temp)
        {
            idx++;
            temp=temp->next;
            assert(idx<10000);//consider infinite cycle
        }
        assert(idx==length);
    }

     void delete_even_positions()
     {
  if(length<=1)
        {
            cout<<"ERROR : Empty Linked list\a\n";
            return;
        }
        for(Node*temp=front ; temp &&temp->next ; temp=temp->next)
        {
            DeleteAndLink(temp->next);

            if(!temp->next)
                tail=temp; //in the even length the tail will change.
        }
        debug_verify_data_integrity();
    }

    void delete_odd_positions()
    {
        //let us make odd positions even (reuse old code)
        insertFirst(INT_MIN);
        delete_even_positions();
        deleteFirst();
    }

    bool isPalandrom()
    {
        if(length<=1)
            return true;

        int len=length/2;
        Node*first{front},*last{tail};

        while(len--)
        {
            if(first->data!=last->data)
                return false;

            first=first->next;
            last=last->prev;
        }
              return true;
    }

    int findMiddle1()// iterate from both directions same time
    {
       assert(front);

        Node*first=front,*last{tail};

        while(first!=last && first->next!=last)
            first=first->next,last=last->prev;
        return last->data;
    }

    int findMiddle2()// iterate from both directions same time
    {
        /*
		 * The idea is simple but smart!
		 * use 2 pointers
		 * The first (slow) moves normally step by step
		 * The second (fast) jump 2 steps each time!
		 * If the list has e.g. 10 elements
		 * When the slow in the middle (e.g. 5), the fast is at the double (10)
		 * From that we know we found the middle.
		 */
      assert(front);

        Node*fast=front,*slow{front};

        while(fast && fast->next)
        {
            fast=fast->next->next; // Hare: jump 2 steps
            slow=slow->next;      // Tortoise
        }
       return slow->data;
    }

    Node* get_previous(Node* target) {		// O(n) time - O(1) memory
		for (Node *cur = front; cur; cur = cur->next) {
			if (cur == target)	// memory wise
				return cur->prev;
		}
		return nullptr;	// still more steps needed - NOT found
	}

    void swap_front_with_tail()
    {
        if(length<=1)
            return;

        cout<<"front address (before swapped): "<<front<<endl;
        cout<<"tail address (before swapped): "<<tail<<endl;

        Node*preTail=get_previous(tail);

        // Let's make current tail as head
        // Link tail to the 2nd node
        tail->next=front->next;
        tail->prev=nullptr;

// Let's make current head as tail
        // Link tail's previous to head
        preTail->next=front;
        front->next=nullptr;

        swap(tail, front);	// Set new head and tail
        debug_verify_data_integrity();

        cout<<"\nfront address (after swapped): "<<front<<endl;
        cout<<"tail address (after swapped): "<<tail<<endl<<endl;;

    }

    swapThoseNodes(Node*h,Node*t)
    {
        cout<<"Old Address :"<<h<<endl;
        cout<<"Old Address :"<<t<<endl;

        Node*temp=h;
        h=t;
        t=temp;

        cout<<"new Address :"<<h<<endl;
        cout<<"new Address :"<<t<<endl;


    }


    void Swap_forward_with_backward(int key)
    {
        if(length<=1 || key+1<length/2)
            return ;

            if(key==1)
                swap_front_with_tail();
            else{
        Node*h=front,*t=tail;
        for(int i=1; i<key; i++)
        {
            h=h->next;
            t=t->prev;
        }
        swapThoseNodes(h,t);
    }
}
}l;

int main()
{
  //  doublyLinkedList l;

   l.insertFirst(10);
    l.insertLast(20);
    l.insertLast(30);
    l.insertLast(40);
    l.insertLast(50);

    l.insertLast(60);
    l.insertLast(70);
    l.insertLast(80);
    l.insertLast(90);
    l.insertLast(100);



l.swap_front_with_tail();
//l.display();


    return 0;
}
