

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;



void maxHeapify(int A[], int i, int heapSize) {
	int largest;
	int left = 2*i;
	int right = 2*i + 1;	

	if (left <= heapSize && A[left] > A[i])
		largest = left;
	else
		largest = i;

	if (right <= heapSize && A[right] > A[largest])
		largest = right;
	
	if (largest != i) {
		int temp = A[i];
		A[i] = A[largest];
		A[largest] = temp;
		maxHeapify(A, largest, heapSize);
	}

}



void buildMaxHeap(int A[], int arraySize) {
	int heapSize = arraySize - 1;
	for (int i = floor((arraySize-1)/2); i >= 0; i--)
		maxHeapify(A, i, heapSize);
}



void heapsort(int A[], int arraySize) {
	buildMaxHeap(A, arraySize);
	int heapSize = arraySize - 1;

	for(int i = heapSize; i >= 0; i--) {
		int temp = A[0];
		A[0] = A[heapSize];
		A[heapSize] = temp;

		heapSize--;
		maxHeapify(A, 0, heapSize);
	}
}	

void printResult(int A[], int arraySize) {

	for (int i = 0; i < arraySize; i++) {
		cout << A[i] << ";";
	}

	cout << endl;

}



int main() {

	int arraySize;
	cin >> arraySize;
	int A[arraySize];

	for (int i = 0; i < arraySize; i++) {
		cin >> A[i];
	}

	heapsort(A, arraySize);
	printResult(A, arraySize);

	return 0;
}