//	SortingProject.cpp
//	Joshua Castelli

#include "stdafx.h"
#include "heapSort.h"
#include <math.h>
#include <time.h>

int heapSort::parent(int i) { return (floor(i/2)); };
int heapSort::leftChild(int i) { return (2 * i); };
int heapSort::rightChild(int i) { return ((2*i) + 1); };
	heapSort::heapSort() {};
void heapSort::sort(string* list, int size) {
		string* heap = list;
		int heapSize = size-1;
		sortHeap(heap, heapSize);
	};
void heapSort::maxHeapify(string* heap, int i, int heapSize) {

	left = leftChild(i);
	right = rightChild(i);

	if (left <= heapSize && heap[left] > heap[right]) {
		largest = left;
	}
	else {
		largest = i;
	}

	if (right <= heapSize && heap[right] > heap[largest]) {
		largest = right;
	}

	if (largest != i) {
		string temp = heap[i];
		heap[i] = heap[largest];
		heap[largest] = temp;
		maxHeapify(heap, largest, heapSize);
	}

};
void heapSort::buildMaxHeap(string* heap, int heapSize) {
	clock_t timerStart;
	timerStart = clock();

	for (int i = (floor(heapSize / 2)); i >= 0; i--) {
		maxHeapify(heap, i, heapSize);
	}

	cout << "BuildHeap Time: " << ((float)(clock() - timerStart) / CLOCKS_PER_SEC) * 1000 << "ms" << endl;
};
void heapSort::sortHeap(string* heap, int heapSize) {
	buildMaxHeap(heap, heapSize);
	for (int i = heapSize; i >= 1; i--) {
		string temp = heap[0];
		heap[0] = heap[i];
		heap[i] = temp;
		heapSize--;
		maxHeapify(heap,0,heapSize);
	}
};
void heapSort::maxHeapInsert() {
	//not implemented yet.
};
string heapSort::heapExtracMax(string* heap, int heapSize) {
	string max;
	if (heapSize < 0) {
		cout << "error, heap underflow" << endl;
	}
	else {
		max = heap[0];
		heap[0] = heap[heapSize];
		heapSize--;
		maxHeapify(heap,0,heapSize);
	}
	return max;
};
void heapSort::heapIncreaseKey() {
	//not implemented yet.
};
string heapSort::heapMaximum(string* heap) { return heap[0]; };