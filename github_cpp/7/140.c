

#include "sorting.h"

void Sorting::mergeSort(int arr[], int low, int high) {
	int mid;
	if (low < high) {
		mid = (low + high)/2;
		mergeSort(arr, low, mid);
		mergeSort(arr, mid+1, high);
		merge(arr,low,mid,high);
	}
	return;
}

void Sorting::merge(int arr[], int low, int mid, int high) {

	
	int leftRange = mid-low+1;
	int rightRange = high-mid;
	int left[leftRange], right[rightRange];

	for(int i = 0; i < leftRange; i++) {
		left[i] = arr[low+i];
	}

	for(int j = 0; j < rightRange; j++) {
		right[j] = arr[mid+1+j];
	}

	int i=0,k=low;
	int j=0;

	
	while (i < leftRange && j < rightRange) {

		if (left[i] <= right[j]) {
			arr[k] = left[i];
			i++;
		} else {
			arr[k] = right[j];
			j++;
		}

		k++;
	}

	
	while (i < leftRange) {
		arr[k] = left[i];
		i++;
		k++;
	}
	
	while (j < rightRange) {
		arr[k] = right[j];
		j++;
		k++;
	}
	return;
}

