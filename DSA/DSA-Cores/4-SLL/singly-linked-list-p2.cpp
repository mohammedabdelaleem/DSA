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