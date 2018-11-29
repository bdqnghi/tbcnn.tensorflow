//============================================================================
// Name        : AppliedAlgo.cpp (Programming Assignment 1)
// Author      : Pulkit Mathur - 2000221318
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iomanip>
#include <time.h>
#include <vector>

using namespace std;


// User defined functions
void InsertionSort(int arr[],int size);
void BubbleSort(int arr[],int size);
void ReverseInsertionSort(int arr[],int size);
void ReverseBubbleSort(int arr[],int size);
int findTimeInsertionSort_1(int arr[],int input_size);
int findTimeBubbleSort_1(int arr[],int input_size);
void part1();
void part2();
void part3();


void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void printArray(int arr[], int n)
{
	for (int i=0; i<n; i++)
		cout << arr[i] << " ";
}

int main()
{
	cout << "PART 1" << endl;
	part1();
	cout << "PART 2" << endl;
	part2();
	cout << "PART 3" << endl;
	part3();
	return 0;
}


/*
 *	Function Name: part1
 *	Parameters: None
 *	Description: Provides random input arrays to both insertion and bubble sort and find average running time
 *	over ten iterations.
 */
void part1()
{
	std::vector<double>insertionSortTimings;
	std::vector<double>bubbleSortTimings;

	for(int i = 2000;i <= 50000;i = i+2000)
	{
		int t1=0;
		int t2=0;
		for(int k = 0;k<10;k++)
		{
			int arr1[i];
			int arr2[i];

			//Populating array
			for(int j=0;j<i;j++)
			{
				int x = rand()%i;
				arr1[j] = x;
				arr2[j] = x;
			}

			t1 = t1 + findTimeInsertionSort_1(arr1,i);
			t2 = t2 + findTimeBubbleSort_1(arr2,i);
		}

		insertionSortTimings.push_back(t1/10);
		bubbleSortTimings.push_back(t2/10);
	}

	cout << "Insertion Sort Timings: ";
	for(int i = 0;i<insertionSortTimings.size();i++)
	{
		cout << insertionSortTimings[i] << " ";
	}
	cout << endl;

	cout << "Bubble Sort Timings: ";
	for(int i = 0;i<bubbleSortTimings.size();i++)
	{
		cout << bubbleSortTimings[i] << " ";
	}
	cout << endl;


}

/*
 *	Function Name: part2
 *	Parameters: None
 *	Description: Provides sorted input arrays to both insertion and bubble sort and find average running time
 *	over ten iterations.
 *
 * */
void part2()
{
	std::vector<double>insertionSortTimings;
	std::vector<double>bubbleSortTimings;

	for(int i = 2000;i <= 50000;i = i+2000)
	{
		int t1=0;
		int t2=0;
		for(int k = 0;k<10;k++)
		{
			int arr1[i];
			int arr2[i];

			//Populating array
			for(int j=0;j<i;j++)
			{
				int x = rand()%i;
				arr1[j] = x;
				arr2[j] = x;
			}

			InsertionSort(arr1,i);
			InsertionSort(arr2,i);
			t1 = t1 + findTimeInsertionSort_1(arr1,i);
			t2 = t2 + findTimeBubbleSort_1(arr2,i);
		}

		insertionSortTimings.push_back(t1/10);
		bubbleSortTimings.push_back(t2/10);
	}

	cout << "Insertion Sort Timings: ";
	for(int i = 0;i<insertionSortTimings.size();i++)
	{
		cout << insertionSortTimings[i] << " ";
	}
	cout << endl;

	cout << "Bubble Sort Timings: ";
	for(int i = 0;i<bubbleSortTimings.size();i++)
	{
		cout << bubbleSortTimings[i] << " ";
	}
	cout << endl;
}




/*
 *	Function Name: part3
 *	Parameters: None
 *	Description: Provides reverse sorted input arrays to both insertion and bubble sort and find average running time
 *	over ten iterations.
 *
 * */
