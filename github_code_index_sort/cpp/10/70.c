#include "stdafx.h"
#include "BucketSort.h"
#include <iostream>

using namespace std;

BucketSort::BucketSort() {}

BucketSort::BucketSort(int arr[], int size)
{
	_size = size;
	for (int i = 0; i < _size; i++)
		wArray[i] = arr[i];
}

BucketSort::~BucketSort() {};

void BucketSort::sortIt()
{
	int largest_item = -10000000;
	//find largest item
	for (int i = 0; i < _size; i++)
	{
		if (largest_item < wArray[i])
			largest_item = wArray[i];
	}


	int *temp_array = new int[largest_item]; //Creating temp array to the size of largest item from wArray
	//initialize all of temp array to 0
	for (int i = 0; i <= largest_item; i++)
	{
		temp_array[i] = 0;
	}
	
	//temp_array indexes are incrimented when the corresponding number in wArray are detected
	for (int i = 0; i < _size; i++)
		temp_array[wArray[i]]++;

	//copy the results back into wArray
	int wArrayIndex = 0;
	for (int i = 0; i <= largest_item; i++)
	{
		if (temp_array[i] > 0) {
			int count = 0;
			int stop = temp_array[i];
			while (count < stop)
			{
				wArray[wArrayIndex] = i;
				wArrayIndex++;
				count++;
			}
		}
	}

	//print results
	printIt();
	delete temp_array;
}

void BucketSort::printIt()
{
	for (int i = 0; i < _size; i++)
		cout << wArray[i] << ", ";
}