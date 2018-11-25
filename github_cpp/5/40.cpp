

#include <iostream>
#include <algorithm>
#include "SortUtils.h"
#include "SelectionSort.h"
using namespace std;

template<typename T>
void insertionSort(T arr[], int n){
	
	for(int i = 1; i < n; i++){
		
		for(int j = i; j > 0 && arr[j] < arr[j-1]; j--)
			swap(arr[j], arr[j - 1]);
		
	}
}

int main(){
	int n = 100000;
	int *arr1 = SortUtils::generateRandomArray(n, 0, n);
	int *arr2 = SortUtils::copyIntArray(arr1, n);

	SortUtils::testSort("SelectionSort", selectionSort, arr1, n);
	SortUtils::testSort("InsertionSort", insertionSort, arr2, n);
	
	delete[] arr1;
	delete[] arr2;

	return 0;
}
