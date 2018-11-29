#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>

#define ARR_LEN 1024000
//#define ARR_LEN 512000

using namespace std;

int thread_count = 2;

void merge_fun(int *arr1, int *arr2, int first, int middle, int last) {
	int i(first);
	int j(middle);
    //this runs while there are elements in left or right subarray
	for (int k(first); k < last; k++) {
		if (i < middle && (j >= last || arr1[i] <= arr1[j]))
			arr2[k] = arr1[i++];
		else
			arr2[k] = arr1[j++];
	}
}

void _merge_sort(int *arr1, int *arr2, int first, int last) {
	if (last - first == 1)
		return;

	int middle = (first + last) / 2;
	_merge_sort(arr1, arr2, first, middle);
	_merge_sort(arr1, arr2, middle, last);
    //merge subarrays
	merge_fun(arr1, arr2, first, middle, last);
	//copy subbarays to arr1
	for (int i(first); i < last; i++)
        arr1[i] = arr2[i];

}

void _merge_sort_parallel(int *arr1, int *arr2, int first, int last) {
	if (last - first == 1)
		return;

	int middle = (first + last) / 2;
    #pragma omp parallel num_threads(thread_count)
	{
        #pragma omp sections
		{
            #pragma omp section
                _merge_sort(arr1, arr2, first, middle);
            #pragma omp section
                _merge_sort(arr1, arr2, middle, last);
		}
	}
	//merge subarrays
	merge_fun(arr1, arr2, first, middle, last);
	//copy subbarays to arr1
	for (int i(first); i < last; i++)
        arr1[i] = arr2[i];
}

void merge_sort(int *arr1, int len) {
    int arr2[ARR_LEN / 2];
	_merge_sort(arr1, arr2, 0, len);
}

void merge_sort_parallel(int *arr1, int len) {
    int *arr2 = new int[ARR_LEN / 2];
    //arr1 contains elements to be sorted, arr2 is working array
	_merge_sort_parallel(arr1, arr2, 0, len);

	delete[] arr2;
}

int main() {

    int *arr1 = new int[ARR_LEN / 2];
    double start, stop;

    srand(5);
    cout << "Array initialization for sequential merge-sort algorithm..." << endl;
    for (int i = 0; i < ARR_LEN / 2; i++) {
        arr1[i] = rand() % ARR_LEN / 2 + 1;
    }
    cout << "Array initialization ended." << endl << endl;

    cout << "Sorting with sequential merge-sort algorithm..." << endl;
    start = clock();
    merge_sort(arr1, ARR_LEN / 2);
    stop = clock();
    cout << "End of sorting with sequential merge-sort algorithm." << endl << endl;
    cout << "Sorting duration time: " << (stop - start)/CLOCKS_PER_SEC << "s" << endl << endl;
    bool condition = true;
    for (int i = 1; i < ARR_LEN / 2; i++) {
        if (arr1[i] < arr1[i-1])
            condition = false;
    }
    string temp = condition ? "is " : "is not ";
    cout << "Array " << temp << "sorted correctly." << endl << endl << "---------------------------------------------------" << endl;

    cout << "Array initialization for parallel merge-sort algorithm..." << endl;
    for (int i = 0; i < ARR_LEN / 2; i++) {
        arr1[i] = rand() % ARR_LEN / 2 + 1;
    }
    cout << "Array initialization ended." << endl << endl;

    cout << "Sorting with parallel merge-sort algorithm..." << endl;
    start = omp_get_wtime();
    merge_sort_parallel(arr1, ARR_LEN / 2);
    stop = omp_get_wtime();
    cout << "End of sorting with parallel merge-sort algorithm." << endl << endl;
    cout << "Sorting duration time: " << (stop - start) << "s" << endl << endl;
    condition = true;
    for (int i = 1; i < ARR_LEN / 2; i++) {
        if (arr1[i] < arr1[i-1])
            condition = false;
    }
    temp = condition ? "is " : "is not ";
    cout << "Array " << temp << "sorted correctly." << endl << endl << "---------------------------------------------------" << endl;

    delete[] arr1;

    return 0;
}