void part3()
{
	std::vector<double>insertionSortTimings;
	std::vector<double>bubbleSortTimings;

	for(int i = 2000;i <= 50000;i = i+2000)
	{
		int t1=0;
		int t2=0;
		for(int k = 0;k<10;k++)
		{
			int arr1[i];
			int arr2[i];

			//Populating array
			for(int j=0;j<i;j++)
			{
				int x = rand()%i;
				arr1[j] = x;
				arr2[j] = x;
			}

			ReverseInsertionSort(arr1,i);
			ReverseBubbleSort(arr2,i);
			t1 = t1 + findTimeInsertionSort_1(arr1,i);
			t2 = t2 + findTimeBubbleSort_1(arr2,i);
		}

		insertionSortTimings.push_back(t1/10);
		bubbleSortTimings.push_back(t2/10);
	}

	cout << "Insertion Sort Timings: ";
	for(int i = 0;i<insertionSortTimings.size();i++)
	{
		cout << insertionSortTimings[i] << " ";
	}
	cout << endl;

	cout << "Bubble Sort Timings: ";
	for(int i = 0;i<bubbleSortTimings.size();i++)
	{
		cout << bubbleSortTimings[i] << " ";
	}
	cout << endl;


}



/*
 *	Function Name: InsertionSort
 *	Parameters: Array and it's size
 *	Description: Sorting the input array using insertion sort algorithm
 *
 */
void InsertionSort(int arr[],int size)
{
	//cout << "In insertion sort" << endl;
	int i, key, j;
	for (i = 1; i < size; i++)
	{
		key = arr[i];
		j = i-1;
		while (j >= 0 && arr[j] > key)
		{
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = key;
	}
}




/*
 *	Function Name: BubbleSort
 *	Parameters: Array and it's size
 *	Description: Sorting the input array using bubble sort algorithm
 *
 */
void BubbleSort(int arr[],int size)
{
	//cout << "In bubble sort" << endl;

	int n = size;
	int i, j;
	for (i = 0; i < n-1; i++)
		for (j = 0; j < n-i-1; j++)
			if (arr[j] > arr[j+1])
				swap(&arr[j], &arr[j+1]);
}



/*
 *	Function Name: findTimeInsertionSort_1
 *	Parameters: Array and it's size
 *	Description: Find the running time of insertion sort over different input sizes.
 *
 */
int findTimeInsertionSort_1(int arr[],int input_size)
{
	//cout << "In findTimeInsertionSort_1  size: " <<  input_size << endl;
	//double t1 = 0;
	auto t_start = std::chrono::high_resolution_clock::now();
	InsertionSort(arr,input_size);
	auto t_end = std::chrono::high_resolution_clock::now();
	//t1 = t1 + std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count();
	return std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
}



/*
 *	Function Name: findTimeBubbleSort_1
 *	Parameters: Array and it's size
 *	Description: Find the running time of bubble sort over different input sizes.
 *
 */
int findTimeBubbleSort_1(int arr[],int input_size)
{
	//cout << "In findTimeBubbleSort_1  size: " <<  input_size << endl;

	//double t1 = 0;
	auto t_start = std::chrono::high_resolution_clock::now();
	BubbleSort(arr,input_size);
	auto t_end = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count();
}



/*
 *	Function Name: ReverseInsertionSort
 *	Parameters: Array and it's size
 *	Description: Sort the array using insertion sort in descending order
 *
 */
void ReverseInsertionSort(int arr[],int size)
{
	int temp[size];
	for(int i = 0;i<size;i++)
	{
		temp[i] = arr[i];
	}
	InsertionSort(temp,size);
	for(int i = 0;i<size;i++)
	{
		arr[i] = temp[size-i-1];
	}
}


/*
 *	Function Name: ReverseInsertionSort
 *	Parameters: Array and it's size
 *	Description: Sort the array using bubble sort in descending order
 */
void ReverseBubbleSort(int arr[],int size)
{
	int temp[size];
	for(int i = 0;i<size;i++)
	{
		temp[i] = arr[i];
	}

	BubbleSort(temp,size);

	for(int i = 0;i<size;i++)
	{
		arr[i] = temp[size-i-1];
	}
}
