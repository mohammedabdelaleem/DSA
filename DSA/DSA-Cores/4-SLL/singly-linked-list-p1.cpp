#include <iostream>
#include <cassert>
#include <climits>
#include<windows.h>
#include<unistd.h>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <sstream>
#define null 0
using namespace std;

struct Node
{
    int data;
    Node*next;

    //Default Constructor
    Node()
    {
        data=0;
        next=NULL;
    }

    //prametrised Constructor
    Node(int data)
    {
        this->data=data;
        this->next=NULL;
    }

    //Destructor
    ~Node()
    {
        cerr<<"Destroy Value "<<data<<" at address "<<this<<endl;
    }
};

class LinkedList
{
private:
    Node*front;//points to the front of the linked list => it's make insertion from the head O(1)
    Node*tail;//points to the end of the linked list => it's make deletion from the tail O(1)
    int length=0;//to know number of nodes in linked list

    vector<Node*> debug_data;	// add/remove nodes you use

	void debug_add_node(Node* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node) {
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}

public:
    LinkedList() {}
    LinkedList(const LinkedList&) = delete;//delete copy constructor
    LinkedList &operator=(const LinkedList &another) = delete;////delete assignment op

    //////////////////////////////New Functions/////////////////////////////////
    ~LinkedList()  		// O(n) time - O(1) memory
    {
        // idea: get next first, remove current front
        while(front)
        {
            Node* current = front->next; //1
            delete front; //2
            front = current;//3
        }
    }

    //////////////Addition
    void addFrist(int data)
    {
        Node*newNode=new Node(data);
        if(length==0)
        {
            front=tail=newNode;
            newNode->next=NULL;//by default
        }
        else
        {
            newNode->next=front;//new node first => first node
            front=newNode;
        }
        length++;
    }

    //////////////
    void addLast(int data)
    {
        Node*newNode=new Node(data);
        if(length==0)
        {
            front=tail=newNode;
            newNode->next=NULL;
        }
        else
        {
            tail->next=newNode;
            newNode->next=NULL;
            tail=newNode;
        }
        length++;
    }

    ///////////////
    void addAtPos(int pos,int data)
    {
        if(pos<0 || pos>length)
        {
            cout<<"Out Of Range\a\n";
            return;
        }
        else
        {
            if(pos==0)
                addFrist(data);
            else if(pos==length)
                addLast(data);
            else
            {
                Node*newNode=new Node(data);
                Node*temp=front;
                for(int i=0; i<pos-1; i++)//pos-1
                {
                    temp=temp->next;
                }
                newNode->next=temp->next;
                temp->next=newNode;//

                length++;
            }
        }
    }

    void addAfter(int N_val,int val)
    {
        if(length<=0)
        {
            cout<<"Empty Linked List\n\a";
            return;
        }

        int idx=Search(N_val);
        if(idx==-1)
        {
            cout<<N_val<<" Not Found \n";
            return;
        }

        Node*temp=GetNode(idx);

        Node*newNode=new Node(val);
        newNode->next=temp->next;
        temp->next=newNode;
        length++;
    }
    ////////////

    //////////
    void insert_2be_sort(int val)
    {
        if(!length || val<=front->data) // !length: This is checking if the linked list has a length of zero.
            addFrist(val);

        else if(val>=tail->data)
            addLast(val);

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

    void print()
    {
        if(length==0)
        {
            cout<<"EMPTY LINKED LIST\n\a";
        }
        Node*current = front;
        while (current != NULL)
        {
            cout << current->data << "  ";
            current = current->next;
        }
        cout<<endl;
    }

//////////////Deletion
    void deleteFirst()
    {
        if(length==0)
        {
            cout<<"Error :Empty Linked List\a\n";
            return;
        }
        //
        if(length==1)
        {
            delete front;//formate front  =>Don't forget//////////////////////////////
            front=tail=NULL;//[reset/Update]
        }
        else
        {
            Node*temp=front;
            front=front->next;
            free(temp);
        }
        length--;
    }

    /////////
    void deleteLast()
    {
        if(length==0)
        {
            cout<<"Error :Empty Linked List\a\n";
            return;
        }
        //
        if(length==1)
        {
            delete front;//formate front
            front=tail=NULL;//[reset/Update]
        }
        else
        {
            Node*current=front;
            while(current->next!=tail)
                current=current->next;

            free(tail);
            current->next=null;
            tail=current;
        }
        length--;
    }

    void deleteAt(int idx=0)
    {
        if(idx<0 || idx>=length)
        {
            cout<<"ERROR : OUT OF RANGE\a\n";
            return;
        }

        if(idx==0)
            deleteFirst();

        else if(idx==length-1)
            deleteLast();

        else
        {
            Node*temp=front->next;
            Node*ptemp=front;
            for(int i=1; i<idx; i++)
            {
                ptemp=temp;
                temp=temp->next;
            }
            ptemp->next=temp->next;
            free(temp);
        }
    }

//////////
    void deleteElement(int element)
    {
        int check=Search(element);
        if(check==-1)
        {
            cout<<element<<" Not Found Can not Delete\a\n";
            return;
        }
        else if(check==0)
        {
            deleteFirst();
        }
        else if(tail->data==element)//check==lenght
        {
            deleteLast();
        }
        else
        {
            Node*temp=front;
            Node*ptemp=null;
            while(temp->next!=null)
            {
                if(temp->data==element)
                {
                    ptemp->next=temp->next;
                    free(temp);
                    break;
                }
                ptemp=temp;
                temp=temp->next;
            }
            free(temp);
        }
    }

    ///////
    int Search(int item)//return index of the node if found
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
                    return idx+1;//i started with -1 and temp=front->next not front
                }

                temp=temp->next;
            }
        }
        idx=-1;
        return idx;
    }

    int getLength()
    {
        return length;
    }

  /*  void Reverse()//for only one ptr[front]
    {
        Node *prev, *Next, *curr;//Next is a holder of the reminder nodes in the linked list before cutting
        prev = NULL;
        curr = front;
        Next = curr->next;
        while (Next != NULL)//curr!=NULL
        {
            Next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = Next;
        }
        front = prev;
    }*/

    void reverse() {		// O(n) time - O(1) memory
		if (length <= 1)
			return;

		tail = front;
		Node *prv = front;
		front = front->next;
		while (front) {
			// store & reverse link
			Node* next = front->next;
			front->next = prv;

			// move step
			prv = front;
			front = next;
		}
		// Finalize front and tail
		front = prv;
		tail->next = nullptr;

		debug_verify_data_integrity();
	}

    //data integrity
   void debug_verify_data_integrity() {
		int len = 0;
		for (Node* cur = front; cur; cur = cur->next, len++)
			;

		assert(length == len);
		//assert(length == (int)debug_data.size());

		if (length == 0) {
			assert(front == nullptr);
			assert(tail == nullptr);
		} else {
			assert(front != nullptr);
			assert(tail != nullptr);

			if (length == 1)
				assert(front == tail);
			else
				assert(front != tail);
		}
	}

///// convert to string
    string debug_to_string()
    {
        if(length==0)
            return "";

        ostringstream oss;
        Node*temp=front;
        while(temp!=null)
        {
            oss<<temp->data;
            if(temp->next)
                oss<<" ";
        }
        return oss.str();
    }

    void clearLinkedList()
    {
        if(length==0)
        {
            cout<<"ERROR : Empty Linked List \a\n";
            return;
        }
        if(length==1)
            deleteFirst();
        else
        {
            while(front)
            {
                Node* current=front->next;
                delete(front);
                front=current;
            }
        }
    }

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

