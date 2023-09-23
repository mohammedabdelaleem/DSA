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

    //////////Problem #4: Get nth from back///////////
    Node*getNthFromBack(int idx)
    {
        if(idx<0 || idx>length)
            return nullptr;

        else
            GetNode(length-idx);
    }

    bool is_the_same(const LinkedList&another)
    {

        if(length!=another.length)
            return false;

        Node*curr=front;
        Node*curr2=another.front;
        while(curr)
        {
            if(curr->data != curr2->data)
            {
                return false;
                break;
            }
            curr=curr->next;
            curr2=curr2->next;
        }
        return true;
    }

    void delete_even_positions()
    {
        int idx=(length/2);
        for(int i=1; i<=idx; i++)
            deleteAt(i);
    }

    ////////////////////////////////////////////////////////////
    Node* get_previous(Node* target)  		// O(n) time - O(1) memory
    {
        for (Node *cur = front, *prv = nullptr; cur; prv = cur, cur = cur->next)
        {
            if (cur == target)	// memory wise
                return prv;
        }
        return nullptr;	// still more steps needed - NOT found
    }

    void swapHeadTail()
    {
        if(length <= 1)
            return;

        cout<<"front address (before swapped): "<<front<<endl;
        cout<<"tail address (before swapped): "<<tail<<endl;

        Node*preTail=get_previous(tail);

        // Let's make current tail as head
        // Link tail to the 2nd node
        tail->next = front->next;

        // Let's make current head as tail
        // Link tail's previous to head
        preTail->next=front;
        front->next=nullptr;

        swap(tail, front);	// Set new head and tail

        debug_verify_data_integrity();

        cout<<"\n=======================================\n";
        cout<<"front address (after swapped): "<<front<<endl;
        cout<<"tail address (after swapped): "<<tail<<endl<<endl;
    }

