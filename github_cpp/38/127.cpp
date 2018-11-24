
using namespace std;
// =========================================================

//HW1P1 queue
//Your name: Christopher Wendling
//Complier:  g++
//File type: Implimentation file

//================================================================

#include "queue.h"   // constructor 
queue::queue()
{
	front = 0;
	rear = -1;
	count = 0;
}

//destructor 
queue::~queue()
{
}

// PURPOSE: returns true if queue is empty, otherwise false
bool queue::isEmpty()
{
	if(rear == -1)
		return true;
	else
		return false;
}

// PURPOSE: returns true if queue is full, otherwise false
bool queue::isFull()
{
	if(count == MAX_SIZE)
		return true;
	else
		return false;
}

// PURPOSE: if full, throws an exception Overflow
// if not full, enters an element at the rear 
// HOW TO CALL: provide the element to be added
void queue::add(el_t elem)
{
	if(isFull())
		throw Overflow();
	else if(rear == (MAX_SIZE - 1)){
		count++;
		rear = 0;
		el[rear] = elem;
	}
	else{
		count++;
		el[++rear] = elem;
	}
}

// PURPOSE: if empty, calls an emergency exit routine
// if not empty, removes the front element to give it back 
// HOW TO CALL: provide a holder for the element removed (pass by ref)
void queue::remove(el_t& elem)
{
	if(isEmpty())
	  throw Underflow();
      	else{
		count--;
		elem = el[front];
		if(front == (MAX_SIZE - 1))
			front = 0;
		else
			++front;
	}
}

// PURPOSE: if empty, throws an exception Underflow
   // if not empty, give back the front element (but does not remove it)
   // TO CALL: provide a holder for the element (pass by ref)
void queue::frontElem(el_t& elem)
{
	if(isEmpty())
		throw Underflow();
	else
		elem = el[front];
}

// PURPOSE: returns the current size to make it 
// accessible to the client caller
int queue::getSize()
{
	return count;
}

// PURPOSE: display everything in the queue from front to rear
//  enclosed in []
// if empty, displays [ empty ]
void queue::displayAll()
{
  int x = front;
    cout << "{";
    for(int i = 0; i < count; ++i, ++x){
		cout << el[x] << ", ";
		if(x == (MAX_SIZE - 1))
			x = -1;
	}
	cout << "}" << endl;
}

// PURPOSE: if empty, throws an exception Underflow
//if queue has just 1 element, does nothing
//if queue has more than 1 element, moves the front one to the rear
void queue::goToBack()
{
	el_t elem;
	if(isEmpty())
		throw Underflow();
	else{
		remove(elem);
		add(elem);
	}
}
