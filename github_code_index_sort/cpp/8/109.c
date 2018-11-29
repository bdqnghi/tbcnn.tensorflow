// Napon Krassner (Jett)
// CSC 2430, Homework 3
// 05/08/2015
// Due: 05/13/2015
// Name: Implementation file for QuickSort class - QuickSort.cpp
// Description: This is the implementation file that implement all the
//				functions in QuickSort class. The QuickSort class uses the
//				quicksort algorithm (recursive) to sort an array of data.
//******************************************************************************

#include "SortData.h"
#include "QuickSort.h"

//********CONSTRUCTOR********
QuickSort::QuickSort(int max)
	: SortData(max)
{
	// Don't need to implement anything else since using the base class
	// to construct the object.
}

//********DESTRUCTOR********
QuickSort::~QuickSort()
{
	// Don't need to one since base class already has a destructor
	// for the object.
}

//********MUTATORS********
_int64 QuickSort::sort()
{
	// Init numops
	numops = 0;

	// Call quicksort
	quicksort(theData, maxSize);

	return numops;
}

//********PRIVATE MEMBER FUNCTIONS********
void QuickSort::quicksort(long theArray[], int n)
{
	recQuickSort(theArray, 0, n - 1);
}

void QuickSort::recQuickSort(long theArray[], int first, int last)
{
	int pivotLoc;

	if (first < last)
	{
		pivotLoc = partition(theArray, first, last);
		recQuickSort(theArray, first, pivotLoc - 1);
		recQuickSort(theArray, pivotLoc + 1, last);
	}
}

void QuickSort::swap(long theArray[], int first, int second)
{
	long temp;

	temp = theArray[first];
	theArray[first] = theArray[second];
	theArray[second] = temp;
	numops += 3;
}

int QuickSort::partition(long theArray[], int first, int last)
{
	long pivot;

	int index;
	int smallIndex;

	swap(theArray, first, (first + last) / 2);

	pivot = theArray[first]; numops++;
	smallIndex = first;

	for (index = first + 1; index <= last; index++)
	{
		if ((++numops) && theArray[index] < pivot)
		{
			smallIndex++;
			swap(theArray, smallIndex, index);
		}
	}

	swap(theArray, first, smallIndex);

	return smallIndex;
}