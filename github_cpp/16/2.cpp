



#include "shell_sort.hpp"
#include "stopwatch.hpp"


#include "bubble.hpp"
#include "emersonRadix.hpp"
#include "InsertionSort.hpp"
#include "merge.hpp"
#include "HeapNorm.hpp"

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(0)); 

	int n = 10000;

	std::vector<int> shell(n);

	
	for (int i=0; i < n; i++)
		shell[i] = rand();

	
	if (!std::is_sorted(shell.begin(), shell.end()))
		std::cout << "Original vector confirmed unsorted" << std::endl << std::endl;

	
	std::vector<int> bubble(shell.begin(), shell.end());
	std::vector<int> radix(shell.begin(), shell.end());
	std::vector<int> insertion(shell.begin(), shell.end());
	std::vector<int> merge(shell.begin(), shell.end());
	HeapNorm<int> heap(shell);

	
	bubblesort(bubble.begin(), bubble.end());
	if (!std::is_sorted(bubble.begin(), bubble.end()))
		std::cout << "Bubble sort FAIL" << std::endl;
	else
		std::cout << "Bubble sort PASS" << std::endl;

	
	shellsort(shell);
	if (!std::is_sorted(shell.begin(), shell.end()) || !std::equal(shell.begin(), shell.end(), bubble.begin()))
		std::cout << "Shell sort FAIL" << std::endl;
	else
		std::cout << "Shell sort PASS" << std::endl;

	
	emersonSort(radix);
	if (!std::is_sorted(radix.begin(), radix.end()) || !std::equal(radix.begin(), radix.end(), bubble.begin()))
		std::cout << "Radix sort FAIL" << std::endl;
	else
		std::cout << "Radix sort PASS" << std::endl;

	
	InsertionSort(insertion);
	if (!std::is_sorted(insertion.begin(), insertion.end()) || !std::equal(insertion.begin(), insertion.end(), bubble.begin()))
		std::cout << "Insertion sort FAIL" << std::endl;
	else
		std::cout << "Insertion sort PASS" << std::endl;

	
	MergeSort(merge, 0, merge.size());
	if (!std::is_sorted(merge.begin(), merge.end()) || !std::equal(merge.begin(), merge.end(), bubble.begin()))
		std::cout << "Merge sort FAIL" << std::endl;
	else
		std::cout << "Merge sort PASS" << std::endl;

	
	heap.buildHeap();
	heap.sort();
	std::vector<int> vheap = heap.getvector();
	if (!std::is_sorted(vheap.begin(), vheap.end()) || !std::equal(vheap.begin(), vheap.end(), bubble.begin()))
		std::cout << "Heap sort FAIL" << std::endl;
	else
		std::cout << "Heap sort PASS" << std::endl;

	return 0;
}
