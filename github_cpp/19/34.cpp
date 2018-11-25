



#ifndef CPP_QUICK_SORT_HPP
#define CPP_QUICK_SORT_HPP

#include <iostream>

auto partition(int arr[], int low, int high) -> int {
	int pivotKey = arr[low];
	while (low != high) {        
		while (low < high && arr[high] >= pivotKey)        
			high --;
		std::swap(arr[low], arr[high]);        
		
		while (low < high && arr[low] <= pivotKey)        
			low ++;
		std::swap(arr[low], arr[high]);        
		
	}


	return low;
}

auto q_sort(int *arr, const int &low, const int &high) -> void {
	if (low != high) {        
		int pivot = partition(arr, low, high);        
		q_sort(arr, low, pivot - 1);        
		q_sort(arr, pivot + 1, high);        
	}
}

auto quick_sort(int arr[], const int &begin, const int &end) -> void {
	q_sort(arr, begin, end - 1);
}

auto main(int, char **) -> int {
	int v[]{4, 2, 4, 5, 1};
	quick_sort(v, 0, 5);

	for (int i : v) {
		std::cout << i << std::endl;
	}

	return 0;
}

#endif 
