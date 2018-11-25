/*
 * InsertionSort.cpp
 *
 *  Created on: Apr 22, 2018
 *      Author: pournami
 */

#include "InsertionSort.h"

InsertionSort::InsertionSort() : VectorSorter("Insertion sort") {}

InsertionSort::~InsertionSort() {}

void InsertionSort::run_sort_algorithm()
{
	/*** reference - https://www.geeksforgeeks.org/insertion-sort/ ***/

	int i,j;
	// For each element of the vector ...
	for(i = 1; i<size; i++)
	{
		Element key(data[i]);
		j = i-1;
		compare_count++;
		// make space to insert a smallest element in between the data
		while(j>=0 && data[j] > key)
		{
			data[j+1] = data[j];
			move_count++;
			j--;
		}
		// insert the smallest element to appropriate position
		data[j+1] = key;
	}
}
