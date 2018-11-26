// Napon Krassner (Jett)
// CSC 2430, Homework 3
// 05/08/2015
// Due: 05/13/2015
// Name: Implementation file for InsertionSort class - InsertionSort.cpp
// Description: This is the implementation file that implement all the
//				functions for InsertionSort class. The InsertionSort class
//				uses the insertionsort algorithm to sort an array of data.
//******************************************************************************

#include "SortData.h"
#include "InsertionSort.h"

//********CONSTRUCTOR********
InsertionSort::InsertionSort(int max)
	: SortData(max)
{
	// Don't need to implement anything else since using the base class
	// to construct the object.
}

//********DESTRUCTOR********
InsertionSort::~InsertionSort()
{
	// Don't need to one since base class already has a destructor
	// for the object.
}

//********MUTATORS********
_int64 InsertionSort::sort()
{
	// Init numops
	numops = 0;

	// Call insertionsort func to sort data
	insertionsort(theData, maxSize);

	return numops;
}

//********PRIVATE MEMBER FUNC********
void InsertionSort::insertionsort(long theArray[], int n)
{
	// Built from Malik's example for selectionsort
	// Added numops to count number of operation
	for (int firstOutOfOrder = 1; firstOutOfOrder < n; firstOutOfOrder++)
	{
		if ((++numops) && theArray[firstOutOfOrder] < theArray[firstOutOfOrder - 1])
		{
			long temp = theArray[firstOutOfOrder]; numops++;
			int loc = firstOutOfOrder;

			do
			{
				theArray[loc] = theArray[loc - 1]; numops++;
				loc--;
			}
			while ((++numops) && loc > 0 && theArray[loc - 1] > temp);

			theArray[loc] = temp; numops++;
		}
	}
}