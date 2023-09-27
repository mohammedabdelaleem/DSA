
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
