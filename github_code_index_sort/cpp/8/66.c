#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include "omp.h"

#define ARR_LEN 131072000 //aprox. 500MB

using namespace std;

int thread_count = omp_get_num_procs();
int sequential = 1000;

//BASIC QUICK_SORT
template <typename Type>
void partitioning(Type* arr, const int first, const int last, int* i, int* j){
    int a(first), b(last);
    Type pivot(arr[(first + last) / 2]);
    Type temp;
    while (a <= b) {
		while (arr[a] < pivot)
			a++;
		while (arr[b] > pivot)
			b--;
		if (a <= b) {
			temp = arr[a];
			arr[a] = arr[b];
			arr[b] = temp;
			a++;
			b--;
		}
	}
	*i = a;
	*j = b;
}

template <typename Type>
void _quick_sort(Type* arr, const int first, const int last){
    int i, j;
  	//partitioning
	partitioning(arr, first, last, &i, &j);
	//sorting
	if (first < j)
        _quick_sort(arr, first, j);
	if (i< last)
        _quick_sort(arr, i, last);
}

template <typename Type>
void quick_sort(Type* arr, int len){
    _quick_sort(arr, 0, len - 1);
}
//BASIC QUICK-SORT END

//PARALLEL QUICK-SORT
template <typename Type>
void _quicksort_parallel(Type* arr, const int first, const int last, const int part) {
    int i, j;
    //partitioning
    partitioning(arr, first, last, &i, &j);
    //sorting
	if (last - first < part) {
		if (first < j){ _quicksort_parallel(arr, first, j, part); }
		if (i < last){ _quicksort_parallel(arr, i, last, part); }
	}
	else {
		#pragma omp task
		    _quicksort_parallel(arr, first, j, part);
		#pragma omp task
		    _quicksort_parallel(arr, i, last, part);
	}

}

template <typename Type>
void quick_sort_parallel(Type* arr, int len) {
	#pragma omp parallel num_threads(thread_count)
	{
		#pragma omp single nowait
		{
			_quicksort_parallel(arr, 0, len - 1, sequential); //sequential defined on top
		}
	}
}
//PARALLEL QUICK-SORT END

//Comparator for qsort
int comparator(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

int main()
{
	int *arr1 = new int[ARR_LEN];
	int *arr2 = new int[ARR_LEN];
	int *arr3 = new int[ARR_LEN];
    double start, stop;

    srand(5);
    cout << "Initialization of arrays..." << endl;
    for (int i = 0; i < ARR_LEN; i++) {
        arr1[i] = rand() % ARR_LEN + 1;
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
    cout << "Initialization of arrays finished." << endl << endl;

    cout << "Sorting with qsort from cstdlib..." << endl;
    start = clock();
    qsort(arr1, ARR_LEN, sizeof(int), comparator);
    stop = clock();
    cout << "End of sorting with qsort from cstdlib." << endl << endl;
    cout << "Sorting duration: " << (stop - start)/CLOCKS_PER_SEC << "s" << endl << endl;
    bool condition = true;
    for (int i = 1; i < ARR_LEN; i++) {
        if (arr1[i] < arr1[i-1]) {
            condition = false;
            break;
        }
    }
    string temp = condition ? "is " : "is not ";
    cout << "Array " << temp << "sorted correctly." << endl << endl << "---------------------------------------------------" << endl;

    cout << endl << endl << endl;

    cout << "Sorting with sequential quick-sort algorithm..." << endl;
    start = clock();
    quick_sort(arr2, ARR_LEN);
    stop = clock();
    cout << "End of sorting with sequential quick-sort algorithm." << endl << endl;
    cout << "Sorting duration: " << (stop - start)/CLOCKS_PER_SEC << "s" << endl << endl;
    condition = true;
    for (int i = 1; i < ARR_LEN; i++) {
        if (arr2[i] < arr2[i-1]) {
            condition = false;
            break;
        }
    }
    temp = condition ? "is " : "is not ";
    cout << "Array " << temp << "sorted correctly." << endl << endl << "---------------------------------------------------" << endl;

    cout << endl << endl << endl;

    cout << "Sorting with parallel quick-sort algorithm..." << endl;
    start = omp_get_wtime();
    quick_sort_parallel(arr3, ARR_LEN);
    stop = omp_get_wtime();
    cout << "End of sorting with parallel quick-sort algorithm." << endl << endl;
    cout << "Sorting duration: " << (stop - start) << "s" << endl << endl;
    condition = true;
    for (int i = 1; i < ARR_LEN; i++) {
        if (arr3[i] < arr3[i-1]) {
            condition = false;
            break;
        }
    }
    temp = condition ? "is " : "is not ";
    cout << "Array " << temp << "sorted correctly." << endl << endl << "---------------------------------------------------" << endl;

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    return 0;

}
