/*****************************************************************************/
/* Project 2 - Sorting Algorithms											 */
/*****************************************************************************
	Author:  Atish Retna Rajah
    Student ID: R643D785

    Author: Nathaniel Hoefer
    Student ID: X529U639
    Program: Project 2


Functions:
	+ insertionSort(Data list[], int size): Sorts the list by using the
		insertion sort method while keeping track of the number of iterations
		Preconditions: The size is not larger than the list
		Postconditions: The list is sorted in ascending order
		> Make a copy of array
		> Pass through the array
			> Set walker to beginning of unordered part
			> While walker greater than 0 and the key before walker is greater
				than walker key, swap the elements and decrement the walker
		> Output results


******************************************************************************/


#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include "data.cpp"
#include "additionalFuncs.cpp"

using namespace std;

#ifndef INSERTION_CPP_
#define INSERTION_CPP_

//	Sorts the list by using the insertion sort method while keeping track of
//		the number of iterations
//		Preconditions: The size is not larger than the list
//		Postconditions: The list is sorted in ascending order
void insertionSort(Data list[], int size)
{

	int walker;
	int count = 0;
	Data temp[size];

	// Makes a temp of the array
	for(int i = 0; i < size; i ++)
		temp[i] = list[i];

	for(int i = 1; i < size; i++)
	{
		walker = i;
		while((walker > 0) && (temp[walker - 1].key > temp[walker].key))
		{
         count++;

         	// Swap the data to place them in order
			swapData(temp[walker], temp[walker - 1]);
         
			walker--;
		}
	}

	outputData(temp, size, count, 'i');

}

#endif /* INSERTION_CPP_ */
