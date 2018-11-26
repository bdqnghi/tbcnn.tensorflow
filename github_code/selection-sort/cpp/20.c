/**
*@author Csillag Robert
*/

#include "Profiler.h"
#include <stdio.h>
#include <math.h>


#define MAX_SIZE 10000

Profiler profiler("Median case");

void selection_sort(int* arr_to_sort, int n) {
	Operation sc = profiler.createOperation("selection_count", n);
	Operation sa = profiler.createOperation("selection_attr", n);
	for (int i = 0; i < n; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
			sc.count();
			if (arr_to_sort[j] < arr_to_sort[min]) {
				min = j;
			}
		}
		if (min != i) {
			sa.count(3);
			int aux = arr_to_sort[i];
			arr_to_sort[i] = arr_to_sort[min];
			arr_to_sort[min] = aux;
		}
	}
}

void insertion_sort(int* arr_to_sort, int n) {
	Operation ic = profiler.createOperation("insertion_count", n);
	Operation ia = profiler.createOperation("insertion_attr", n);
	for (int i = 1; i < n; i++) {
		ia.count();
		int aux = arr_to_sort[i];
		int j = i - 1;
		while ((j >= 0) && (aux < arr_to_sort[j])) {
			ic.count();
			ia.count();
			arr_to_sort[j + 1] = arr_to_sort[j];
			j--;
		}
		if (j > 0) {
			ic.count();
		}
		arr_to_sort[j + 1] = aux;
		ia.count();
	}
}

void bubble_sort(int* arr_to_sort, int n) {
	Operation bc = profiler.createOperation("bubble_count", n);
	Operation ba = profiler.createOperation("bubble_attr", n);
	bool flag = true;
	while (flag) {
		flag = false;
		for (int i = 0; i < n - 1; i++) {
			bc.count();
			if (arr_to_sort[i] > arr_to_sort[i + 1]) {
				ba.count(3);
				int aux = arr_to_sort[i];
				arr_to_sort[i] = arr_to_sort[i + 1];
				arr_to_sort[i + 1] = aux;
				flag = true;
			}
		}
		n--;
	}
}

int main(void) {
	int arr[MAX_SIZE];
	int arr2[MAX_SIZE];
	int arr3[MAX_SIZE];
	int arr4[MAX_SIZE];

	for (int n = 100; n <= MAX_SIZE; n += 100) {
		for (int i = 0; i < 5; i++) {
			FillRandomArray(arr, n, 10, 100000, false, 0);
			memcpy(arr2, arr, sizeof(arr2));
			selection_sort(arr2, n);
			memcpy(arr3, arr, sizeof(arr3));
			insertion_sort(arr3, n);
			memcpy(arr4, arr, sizeof(arr4));
			bubble_sort(arr4, n);
		}
	}

	profiler.divideValues("selection_count", 5);
	profiler.divideValues("selection_attr", 5);
	profiler.divideValues("insertion_count", 5);
	profiler.divideValues("insertion_attr", 5);
	profiler.divideValues("bubble_count", 5);
	profiler.divideValues("bubble_attr", 5);

	profiler.addSeries("total_selection_med", "selection_count", "selection_attr");
	profiler.addSeries("total_insertion_med", "insertion_count", "insertion_attr");
	profiler.addSeries("total_bubble_med", "bubble_count", "bubble_attr");

	profiler.createGroup("median_case_count", "selection_count", "insertion_count", "bubble_count");
	profiler.createGroup("median_case_attr", "selection_attr", "insertion_attr", "bubble_attr");
	profiler.createGroup("median_case_attr_selection", "selection_attr");
	profiler.createGroup("median_case_total", "total_selection_med", "total_insertion_med", "total_bubble_med");

	profiler.reset("Defav case");

	for (int n = 100; n <= MAX_SIZE; n += 100) {
		FillRandomArray(arr, n, 10, 100000, false, 1);
		arr[0] = arr[n-1] + 1;
		selection_sort(arr, n);
	}

	for (int n = 100; n <= MAX_SIZE; n += 100) {
		FillRandomArray(arr2, n, 10, 100000, false, 2);
		memcpy(arr3, arr2, sizeof(arr3));
		insertion_sort(arr2, n);
		bubble_sort(arr3, n);
	}

	profiler.addSeries("total_selection_defav", "selection_count", "selection_attr");
	profiler.addSeries("total_insertion_defav", "insertion_count", "insertion_attr");
	profiler.addSeries("total_bubble_defav", "bubble_count", "bubble_attr");

	profiler.createGroup("defav_case_count", "selection_count", "insertion_count", "bubble_count");
	profiler.createGroup("defav_case_attr", "selection_attr", "insertion_attr", "bubble_attr");
	profiler.createGroup("defav_case_attr_selection", "selection_attr");
	profiler.createGroup("defav_case_total", "total_selection_defav", "total_insertion_defav", "total_bubble_defav");

	profiler.reset("Fav case");

	for (int n = 100; n <= MAX_SIZE; n += 100) {
			FillRandomArray(arr, n, 10, 100000, false, 1);
			memcpy(arr2, arr, sizeof(arr2));
			selection_sort(arr2, n);
			memcpy(arr3, arr, sizeof(arr3));
			insertion_sort(arr3, n);
			memcpy(arr4, arr, sizeof(arr4));
			bubble_sort(arr4, n);
	}

	profiler.addSeries("total_selection_fav", "selection_count", "selection_attr");
	profiler.addSeries("total_insertion_fav", "insertion_count", "insertion_attr");
	profiler.addSeries("total_bubble_fav", "bubble_count", "bubble_attr");

	profiler.createGroup("fav_case_count", "selection_count", "insertion_count", "bubble_count");
	profiler.createGroup("fav_case_count_ins_bub", "insertion_count", "bubble_count");
	profiler.createGroup("fav_case_attr", "selection_attr", "insertion_attr", "bubble_attr");
	profiler.createGroup("fav_case_total", "total_selection_fav", "total_insertion_fav", "total_bubble_fav");
	profiler.createGroup("fav_case_total_ins_bub", "total_insertion_fav", "total_bubble_fav");

	profiler.showReport();
	return 0;
}