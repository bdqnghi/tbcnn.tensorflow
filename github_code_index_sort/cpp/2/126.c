/**
* Name: Thomas Asuncion
* Program - Insert vs Merge Sort Analyzer
**/

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <chrono>
#include "Sort.h"

using String = std::string;
using namespace std::chrono;

// Declare the 'blueprint' of the functions here.
void printIntroduction();
void printArray(int[], int);
void generateRandomArray(int[], int);
void case1AscendInsertSorted();
void case1AscendMergeSorted();
void case2DescendInsertSorted();
void case2DescendMergeSorted();
void case3RandInsertSorted();
void case3RandMergeSorted();

// Global variable for array length declared here:
const static int length = 100;

Sort SortingMethod;

int main()
{
	printIntroduction();

	case1AscendInsertSorted();
	case1AscendMergeSorted();

	case2DescendInsertSorted();
	case2DescendMergeSorted();

	case3RandInsertSorted();
	case3RandMergeSorted();

	return 0;
}

void printIntroduction()
{
	std::cout << " ___________________________________________________________________________________________" << std::endl;
	std::cout << "|          ### Welcome to the insertion sort & merge sort runtime analyzer! ###             |" << std::endl;
	std::cout << "|                                                                                           |" << std::endl;
	std::cout << "| The following program will run an insertion-sort and merge-sort on three different cases! |" << std::endl;
	std::cout << "| The program can be configured by adjusting the global length variable in the Main.cpp.    |" << std::endl;
	std::cout << "|                                                                                           |" << std::endl;
	std::cout << "| The three cases that will be looked into are:                                             |" << std::endl;
	std::cout << "|    - Case 1: For a sorted array of ascending order.                                       |" << std::endl;
	std::cout << "|    - Case 2: For a sorted array of descending order.                                      |" << std::endl;
	std::cout << "|    - Case 3: For an unsorted array of random order.                                       |" << std::endl;
	std::cout << "|                                                                                           |" << std::endl;
	std::cout << "| Note: The array elements will be randomly generated integers from 0 - 99.                 |" << std::endl;
	std::cout << "|___________________________________________________________________________________________|" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
}

