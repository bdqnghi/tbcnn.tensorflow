#pragma once
#include <iostream>
#include <time.h>
#include "swap.h"

using namespace std;



void heapify(int arr[], int n, int i)
{
	int largest = i;  
	int l = 2 * i + 1;  
	int r = 2 * i + 2;  

						
	if (l < n && arr[l] > arr[largest])
		largest = l;

	
	if (r < n && arr[r] > arr[largest])
		largest = r;

	
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		
		heapify(arr, n, largest);
	}
}

void heapS(int *array, int size) {
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(array, size, i);

	
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
