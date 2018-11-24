/* 插入排序  O(n^2)
工作原理是通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入
*/

#include <iostream>
#include <algorithm>
#include "SortUtils.h"
#include "SelectionSort.h"
using namespace std;

template<typename T>
void insertionSort(T arr[], int n){
	// 数组第一个数固定	
	for(int i = 1; i < n; i++){
		// 找到 arr[i] 的合适插入位置		
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
	// 释放 arr开的数组空间
	delete[] arr1;
	delete[] arr2;

	return 0;
}
