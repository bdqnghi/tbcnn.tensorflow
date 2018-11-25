



#include "Insertion_SORT.h"
#include "Merge_Sort.h"
#include "PQ_Heap.h"
#include "Quick_Sort.h"
#include "Shell_Sort.h"

#include <thread>
#include <time.h>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
using std::thread;
using std::cout;
using std::endl;


int* GenArr(int count)
{
	int* arr = new int[count];
	for (int i = 0; i < count; i++)
	{
		arr[i] = rand() % 1001;
	}
	return arr;
}

int main(void)
{
	int k = 2; 
	int option = 0;
	int exit = 0;

	Insertion_Sort insertion;
	Merge_Sort merge;
	PQ_Heap <int>heap(k);
	Quick_Sort quick;
	Shell_Sort shell;

	int gaps[4] = { 12, 7, 3, 1 };

	srand(time(NULL));
	int count = 2000000;
	int* numsOriginal = GenArr(count);

	int* numcpy1 = numsOriginal;
	int* numcpy2 = numsOriginal;
	int* numcpy3 = numsOriginal;
	int* numcpy4 = numsOriginal;
	int* numcpy5 = numsOriginal;

	while (exit != 1)
	{
		cout << "---------------------MENU-----------------------" << endl;
		cout << "|----------------------------------------------|" << endl;
		cout << "|1. Run all 5 sorting algorithms simultaneously|" << endl;
		cout << "|2. Run InsertionSort                          |" << endl;
		cout << "|3. Run MergeSort                              |" << endl;
		cout << "|4. Run HeapSort                               |" << endl;
		cout << "|5. Run QuickSort                              |" << endl;
		cout << "|6. Run ShellSort                              |" << endl;
		cout << "|7. Exit program                               |" << endl;
		cout << "|----------------------------------------------|" << endl;

		while (option >= 0 && option < 7)
		{
			option = 0;
			std::cin >> option;
			if (option == 1)
			{
				thread Insertion(&Insertion_Sort::InsertionSort, insertion, numcpy1, count, 0, 1);
				thread Merge(&Merge_Sort::MergeSort, merge, numcpy2, count);
				thread Quick(&Quick_Sort::QuickSort, quick, numcpy3, count);
				thread Shell(&Shell_Sort::ShellSort, shell, numcpy4, count, gaps, 4);
				thread Heap(&PQ_Heap<int>::Heapsort, heap, numcpy5);

				Insertion.detach();
				Merge.detach();
				Quick.detach();
				Shell.detach();
				Heap.detach();
			}
			else if (option == 2)
			{
				thread Insertion(&Insertion_Sort::InsertionSort, insertion, numcpy1, count, 0, 1);
				Insertion.detach();
			}
			else if (option == 3)
			{
				thread Merge(&Merge_Sort::MergeSort, merge, numcpy2, count);
				Merge.detach();
			}
			else if (option == 4)
			{
				thread Heap(&PQ_Heap<int>::Heapsort, heap, numcpy5);
				Heap.detach();
			}
			else if (option == 5)
			{
				thread Quick(&Quick_Sort::QuickSort, quick, numcpy3, count);
				Quick.detach();
			}
			else if (option == 6)
			{
				thread Shell(&Shell_Sort::ShellSort, shell, numcpy4, count, gaps, 4);
				Shell.detach();
			}
		}
		if (option = 7)
			exit = 1;

		option = 0;
	}
	return 0;
}