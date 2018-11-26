/*****************************************************************************/
/* Project 2 - Sorting Algorithms											 */
/*****************************************************************************
	Author:  Atish Retna Rajah
    Student ID: R643D785

    Author: Nathaniel Hoefer
    Student ID: X529U639
    Program: Project 2


Functions:
	+ bubbleSort(Data list[], int size): Sorts the list by using the bubble sort
		method while keeping track of the number of iterations
		Preconditions: The size is not larger than the list
		Postconditions: The list is sorted in ascending order
		> Copy the array to a temp array.
		> In order to optimize, use a sorted value to tell if the list has been
			sorted before comparing entire list
		> Starting with the last two elements, compare each pair of elements.
			> If right element is less than left element, swap them
			> The least element will bubble to the beginning of the list
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

#ifndef BUBBLE_CPP_
#define BUBBLE_CPP_

// Bubble Sort
void bubbleSort(Data list[], int size)
{

	Data temp[size];
   
	// make a temp of the array
	for(int i = 0; i < size; i ++)
		temp[i] = list[i];

	int walker, count;
	count = 0;

	// Used for optimized sorting
	bool sorted = false;
	
	// Sort temp list
	for(int i = 0; (i < size) && (sorted == false); i++)
	{
		sorted = true;

		// Compares each two elements starting from the top and swaps them if
		// the right element is less than the right
		for(walker = size - 1; walker > i; walker--)
		{
			if(temp[walker].key < temp[walker - 1].key)
			{
				swapData(temp[walker], temp[walker - 1]);
				sorted = false;
			}

	         count++;
		}
	}	

	outputData(temp, size, count, 'b');
}

#endif /* BUBBLE_CPP_ */
