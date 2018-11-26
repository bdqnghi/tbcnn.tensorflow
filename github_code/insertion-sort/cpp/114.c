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
#include "InsertionSort.h"

using namespace std;

/*
  Name: swap in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver 
  Purpose: swaps positions of two values in the array
  Incoming: two values to be swapped
  Outgoing: N/A
  Return: N/A
*/
void InsertionSort::swap(int val1, int val2) {

	int temp;
	temp = arr[val2];
	arr[val2] = arr[val1];
	arr[val1] = temp;
	numSwaps++;

}


/*
  Name: init (initialize) in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: initializes the data member arr by copying the array passed in
  Incoming: an array, size of the array
  Outgoing: a is a pointer to the array
  Return: N/A
*/
void InsertionSort::init(int * a, int arrSize) {

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
  Name: InsertionSort in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: constructor for InsertionSort
  Incoming: N/A
  Outgoing: N/A
  Return: N/A
*/
InsertionSort::InsertionSort() {

	InsertionSort::CLASS_NAME = "InsertionSort";
	
	arr = 0;
	size = 0;

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;

}


/*
  Name: InsertionSort in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: initializes array for Insertion sort class
  Incoming: an array to be copied into data member arr and size
  Outgoing: a is a pointer to the array
  Return: N/A
*/
InsertionSort::InsertionSort(int * a, int arrSize) {

	InsertionSort::CLASS_NAME = "InsertionSort";

	init(a, arrSize);

}


/*
  Name: ~InsertionSort in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: deconstructs array in Insertion sort
  Incoming: N/A
  Outgoing: N/A
  Return: N/A
*/
InsertionSort::~InsertionSort() {

	delete [] arr;
	size = 0;

	numInnerLoops = 0;
	numOuterLoops = 0;
	numSwaps = 0;


}


/*
  Name: sort in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: sorts the array using Insertion Sort method 
  Incoming: N/A 
  Outgoing: N/A
  Return: N/A
*/
void InsertionSort::sort() {

	// Looks over items already sorted
	for (int position = 0; position < size; ++position) {
		
		// While the inserted array item is less than previous array item
		while ((position > 0) && (arr[position-1] > arr[position])) {

			// swap
			swap(position, position-1);
			--position;
			numInnerLoops++;

        }

		numOuterLoops++;

    }

}


/*
  Name: sort in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: sort the array being passed in
  Incoming: pointer to an array, size of array
  Outgoing: a is a pointer to an array
  Return: N/A
*/
void InsertionSort::sort(int * a, int arrSize) {

	init(a, arrSize);
	sort();

}


/*
  Name: print in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: Print array 
  Incoming: N/A
  Outgoing: N/A
  Return: N/A
*/
void InsertionSort::print() const {

	
	for (int i = 0; i < size; i++)
		cout << arr[i] << "\t";

	cout << endl;

}


/*
  Name: getNumLoops in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: returns the number of total loops executed by Insertion Sort
  Incoming: N/A
  Outgoing: N/A
  Return: Returns the number of loops
*/
int InsertionSort::getNumLoops() const {

	return (numInnerLoops + numOuterLoops);

}


/*
  Name: getNumOuterLoops in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: returns the number of outer loops executed by InsertionSort
  Incoming: N/A
  Outgoing: N/A
  Return: Returns the number of outer loops
*/
int InsertionSort::getNumOuterLoops() const {

	return numOuterLoops;

}


/*
  Name: getNumInnerLoops in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: return the number of inner loop executed by Insertion sort
  Incoming: N/A
  Outgoing: N/A
  Return: Returns the number of inner loops
*/
int InsertionSort::getNumInnerLoops() const {

	return numInnerLoops;

}


/*
  Name: getNumSwaps in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: Return the number of swaps executed by InsertionSort
  Incoming: N/A
  Outgoing: N/A
  Return: Returns the number of swaps
*/
int InsertionSort::getNumSwaps() const {

	return numSwaps;
}


/*
  Name: getArr in scope of InsertionSort
  Writer(s): Jeffrey Allen & Michael Beaver
  Purpose: Returns the array of the data
  Incoming: N/A
  Outgoing: N/A
  Return: Returns a pointer to a copy of the data member array
*/
int* InsertionSort::getArr() const {
	
	int * tmp = new int [size];

	for (int i = 0; i < size; i++)
		tmp[i] = arr[i];

	return tmp;

}