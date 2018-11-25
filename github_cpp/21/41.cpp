

#include <iostream>
#include "SortUtils.h"
using namespace std;

void selectionSort(int arr[], int len)
{
	for(int i = 0; i < len; i++){
		int minIndex = i;  
		for(int j = i + 1; j < len; j++)
			if(arr[j] < arr[minIndex])
				minIndex = j;			
			
		swap(arr[i], arr[minIndex]);
	}
}

int main() {

	int n = 10000;
	int *arr = SortUtils::generateRandomArray(n, 0, n);
	
	

	SortUtils::testSort("SelectionSort", selectionSort, arr, n);
	
	delete[] arr;
    return 0;
}
