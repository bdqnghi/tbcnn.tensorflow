/*
	Names: Jeffrey Allen and Michael Beaver
	CS355 Fall 2012
	Assignment: Assignment 11, Group 3
	Description: This program implements a system design for comparing different sorting algorithms.  The class
				hierarchy allows for "plug-n-play" of sorting algorithm class objects.  The driver program allows
				the user to input data either manually or via file.  The data is sorted and iteration information
				is collected.  The user then has the option to view the iteration information for each algorithm.
    Due Date: November 20, 2012
*/

#include <iostream>
#include "SelectionSort.h"

using namespace std;


/*
  Name: SelectionSort in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Default constructor. Initializes object to valid state.
  Incoming: N/A
  Outgoing: N/A
  Return: N/A
*/
SelectionSort::SelectionSort() {

	SelectionSort::CLASS_NAME = "SelectionSort";

	arr = 0;
	size = 0;

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;

}


/*
  Name: SelectionSort in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Overloaded constructor. Initializes object to valid state.
  Incoming: a is a pointer to an array and arrSize is the size of the array
  Outgoing: a is a pointer to an array
  Return: N/A
*/
SelectionSort::SelectionSort(int * a, int arrSize) {

	SelectionSort::CLASS_NAME = "SelectionSort";

	init(a, arrSize);

}


/*
  Name: ~SelectionSort in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Destructor. Returns memory and resets values.
  Incoming: N/A
  Outgoing: N/A
  Return: N/A
*/
SelectionSort::~SelectionSort() {

	delete [] arr;
	size = 0;

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;

}


/*
  Name: init in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Initializes the object data members to prepare for sorting.
  Incoming: a is a pointer to an array and arrSize is the size of the array
  Outgoing: a is a pointer to an array
  Return: N/A (void)
*/
void SelectionSort::init(int * a, int arrSize) {

	size = arrSize;
	arr = new int [size];

	// Copy array values into data member array
	for (int i = 0; i < arrSize; i++)
		arr[i] = a[i];

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;

}


/*
  Name: sort in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Performs selection sort on the arr data member.
  Incoming: N/A
  Outgoing: N/A
  Return: N/A (void)
*/
void SelectionSort::sort() {

	int min;

	// Iterate over the entire array
	for (int i = 0; i < size; i++) {

		min = i;

		// Compare each value to the minimum
		for (int j = i; j < size; j++) {

			// Change the minimum if necessary
			if (arr[j] < arr[min])
				min = j;

			numInnerLoops++;

		}

		// Swap values if necessary
		if (i != min)
			swap(i, min);

		numOuterLoops++;

	}

}

/*
  Name: sort in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Performs selection sort on the arr data member.
  Incoming: a is a pointer to an array and arrSize is the size of the array
  Outgoing: a is a pointer to an array
  Return: N/A (void)
*/
void SelectionSort::sort(int * a, int arrSize) {

	// Initialize data members
	init(a, arrSize);

	sort();

}


/*
  Name: swap in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Swaps two values in an array.
  Incoming: val1 and val2 are indices in the array
  Outgoing: N/A
  Return: N/A (void)
*/
void SelectionSort::swap(int val1, int val2) {

	int temp;
	temp = arr[val2];
	arr[val2] = arr[val1];
	arr[val1] = temp;

	numSwaps++;

}


/*
  Name: sort in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Prints the arr data member.
  Incoming: N/A
  Outgoing: N/A
  Return: N/A (void)
*/
void SelectionSort::print() const {

	for (int i = 0; i < size; i++)
		cout << arr[i] << "\t";

	cout << endl;

}


/*
  Name: getNumLoops in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Returns the total number of loops performed.
  Incoming: N/A
  Outgoing: N/A
  Return: Returns the total number of loops performed
*/
int SelectionSort::getNumLoops() const {

	return (numInnerLoops + numOuterLoops);

}

/*
  Name: getNumOuterLoops in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Returns the number of outer loops performed.
  Incoming: N/A
  Outgoing: N/A
  Return: Returns the number of outer loops performed
*/
int SelectionSort::getNumOuterLoops() const {

	return numOuterLoops;

}


/*
  Name: getNumInnerLoops in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Returns the number of inner loops performed.
  Incoming: N/A
  Outgoing: N/A
  Return: Returns the number of inner loops performed
*/
int SelectionSort::getNumInnerLoops() const {

	return numInnerLoops;

}


/*
  Name: getNumSwaps in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Returns the number of swaps performed.
  Incoming: N/A
  Outgoing: N/A
  Return: Returns the number of swaps performed
*/
int SelectionSort::getNumSwaps() const {

	return numSwaps;

}


/*
  Name: getArr in scope of SelectionSort
  Writer(s): Michael Beaver
  Purpose: Returns a pointer to the array.
  Incoming: N/A
  Outgoing: N/A
  Return: Returns a pointer to the array
*/
int * SelectionSort::getArr() const {

	int * tmp = new int [size];

	for (int i = 0; i < size; i++)
		tmp[i] = arr[i];

	return tmp;

}