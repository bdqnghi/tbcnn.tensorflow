
using namespace std;

// =========================================================

//HW1P2 stack(vector)
//Your name: Christopher Wendling
//Complier:  g++
//File type: implimentation file stack.cpp

//================================================================

#include "stack.h"

//Object Constructor will do nothing
stack::stack()
{}
//Object Destructor calls clear function and destroys all elements of vector.
stack::~stack()
{ 
	clearIt();
}
// 	PURPOSE: isEmpty checks vector size and returns true if empty, false otherwise.
bool stack::isEmpty()
{ 
	if(el.size() == 0) 
		return true; 
	else 
		return false; 
}    
// PURPOSE: Return false, stack will never be full.
bool stack::isFull()
{ 
	return false;
}
// PURPOSE: adds an element to el
void stack::push(el_t elem)
{ 
	el.push_back(elem);
}
// PURPOSE: pop calls isEmpty and if true, throws an exception (Underflow)
//  Otherwise, removes an element from el and gives it back.
void stack::pop(el_t& elem)
{ 
	if(isEmpty())
	  throw Underflow();
    else{ 
		elem = el[el.size() - 1]; 
		el.pop_back();
	}
}
// PURPOSE: topElem calls isEmpty and if true, throws an exception (underflow)
//    Otherwise, gives back the top element from el.
void stack::topElem(el_t& elem)
{ 
	if(isEmpty()) 
		throw Underflow();
    else{ 
		elem = el[el.size() - 1];		
	}
}
//dislayAll calls isEmpty and if true, displays [ empty ].
//  Otherwise, diplays the elements vertically.
void stack::displayAll()
{  
	if(isEmpty()) 
		cout << ".[ empty ]." << endl;
    else 
		for(int i = el.size() - 1; i>=0; --i){ 
			cout << el[i] << endl; 
		}
}
//  PURPOSE: destroys all elements of vector
void stack::clearIt()
{
	el.clear();
}
