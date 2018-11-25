// Napon Krassner (Jett)
// CSC 2430, Homework 3
// 05/08/2015
// Due: 05/13/2015
// Name: Header file for InsertionSort class - InsertionSort.h
// Description: This is the header file that contain all the function
//				declaration for the InsertionSort class and documentation
//				explaining how they work. InsertionSort is a derived class from
//				SortData class.
//******************************************************************************

#ifndef _INSERTION_SORT_
#define _INSERTION_SORT_

#include "SortData.h"

using namespace std;

class InsertionSort : public SortData
{
public:
	//********CONSTRUCTOR********
	// Parameters: int - size of the array with default max to 100
	// Return: nothing
	// Description: Uses new operator, allocate theData array with size
	//				in param.
	InsertionSort(int = 100);

	//********DESTRUCTOR********
	// Parameters: None
	// Return: nothing
	// Description: Deallocates the memory for InsertionSort class to free up
	//				the heap and avoid memory leak.
	~InsertionSort();

	//********MUTATORS********
	// Parameters: none
	// Return: _int64 - number of significant operations
	// Description: Sorts theData array using insertionsort
	//				returns a count of numops that were required.
	// Note: significant operation is:
	//		- a comparison of two key-data values
	//		- an assignment of two key-data values
	_int64 sort();

private:
	//********PRIVATE MEMBER VARS********
	_int64 numops;

	//********PRIVATE MEMBER FUNCTIONS********
	// Parameters: long - theArray, int - size of theArray
	// Return: nothing
	// Description: Uses the insertionsort algorithm to sort theArray
	//				with size n.
	//				Built based on Malik's example for selectionsort.
	//				Added counting number of operation.
	void insertionsort(long[], int);
};

#endif