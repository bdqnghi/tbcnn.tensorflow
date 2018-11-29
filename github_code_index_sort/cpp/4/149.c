#pragma once
#include <iostream>
#include <time.h>
#include "swap.h"

using namespace std;

//reference used:
//http://quiz.geeksforgeeks.org/heap-sort/
void heapify(int arr[], int n, int i)
{
	int largest = i;  // Initialize largest as root
	int l = 2 * i + 1;  // left = 2*i + 1
	int r = 2 * i + 2;  // right = 2*i + 2

						// If left child is larger than root
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest so far
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// If largest is not root
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree
		heapify(arr, n, largest);
	}
}

void heapS(int *array, int size) {
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(array, size, i);

	// One by one extract an element from heap
	for (int i = size - 1; i >= 0; i--) {
		swap(array, 0, i);
		heapify(array, i, 0);
	}
}


double heapsort(int *array, int size){
  double start = clock();

  heapS(array, size);

  double end = clock();
  double total = (end - start) / CLOCKS_PER_SEC ;
  return total;
}
