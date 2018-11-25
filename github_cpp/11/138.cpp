#include <iostream>

using namespace std;

void print(int arr[], int length) {
	int i;
	for (i=0;i<length;i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void max_heapify(int arr[], int i, int length) {
	int largest = i;
	int left = 2*i + 1;
	int right = 2*i + 2;

	if ((left < length) && (arr[left] > arr[largest])) {
		largest = left;
	} 
	if ((right < length) && (arr[right] > arr[largest])) {
		largest = right;
	} 

	if (largest != i) {
		swap(&arr[largest], &arr[i]);
		max_heapify(arr, largest, length);
	}
}


void build_max_heap(int arr[], int length) {
	cout << "build_max_heap" << endl;
	int i;
	for (i=length/2; i>=0; i--) {
		cout << "Node: " << i << ", " << arr[i] << endl;
		max_heapify(arr, i, length);
		print(arr, length);
	}
}


void heapsort(int arr[], int length) {
	build_max_heap(arr, length);
	cout << "heapsort" << endl;
	int i;
	for (i=0;i<length;i++) {
		print(arr, length);
		swap(&arr[0], &arr[length-i-1]);
		max_heapify(arr, 0, length-1);
	}
}


int main() {
	int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	int size = sizeof(arr)/sizeof(arr[0]);
	cout << "size: " << size << endl;
	print(arr, size);
	heapsort(arr, size);
	cout << "final" << endl;
	print(arr, size);
	return 0;
}