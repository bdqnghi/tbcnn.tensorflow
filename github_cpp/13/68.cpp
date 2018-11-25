#include<iostream>
#include<ctime>

#include "SLList.h"
#include "BubbleSort.h"
#include "QuickSort.h"

using namespace std;

void insertRandomElements(int arr[], int n) {
	for (int i=0; i<n; ++i) {
		arr[i] = rand()%100;
	}
}

void insertRandomElements(SLList &arr, int n) {
	for (int i=0; i<n; ++i) {
		ar.insert(rand()%100);
	}
}

void bubbleSortTimeA(int n) {
	int arrA[15000];
	BubbleSort bs;

	insertRandomElements(arrA, n);

	clock_t begin = clock();
	bs.sort(arrA, n);
	clock_t end = clock();
	double time = double(end-begin)/CLOCKS_PER_SEC;

	cout << "Time for " << n << " items: " << time << " seconds." << endl;
}

void quickSortTimeA(int n) {
	int arrA[15000];
	QuickSort qs;

	insertRandomElements(arrA, n);

	clock_t begin = clock();
	qs.sort(arrA, n);
	clock_t end = clock();
	double time = double(end-begin)/CLOCKS_PER_SEC;

	cout << "Time for " << n << " items: " << time << " seconds." << endl;
}


void bubbleSortTimeLL(int n) {
	SLList linkLL;
	BubbleSort bs;

	insertRandomElements(linkLL, n);

	clock_t begin = clock();
	bs.sort(linkLL);
	clock_t end = clock();
	double time = double(end-begin)/CLOCKS_PER_SEC;

	cout << "Time for " << n << " items: " << time << " seconds." << endl;
}

void quickSortTimeLL(int n) {
	SLList linkLL;
	QuickSort qs;

	insertRandomElements(linkLL, n);

	clock_t begin = clock();
	qs.sort(linkLL);
	clock_t end = clock();
	double time = double(end-begin)/CLOCKS_PER_SEC;

	cout << "Time for " << n << " items: " << time << " seconds." << endl;
}

int main() {
	cout << "Running time comparision for array based lists." << endl;
	cout << "Bubble sort: " << endl;
	bubbleSortTimeA(100);
	bubbleSortTimeA(1000);
	bubbleSortTimeA(2500);
	bubbleSortTimeA(5000);
	bubbleSortTimeA(8000);
	bubbleSortTimeA(10000);

	cout << "Quick sort: " << endl;
	quickSortTimeA(100);
	quickSortTimeA(1000);
	quickSortTimeA(2500);
	quickSortTimeA(5000);
	quickSortTimeA(8000);
	quickSortTimeA(10000);

	cout << "Running time comparision for linked lists." << endl;
	cout << "Bubble sort: " << endl;
	bubbleSortTimeLL(100);
	bubbleSortTimeLL(1000);
	bubbleSortTimeLL(2500);
	bubbleSortTimeLL(5000);
	bubbleSortTimeLL(8000);
	bubbleSortTimeLL(10000);

	cout << "Quick sort: " << endl;
	quickSortTimeLL(100);
	quickSortTimeLL(1000);
	quickSortTimeLL(2500);
	quickSortTimeLL(5000);
	quickSortTimeLL(8000);
	quickSortTimeLL(10000);

	return 0;
}
