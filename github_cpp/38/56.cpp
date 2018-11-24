#include "Queue.h"


Queue::Queue()
{
	size = 0;
	head = 0;
	tail = 0;
	capacity = 1;

	elementArray = new int[capacity];
}

Queue::Queue( int c )
{
	size = 0;
	head = 0;
	tail = 0;
	capacity = c;

	elementArray = new int[capacity];
}

Queue::~Queue()
{
	delete[] elementArray;
	elementArray = nullptr;
}

void Queue::enQueue( int element )
{
	if (size == capacity)
	{
		resize( size * 2 );
	}

	elementArray[tail++] = element;

	if (tail == capacity)
	{
		tail = 0;
	}

	size++;
}

int Queue::deQueue()
{
	if (isEmpty())
	{
		throw exception( "Empty queue error" );
	}

	int returnedEle = elementArray[head];

	if (++head == capacity)
	{
		head = 0;
	}

	if (--size > 0 && size <= capacity / 4)
	{
		resize( capacity / 2 );
	}

	return returnedEle;
}

int Queue::getSize()
{
	return size;
}

int Queue::getCapacity()
{
	return capacity;
}

void Queue::printQueue()
{
	if (isEmpty())
	{
		cout << "Empty queue" << endl;

		return;
	}

	for (int i = head; i < head + size; i++)
	{
		if (i == capacity)
		{
			i == 0;
		}

		cout << "Index: " << i << " Element: " << elementArray[i] << endl;
	}
}

bool Queue::isEmpty()
{
	return size == 0;
}

void Queue::resize( int c )
{
	int* newArray = new int[c];

	for (int i = 0; i < capacity; i++)
	{
		newArray[i] = elementArray[head + i];
	}

	// Re-position head and tail
	head = 0;
	tail = size;
	capacity = c;

	// Delete old array
	delete[] elementArray;
	// Setup new array
	elementArray = newArray;
}