void printArray(int arr[], int n)
{
	std::cout << "[ ";
	for (int i = 0; i<n; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << "]";
	std::cout << "\n\n";
}

void generateRandomArray(int arr[], int n)
{
	for (int i = 0; i<n; i++) {
		arr[i] = rand() % 99; // generate a random integer from 0 - 99.
	}
}

void case1AscendInsertSorted()
{
	int arr[length];

	// Generate an array of random integers, sort it ascendingly, and print.
	generateRandomArray(arr, length);
	SortingMethod.insertionSortAscending(arr, length);
	std::cout << "INSERT-SORT CASE 1 - The following array is of size " << length << " in ascending order: " << std::endl;
	printArray(arr, length);

	// Start measure time here.
	auto start = high_resolution_clock::now();

	SortingMethod.insertionSortAscending(arr, length);

	// End measure time here.
	auto end = high_resolution_clock::now();

	std::cout << "Running through the insertion-sort algorithm on the ascendingly sorted array...\n\n";

	std::cout << "Sorted array (insertion sort):" << std::endl;
	printArray(arr, length);

	// Print out runtime in microseconds.
	auto duration = duration_cast<microseconds>(end - start);
	std::cout << "  --> The following runtime of the insertion-sort algorithm in this case is " << duration.count() << " microseconds. \n\n";
}

void case1AscendMergeSorted()
{
	int arr[length];

	// Generate an array of random integers, sort it ascendingly, and print.
	generateRandomArray(arr, length);
	SortingMethod.insertionSortAscending(arr, length);
	std::cout << "MERGE-SORT CASE 1 - The following array is of size " << length << " in ascending order: " << std::endl;
	printArray(arr, length);

	// Start measure time here.
	auto start = high_resolution_clock::now();

	SortingMethod.mergeSort(arr, length);

	// End measure time here.
	auto end = high_resolution_clock::now();

	std::cout << "Running through the merge-sort algorithm on the ascendingly sorted array...\n\n";

	std::cout << "Sorted array (merge sort):" << std::endl;
	printArray(arr, length);

	// Print out runtime in microseconds.
	auto duration = duration_cast<microseconds>(end - start);
	std::cout << "  --> The following runtime of the merge-sort algorithm in this case is " << duration.count() << " microseconds. \n";
	std::cout << "_____________________________________________________________________________________________________________________ \n\n";
}

void case2DescendInsertSorted()
{
	int arr[length];

	// Generate an array of random integers, sort it descendingly, and print.
	generateRandomArray(arr, length);
	SortingMethod.insertionSortDescending(arr, length);
	std::cout << "INSERT-SORT CASE 2: The following array is of size " << length << " in descending order: " << std::endl;
	printArray(arr, length);

	// Start measure time here.
	auto start = high_resolution_clock::now();

	SortingMethod.insertionSortAscending(arr, length);

	// End measure time here.
	auto end = high_resolution_clock::now();

	std::cout << "Running through the insertion-sort algorithm on the descendingly sorted array...\n\n";

	std::cout << "Sorted array (insertion sort):" << std::endl;
	printArray(arr, length);

	// Print out runtime in microseconds.
	auto duration = duration_cast<microseconds>(end - start);
	std::cout << "  --> The following runtime of the insertion-sort algorithm in this case is " << duration.count() << " microseconds. \n\n";
}

void case2DescendMergeSorted()
{
	int arr[length];

	// Generate an array of random integers, sort it ascendingly, and print.
	generateRandomArray(arr, length);
	SortingMethod.insertionSortDescending(arr, length);
	std::cout << "MERGE-SORT CASE 2 - The following array is of size " << length << " in descending order: " << std::endl;
	printArray(arr, length);

	// Start measure time here.
	auto start = high_resolution_clock::now();

	SortingMethod.mergeSort(arr, length);

	// End measure time here.
	auto end = high_resolution_clock::now();

	std::cout << "Running through the merge-sort algorithm on the descendingly sorted array...\n\n";

	std::cout << "Sorted array (merge sort):" << std::endl;
	printArray(arr, length);

	// Print out runtime in microseconds.
	auto duration = duration_cast<microseconds>(end - start);
	std::cout << "  --> The following runtime of the merge-sort algorithm in this case is " << duration.count() << " microseconds. \n";
	std::cout << "_____________________________________________________________________________________________________________________ \n\n";
}

void case3RandInsertSorted()
{
	int arr[length];

	// Generate an array of random integers - non sorted.
	generateRandomArray(arr, length);
	std::cout << "INSERT-SORT CASE 3: The following array is of size " << length << " in random order: " << std::endl;
	printArray(arr, length);

	// Start measure time here.
	auto start = high_resolution_clock::now();

	SortingMethod.insertionSortAscending(arr, length);

	// End measure time here.
	auto end = high_resolution_clock::now();

	std::cout << "Sorted array (insertion sort):" << std::endl;
	printArray(arr, length);

	// Print out runtime in microseconds.
	auto duration = duration_cast<microseconds>(end - start);
	std::cout << "  --> The following runtime of the insertion-sort algorithm in this case is " << duration.count() << " microseconds. \n\n";
}

void case3RandMergeSorted()
{
	int arr[length];

	// Generate an array of random integers, sort it ascendingly, and print.
	generateRandomArray(arr, length);
	std::cout << "MERGE-SORT CASE 3 - The following array is of size " << length << " in random order: " << std::endl;
	printArray(arr, length);

	// Start measure time here.
	auto start = high_resolution_clock::now();

	SortingMethod.mergeSort(arr, length);

	// End measure time here.
	auto end = high_resolution_clock::now();

	std::cout << "Running through the merge-sort algorithm on the randomly generated unsorted array...\n\n";

	std::cout << "Sorted array (merge sort):" << std::endl;
	printArray(arr, length);

	// Print out runtime in microseconds.
	auto duration = duration_cast<microseconds>(end - start);
	std::cout << "  --> The following runtime of the merge-sort algorithm in this case is " << duration.count() << " microseconds. \n";
	std::cout << "_____________________________________________________________________________________________________________________ \n\n";
}
