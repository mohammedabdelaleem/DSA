#include <iostream>
#include <cstring>
#include <assert.h>

#define itn int
using namespace std;

// simple trick to avoid re-changing the class
//typedef char t;

template<class Type>
class STACKADT
{
private:
    Type* _data{ };
    int _size{ };
    int _top{ };
public:
    STACKADT(int size) :_size(size), _top(-1)
    {
        _data = new Type[size];
    }
    ~STACKADT() {
        delete[]_data;
    }
    //////////////
    STACKADT(const STACKADT& source)//when i create an obj as a ptr this way don't work as default
    {
        _size = source._size;
        _top = source._top;
        _data = new Type[_size];
        assert(_data != NULL);
        //coping
        for (int i = _top; i >= 0; i--)
            _data[i] = source._data[i];
    }
    ////////////
    bool full()
    {
        return(_top == _size - 1);
    }
    ////////////
    bool IsEmpty()
    {
        return(_top == -1 );
    }
    //////////////
    void push(Type num)
    {
        if (full())
        {
            //We Can Use Capacity Trick -> Expaned Capacity.
            cout << "Stack OverFlow\n";
            return;
        }
        else
        {
            _data[++_top] = num;
        }
    }
    //////////
    Type pop()
    {
        /* //if i made my stack as character stack then what?
                         this is a problem with template , but
                         if i use it as an integer stack ,the problem will solved
                         so assume that my own stack is not char */
        if (IsEmpty())
        {
            cout << "Stack UnderFlow\n";
            return -1;
        }
        return _data[_top--];
    }
    ///////////////
    Type TopItem()
    {
        /* //if i made my stack as character stack then what?
                          this is a problem with template , but
                          if i use it as an integer stack ,the problem will solved
                          so assume that my own stack is not char */
        if (IsEmpty())
        {
            // cout<<"Stack UnderFlow\n";
            return -1;
        }
        return _data[_top];
    }

    itn Top()
    {
        return _top;
    }
    //////////
    void Print()
    {
        if (IsEmpty())
        {
            cout << "Stack UnderFlow\n";
            return;
        }
        else
        {
            cout << "your elements: \n";
            for (int i = _top; i >= 0; i--)
                cout << _data[i] << " ";
            cout << endl;
        }
    }
    ////
    void ReplaceAllSpecificElementsWith(Type _old, Type _new)
    {
        if (IsEmpty())
        {
            cout << "Stack UnderFlow\n";
            return;
        }
        for (int i = _top; i >= 0; i--)
            if (_data[i] == _old)
                _data[i] = _new;
    }
    /////////
    void Reverese()//check more
    {

        if (IsEmpty())
        {
            cout << "Stack UnderFlow\n";
            return;
        }
        STACKADT<Type>* s2 = new STACKADT<Type>(_size);

        for (int i = _top; i >= 0; i--)
            s2->push(_data[i]);

        for (int i = _top; i >= 0; i--)
            _data[i] = s2->_data[i];

        delete[] s2;
    }
    ///////
    int CountElements()
    {
        return _top + 1;//because of idx
    }

    ///////////////
    int Search_element(Type Target)
    {
        int key = -2;
        if (IsEmpty())
        {
            cout << "Stack UnderFlow\n";
            return key;
        }

        for (int i = 0; i <= _top; i++)
        {
            if (Target == _data[i])
                key = i;
            return key;
        }
        return key;
    }
    //////////////////
    int Frequancy(Type e)
    {
        int k = 0;
        for (int i = 0; i <= _top; i++)
            if (e == _data[i])
                k++;
        return k;
    }
    void Edit(int pos, Type e)
    {
        _data[pos - 1] = e;
    }
    /* Balanced Pranteses*//////////////////////////////////////////////////////////
    bool Isbalanced( char* exp)
    {
        if (strlen(exp) == 0)
        {
            cout << "Expression is Empty\n";
            return false;
        }
        for (int i = 0; exp[i] != '\0'; i++)
        {
            if (exp[i] == '(')
                push('(');
            else if (exp[i] == ')')
            {
                if (IsEmpty())
                    return false;
                else
                    pop();
            }
        }
        return (IsEmpty());
    }
    ////convert from infix to postfix
    //1-
    bool IsOperand(char c)
    {
        return((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
    }
    //2-
    int pre(char c)
    {
        if (c == '*' || c == '/')
            return 2;
        else if (c == '+' || c == '-')
            return 1;
        else
            return 0; //stack is empty
    }
    ///////
    Type* convertInfixToPostfix(Type* infix)
    {
        Type* postfix = new Type[strlen(infix)];
        int InfixCtr = 0; 
        int PostfixCtr = 0;
        while (infix[InfixCtr] != '\0')
        {
            if (IsOperand(infix[InfixCtr]))
            {
                postfix[PostfixCtr++] = infix[InfixCtr++];
            }
            else    //operator
            {
                if (pre(infix[InfixCtr]) > pre(TopItem()))
                    push(infix[InfixCtr++]);
                else
                {
                    postfix[PostfixCtr++] = pop();
                }
            }
        }
        while (!IsEmpty())
        {
            postfix[PostfixCtr++] = pop();
        }
        postfix[PostfixCtr] = '\0';
        return postfix;
    }
    ////Evaluate postfix(postfix)
    int EvaluatePostfix(char* postfix)
    {
        int SecondPOP = 0;//for second pop()
        int FirstPOP = 0;//for first pop()

        for (int i = 0; postfix[i] != '\0'; i++)
        {
            if (IsOperand(postfix[i]))
            {
                push(postfix[i] - '0');//as number not char
            }
            else
            {
                FirstPOP = pop();
                SecondPOP = pop();
                switch (postfix[i])
                {
                case '+':
                    push(SecondPOP + FirstPOP);
                    break;
                case '-':
                    push(SecondPOP - FirstPOP);
                    break;
                case '*':
                    push(SecondPOP * FirstPOP);
                    break;
                case '/':
                    push(SecondPOP / FirstPOP);
                    break;
                default:
                    break;
                }
            }
        }
        return TopItem();
    }
    /////////// obj1.operator=(obj2)
    void operator=(const STACKADT& source)
    {
        if (this != &source)
        {
            delete[]_data;
            _size = source._size;
            _top = source._top;
            _data = new Type[_size];
            for (int i = _top; i >= 0; i--)
                _data[i] = source._data[i];
        }
        else
            return;
    }

};
/*كورس فاخر من الاخر وده هيخليني امشي فيه براحتي واذاكر كويس علشان اتعلم اكبر قدر ممكن ان شاء الله (مش الاسم اني خلصت الكورس وخلاص الكورس مهم وممتع فعلا*/
int main() {
    short Size = 10;
    STACKADT<short>* S1 = new STACKADT<short>(Size);

    return 0;
}
