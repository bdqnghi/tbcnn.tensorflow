#include <iostream>
using namespace std;

const int maxQsize = 100;

class Queue
{
	char q[maxQsize]; //this array holds the queue
	int size; // maximum number of elements the queue can store
	int putloc, getloc; // the put and get indices

public:

	// construct a queue of a specific length.

Queue(int len)
{
	//queue must be less than max and positive.
	if(len > maxQsize) len = maxQsize;
	else if(len <= 0) len = 1;

	size = len;
	putloc = getloc = 0;
}

// put a character into the queue.

void put(char ch)
{
	if(putloc == size)
	{
		cout << " -- Queue is full.\n";
		return;
	}
	putloc++;
	q[putloc] = ch;
}

//Get a character from the queue.

char get()
{
	if(getloc == putloc)
	{
		cout << " -- Queue is empty.\n";
		return 0;
	}
	getloc++;
	return q[getloc];
}
};

//Demonstrate the Queue class.

int main()
{
	Queue bigQ(100);

	Queue smallQ(4);
	char ch;
	int i;

	cout << "Using bigQ to store the alphabet.\n";
	//put some numbers into bigQ
	for(i=0; i < 26; i++)
		bigQ.put('A' + i);

		//retrieve and display elements from bigQ
	cout << "Contents of bigQ: ";
	for (i=0; i < 26; i++)
	{
		ch = bigQ.get();
		if (ch != 0) cout << ch;
	}

	cout << "\n\n";
	cout << "Using smallQ to generate some errors.";

	//Now use smallQ to generate some errors
	for(i=0; i < 5; i++)
	{
		cout << "Attempting to store " << 
			(char) ('Z' - i);
		smallQ.put('Z' - i);

		cout << "\n";
	}
	cout << "\n";
	//more errors on smallQ
	cout << "Contents of smallQ: ";
	for(i=0; i < 5; i++)
	{
		ch = smallQ.get();

		if(ch != 0) cout << ch;
	}
	cout << "\n";
}


