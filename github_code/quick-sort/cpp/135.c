/*
 * quick.cpp
 *
 *  Created on: Mar 2, 2018
 *      Author: chadstewart
 */

#include <iostream>

#include "quick.h"

using namespace std;

quick::quick()
{

}

quick::~quick()
{

}

void quick::quickSort(int* array, int low, int high)
{
	if(low < high)
	{
		int pivot = partition(array, low, high);

		quickSort(array, low, pivot - 1);
		quickSort(array, pivot + 1, high);
	}
}

int quick::partition(int* array, int low, int high)
{
	int pivot = array[high];
	int i = (low - 1);

	for(int j = low; j <= high - 1; j++)
	{
		if(array[j] <= pivot)
		{
			i++;
			swap(&array[i], &array[j]);
		}
	}

	swap(&array[i + 1], &array[high]);

	return(i + 1);
}

void quick::swap(int* firstElement, int* secondElement)
{
	int temp = *firstElement;
	*firstElement = *secondElement;
	*secondElement = temp;

}

void quick::printArray(int* array, int size)
{
        for(int i = 0; i < size; i++)
        {
                cout << array[i] << " ";
        }

        cout << "\n" << endl;
}






