#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

class StackOverFlowException 
{
    public:
        StackOverFlowException() 
        {
            cout << "Stack overflow" << endl;
        }
};

class StackUnderFlowException 
{
    public:
        StackUnderFlowException() 
        {
            cout << "Stack underflow" << endl;
        }
};

class ArrayStack 
{
	private:
	int data[MAX_SIZE];
	int top;
	
	public:
	ArrayStack()
	{
		top = -1;
	}
	int Pop();
	void Push(int number);
	int Top();
	int Size();
	bool isEmpty();
	
};

int ArrayStack::Pop() {
	if ( top == -1 ) 
            {            
                throw new StackUnderFlowException();            
            }            
    return data[top--];   
}

void ArrayStack::Push(int number)
{
	if ( top >= MAX_SIZE ) 
    {            
        throw new StackOverFlowException();
    }                   
    data[++top] = number; 
}

int ArrayStack::Top()
{
	return data[top];      
	
}

int ArrayStack::Size()
{
	return top + 1;
}

bool ArrayStack::isEmpty()
{
	if (top == -1) {
		return true;
	} else {
		return false;
	}
}
int main() {
	 
	 ArrayStack s;
	 if ( s.isEmpty() ) 
            {
            cout << "Stack is empty" << endl;    
            }
        // Push elements    
        s.Push(100);    
        s.Push(200);    
        // Size of stack
        cout << "Size of stack = " << s.Size() << endl;
        // Top element    
        cout << s.Top() << endl;    
        // Pop element    
        cout << s.Pop() << endl;
        // Pop element    
        cout << s.Pop() << endl;
        // Pop element    
     
}




