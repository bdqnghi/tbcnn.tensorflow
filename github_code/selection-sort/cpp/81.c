/*****************************************************************************/
/* Project 2 - Sorting Algorithms											 */
/*****************************************************************************
	Author:  Atish Retna Rajah
    Student ID: R643D785

    Author: Nathaniel Hoefer
    Student ID: X529U639
    Program: Project 2


Functions:
	+ selectionSort(Data arr[], int size): Sorts the list by using the
		selection sort method while keeping track of the number of iterations
		Preconditions: The size is not larger than the list
		Postconditions: The list is sorted in ascending order
		> Copy the array to a temp array.
		> Make a pass through the list for for each element in the list
		> During each pass, set a min to equal the pass index and compare each
			following element to min and swap them if current element is less
		> Keep track of number of iterations with a counter
		> Output results


******************************************************************************/


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include "data.cpp"
#include "additionalFuncs.cpp"

using namespace std;

#ifndef SELECTION_CPP_
#define SELECTION_CPP_

//	Sorts the list by using the selection sort method while keeping track of the
//		number of iterations
//		Preconditions: The size is not larger than the list
//		Postconditions: The list is sorted in ascending order
void selectionSort(Data list[], int size)
{
	int min, count;
	count = 0;

	Data temp[size];

	// Makes a temp of the array
	for (int i = 0; i < size; i++)
		temp[i] = list[i];
      
	// Sorts the data
	for (int i = 0; i < size - 1; i++)
	{
		min = i;
	
		for (int j = i + 1; j < size; j++)
		{
			// Set min to jth key if it is less than min
			if (temp[j].key < temp[min].key)
				min = j;

			count++;
		}
      
		// Swap the data if min was changed
		if (min != i)
			swapData(temp[i], temp[min]);
	}

	outputData(temp, size, count, 's');
}

#endif /* SELECTION_CPP_ */
