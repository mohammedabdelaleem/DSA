//ProgrammingAdvices.com
//Mohammed Abu-Hadhoud

#include <iostream>
#include "clsDblLinkedList.h"

using namespace std;


int main()
{
    clsDblLinkedList <int> MyDblLinkedList;

   for (short i = 1; i <= 10; i++)
   {
       MyDblLinkedList.InsertAtEnd(i);
   }

    MyDblLinkedList.PrintList();

     MyDblLinkedList.UpdateItem(2,500);
 
    MyDblLinkedList.PrintList();



    system("pause>0");

}