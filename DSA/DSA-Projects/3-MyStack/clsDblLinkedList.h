#pragma once

#include <iostream>
using namespace std;


template<class Type>
class clsDblLinkedList
{
protected:
    short _Size = 0;//to know number of nodes


public:
    // Create a node
    class Node
    {
    public:
        Type value;
        Node* next;
        Node* prev;

        Node(Type data = 0)
        {
            value = data;
            prev = next = NULL;
        }
      /*  ~Node()
        {
            cout << "Destroy Node With Value " << value << " At " << this << endl;
        }*/
    };

    Node* head;

  /*  clsDblLinkedList() {}
    clsDblLinkedList(const clsDblLinkedList& source) = delete;
    clsDblLinkedList &operator=(const clsDblLinkedList&source)=delete;*/

    ~clsDblLinkedList()
    {
        Clear();
    }

    bool IsEmpty()
    {
        return (_Size == 0 && !head);
    }
    
    void InsertAtBeginning(Type value) {

        /*
            1-Create a new node with the desired value.
            2-Set the next pointer of the new node to the current head of the list.
            3-Set the previous pointer of the current head to the new node.
            4-Set the new node as the new head of the list.
        */

        Node* newNode = new Node(value);
        newNode->next = head;
        newNode->prev = NULL;

        if (head != NULL) {
            head->prev = newNode;
        }
        head = newNode;

        _Size++;
    }

    Node* Find(Type Value)
    {
        Node* temp = head;
        while (temp != NULL) {

            if (temp->value == Value)
                return temp;


            temp = temp->next;
        }

        return NULL;

    }

    void InsertAfter(Node* current, Type value) {


        /*  1 - Create a new node with the desired value.
             2-Set the next pointer of the new node to the next node of the current node.
             3-Set the previous pointer of the new node to the current node.
             4-Set the next pointer of the current node to the new node.
             5-Set the previous pointer of the next node to the new node(if it exists).
        */

        Node* newNode = new Node(value);
        newNode->next = current->next;
        newNode->prev = current;

        if (current->next != NULL) {
            current->next->prev = newNode;
        }
        current->next = newNode;

        _Size++;
    }

    bool InsertAfter(short index, Type Value)
    {
        Node* ItemNode = GetNode(index);
        if(ItemNode!=NULL)
        {
            InsertAfter(ItemNode,Value);
            return true;
        }
        return false;
    }

    void InsertAtEnd(Type value) {

        /*
            1-Create a new node with the desired value.
            2-Traverse the list to find the last node.
            3-Set the next pointer of the last node to the new node.
            4-Set the previous pointer of the new node to the last node.
        */

        Node* newNode = new Node(value);
        newNode->next = NULL;//by default we can ignore it.
        if (head == NULL) {
            newNode->prev = NULL; //by default we can ignore it.
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }

        _Size++;
    }

    void DeleteNode( Node*& NodeToDelete) {


        /*
            1-Set the next pointer of the previous node to the next pointer of the current node.
            2-Set the previous pointer of the next node to the previous pointer of the current node.
            3-Delete the current node.
        */
        if (head == NULL || NodeToDelete == NULL) {
            return;
        }
        if (head == NodeToDelete) {
            head = NodeToDelete->next;
        }
        if (NodeToDelete->next != NULL) {
            NodeToDelete->next->prev = NodeToDelete->prev;
        }
        if (NodeToDelete->prev != NULL) {
            NodeToDelete->prev->next = NodeToDelete->next;
        }
        delete NodeToDelete;// || free Ya Man.

        _Size--;
    }

    void DeleteFirstNode() {

        /*
            1-Store a reference to the head node in a temporary variable.
            2-Update the head pointer to point to the next node in the list.
            3-Set the previous pointer of the new head to NULL.
            4-Delete the temporary reference to the old head node.
        */

        if (head == NULL) {
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        delete temp;

        _Size--;
    }

    void DeleteLastNode() {

        /*
            1-Traverse the list to find the last node.
            2-Set the next pointer of the second-to-last node to NULL.
            3-Delete the last node.
        */

        if (head == NULL) {
            return;
        }
        if (head->next == NULL) {
            delete head;
            head = NULL;
            return;
        }
        Node* current = head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = NULL;
        delete temp;

        _Size--;
    }

    short Size()
    {
        return _Size;
    }

    // Print the linked list
    void PrintList()
    {
        Node* current = head;

        while (current != NULL) {
            cout << current->value << "  ";
            current = current->next;
        }
        cout << endl;

        delete current; //it will deleted by default because we didn't allocate a memory for him
    }

    void Clear()
    {
        while (_Size>0)
        {
            DeleteFirstNode();
        }
    }

    Node* GetNode(short index)
    {
        if (index < 0 || index >= _Size)
            return NULL;

        Node* Current= head;
        while (Current !=NULL && index--)
        {
            Current = Current->next;
        }
        return Current;
    }

    Type GetItem(short index)
    {
        Node* N = GetNode(index);
        
        return N ? N->value : INT_MIN;
    }

    Type operator[](short index)
    {
        return GetItem(index);
    }

    bool UpdateItem(short index, Type NewValue)
    {
        Node* ItemNode = GetNode(index);

        if(ItemNode!=NULL)
        {
            ItemNode->value = NewValue;
            return true;
        }
        else
        {
            return false;
        }
    }

    void Reverse()
    {
        Node* current = head;
        Node* temp = nullptr;
        while (current!=nullptr)
        {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        //In the reverseDoublyLinkedList function, after reversing the pointers of each node, 
        //  *the temp variable will be pointing to the last node of the original list.To update the head pointer correctly
        //  *we need to assign temp->prev to head.
        //  *This ensures that the head pointer now points to the new first node of the reversed list.
        if (temp != nullptr) {
            head = temp->prev; // i need to understand this again.
        }
    }

    
};