// These 2 simple functions just to not forget changing the vector and length
	void delete_node(Node* node) {
		debug_remove_node(node);
		--length;
		delete node;
	}

	void add_node(Node* node) {
		debug_add_node(node);
		++length;
	}

	void delete_next_node(Node* node) {
		// Delete the next of the current node
		// Handle if next is tail case
		assert(node);

		Node* to_delete = node->next;
		bool is_tail = to_delete == tail;

		// node->next in middle to delete
		node->next = node->next->next;

		delete_node(to_delete);
		if (is_tail)
			tail = node;
	}

    	void remove_duplicates_from_not_sorted() {		// O(n^2) time - O(1) memory
		if (length <= 1)
			return;

		// Just like 2 nested loops, find all duplicates and delete

		for (Node *cur1 = front; cur1; cur1 = cur1->next) {
			for (Node *cur2 = cur1->next, *prv = cur1; cur2;) {
				if(cur1->data == cur2->data) {
					delete_next_node(prv);
					cur2 = prv->next;
				} else
					prv = cur2, cur2 = cur2->next;	// normal move
			}
		}
		debug_verify_data_integrity();
	}

     void Sort() {
        if (front == NULL || front->next == NULL) {
            return;
        }
        Node *i, *j;
        int temp;

        for (i = front; i != NULL; i = i->next) {
            for (j = i->next; j != NULL; j = j->next) {
                if (i->data > j->data) {
                    temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
        }
    }

    Node* get_nth(int n) {		// O(n) time - O(1) memory
		int cnt = 0;
		for (Node* cur = front; cur; cur = cur->next)
			if (++cnt == n)
				return cur;

		return nullptr;
	}

	void left_rotate(int k) {		// O(n) time - O(1) memory
		if(length <= 1 || k % length == 0)
			return;	// 0 or 1 elements or useless rotation
		k %= length;	// Remove useless cycles

		Node* nth = get_nth(k);
		tail->next = front;		// create cycle

		// Reset tail/front
		tail = nth;
		front = nth->next;

		tail->next = nullptr;	// disconnect cycle
		debug_verify_data_integrity();
	}
   int& operator[](int index) {
        int count = 0;
        Node* current_node = front;
        while (current_node != NULL) {
            if (count == index) {
                return current_node->data;
            }
            count++;//normal move
            current_node = current_node->next;//
        }
    }
} obj;
//functions i need
void _interface();
void print_nchars_line(char c, int counter);
void moveCursor(int col, int row);
void loading();

void handleInsertion();
void handleDeletion();
void handleSearching();
void handleSorting();

void handleDuplication();
void handleRotation();
int main()
{
    _interface();
    return 0;
}

void _interface()
{
    int choice1;
    char choice2;
    do
    {
        do
        {
            system("cls");
            cout<<"\t\t***Linked List Implementation***\n";
            cout<<"\t\t\t  1-Is Empty ?\n"<<
                "\t\t\t  2-Insert\n"<<
                "\t\t\t  3-Delete\n"<<
                "\t\t\t  4-Print\n"<<
                "\t\t\t  5-Search\n"<<
                "\t\t\t  6-Sort\n"<<
                "\t\t\t  7-Reverse\n"<<
                "\t\t\t  8-Remove Duplicated\n"<<
                "\t\t\t  9-Left Rotate\n"<<
                "\t\t\t  10-Swap Head with Tail\n"<<
                "\t\t\t  11-Get number of Nodes\n"<<
                "\t\t\t  12-Clear Linked List\n"<<
                "\t\t\t  0-Exit\n\n";

            cout<<"Enter Your Choice :  ";
            cin>>choice1;
        }
        while((choice1<0 || choice1>12));

        switch(choice1)
        {
        case 1:
            (obj.getLength()==0)?cout<<"EMPTY LINKED lIST \n\a":cout<<"NO : It Has "<<obj.getLength()<<" Nodes\n";
            break;

        case 2:
            handleInsertion();
            break;

        case 3:
            handleDeletion();
            break;

        case 4:
            obj.print();
            break;

        case 5:
            handleSearching();
            break;

        case 6:
            handleSorting();
            break;

        case 7:
            if(obj.getLength()==0)
                cout<<"EMPTY LINKED LIST\n\a";
            else
            obj.reverse();
            break;

        case 8:
             handleDuplication();
            break;

        case 9:
            handleRotation();
            break;

        case 10:
            obj.swapHeadTail();
            break;

        case 11:
            cout<<"Number Of Nodes : "<<obj.getLength()<<endl;
            break;

            case 12:
            obj.clearLinkedList();
            cout<<"Cleared Successfully\n";
            break;
        }

        cout<<"Repeat Again ?(Y/N)";
        cin>>choice2;
        if(choice2=='Y' || choice2=='y')loading();
    }
    while((choice2=='Y' || choice2=='y'));

}

// to move cursor over console
void moveCursor(int col, int row) /////////////
{
    cout << "\033[" << col << ";" << row << "H";
}

void loading()
{
    system("cls");
    for (int i=3 ; i>=0 ; i--)
    {
        moveCursor(5,5);
        cout<<"start after "<<i<<" sec";
        sleep(1);
        system("cls");
    }
}


void handleInsertion()
{
    int choice,pos,val,node_vale,number_of_nodes,counter;
    do
    {
        system("cls");
        cout<<"Insertion Process\n"<<
            "1-Insert First\n"<<
            "2-Insert After\n"<<
            "3-Insert At\n"<<
            "4-Insert Last\n"<<
            "5-Insert To Be Sorted\n";

        cout<<"Enter Your Choice : ";
        cin>>choice;
        if((choice<1  ||  choice>5))cout<<"Enter Valid Choice\n";
    }
    while(choice<1  ||  choice>5);

    switch(choice)
    {
    case 1:
        cout<<"(How many times you need to do this? : ";
        cin>>counter;
        for(int i=1; i<=counter; i++)
        {
            cout<<"Enter value "<<i<<" : ";
            cin>>val;
            obj.addFrist(val);
        }
        break;

    case 2:
        cout<<"(How many times you need to do this? : ";
        cin>>counter;
        for(int i=1; i<=counter; i++)
        {
            cout<<"Enter a node you need to add after it : ";
            cin>>node_vale;

            cout<<"Enter value "<<i<<" : ";
            cin>>val;

             obj.addAfter(node_vale,val);
        }
        break;

    case 3:
         cout<<"(How many times you need to do this? : ";
        cin>>counter;
        for(int i=1; i<=counter; i++)
        {
        cout<<"At process "<<i<<"\n";
        cout<<"Enter the position : ";
        cin>>pos;
        cout<<"Enter the value : ";
        cin>>val;
        obj.addAtPos(pos,val);
        }
        break;

    case 4:
         cout<<"(How many times you need to do this? : ";
        cin>>counter;
        for(int i=1; i<=counter; i++)
        {
        cout<<"At process "<<i<<"\n";
        cout<<"Enter the value : ";
        cin>>val;
        obj.addLast(val);
        }
        break;

    case 5:
        cout<<"Enter a number of nodes you wanna insert : ";
        cin>>number_of_nodes;
        for( int i=1; i<=number_of_nodes; i++)
        {
            cout<<"Enter node number "<<i<<" : ";
            cin>>val;
            obj.insert_2be_sort(val);
        }
    }
}

void handleDeletion()
{
    int choice,val,pos;
    do
    {
        system("cls");
        cout<<"Deletion Process\n"<<
            "1-Delete First\n"<<
            "2-Delete Last\n"<<
            "3-Delete by Index\n"<<
            "4-Delete by Element\n"<<
            "5-Delete Even Position\n";

        cout<<"Enter Your Choice : ";
        cin>>choice;
        if((choice<1  ||  choice>5))cout<<"Enter Valid Choice\n";
    }
    while(choice<1  ||  choice>5);

    switch(choice)
    {
    case 1:
        obj.deleteFirst();
        break;

    case 2:
        obj.deleteLast();
        break;

    case 3:
        cout<<"Enter the position : ";
        cin>>pos;
        obj.deleteAt(pos);
        break;

    case 4:
        cout<<"\nEnter a vale You Wanna Delete: ";
        cin>>val;
        obj.deleteElement(val);
        break;

    case 5:
        obj.delete_even_positions();
        cout<<"Even Position Deleted Successfully\n\n";
    }
}

void handleSearching()
{
    int key;
    cout<<"Enter a key : ";
    cin>>key;
    int check=obj.Search(key);
    (check!=-1)?cout<<key<<" Found at index "<<check<<endl : cout<<key<<" Not Found \a\n"<<endl;
}
void handleSorting()
{
obj.Sort();
cout<<"Sorted Successfully \n";
}

void handleDuplication()
{
    obj.remove_duplicates_from_not_sorted();
    cout<<"Removed Successfully \n";
}

void handleRotation()
{
    int rotation_number;
    cout<<"Enter a rotation number : ";
    cin>>rotation_number;
    obj.left_rotate(rotation_number);
}


/*
● In many cases, our links will be separated (-> next)
● We have hard time in printing
● A good way is to track the nodes and print their info
● Use a seperate vector to track current nodes
● Print the queue nodes itself not the linked list nodes

Visualizing linked list
● You don’t need to understand the details
○ Use these 2 functions to add/remove a node
*/
/*
vector<Node*> debug_data;	// add/remove nodes you use

void debug_add_node(Node* node)
{
    debug_data.push_back(node);
}
void debug_remove_node(Node* node)
{
    auto it = std::find(debug_data.begin(), debug_data.end(), node);
    if (it == debug_data.end())
        cout << "Node does not exist\n";
    else
        debug_data.erase(it);
}
*/
