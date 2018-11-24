/* 选择排序
每一次从待排序的数据元素中选出最小（或最大）的一个元素，存放在序列的起始位置，直到全部待排序的数据元素排完  
*/

#include <iostream>
#include "SortUtils.h"
using namespace std;

void selectionSort(int arr[], int len)
{
	for(int i = 0; i < len; i++){
		int minIndex = i;  // 在区间 [i,len) 里寻找最小值
		for(int j = i + 1; j < len; j++)
			if(arr[j] < arr[minIndex])
				minIndex = j;			
			
		swap(arr[i], arr[minIndex]);
	}
}

int main() {

	int n = 10000;
	int *arr = SortUtils::generateRandomArray(n, 0, n);
	//selectionSort(arr, n);
	//SortUtils::printArray(arr, n);

	SortUtils::testSort("SelectionSort", selectionSort, arr, n);
	// 释放 arr开的数组空间
	delete[] arr;
    return 0;
}
