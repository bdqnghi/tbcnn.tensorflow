/*
 * quick-sort.cpp
 *
 *  Created on: May 3, 2016
 *      Author: ppalwe
 */

/*
 * best/avg time O(logN)
 * worst O(N^2) - based on pivot and if array is sorted in opposite order already
 * Space O(1)
 */
#include "sorting.h"

void Sorting::quickSort(int arr[], int low, int high) {
	if (low < high) {
		// partition array with element <= pivot to left of it and others to the right
		// partition returns the pivot index after partition
		int pivotIndex = partition(arr, low, high);
		//recursively sort two sets from low to current pivotIndex and rest half
		quickSort(arr,low,pivotIndex);
		quickSort(arr, pivotIndex+1,high);
	}
	return;
}

int Sorting::partition(int arr[], int low, int high) {
	Utils util;
	// chose middle as pivot to avoid worst case on partially/completely sorted input
	int pivot = arr[(low+high)/2];
	int pivotIndex = low;
	// put all elements less than pivot to the left of pivot and rest on the right of pivot
	for (int i = low; i < high; i++) {
		if (arr[i] <= pivot) {
			// element is smaller swap with pivotIndex and increment picotIndex
			util.swap(&arr[i], &arr[pivotIndex]);
			pivotIndex++;
		}
	}
	// swap last/pivot element with pivotIndex
	util.swap(&arr[high],&arr[pivotIndex]);
	return pivotIndex;
}
