#include <stdio.h>

void makeHeap(int* arr, int length);
void siftDown(int *arr, int length, int id);
int getParentId(int id);
int getLeftChildId(int id);
int getRightChildId(int id);
//TODO: remove return pointers, use void
int* insert(int* arr, int length, int val);
int* extendArray(int* arr, int length, int add);
void siftUp(int* arr, int length, int id);
int extractMin(int* arr, int length);

int main()
{
	int length = 20;
	int* arr = new int[length];
	int temp[20] = { 20, 10, 38, 35, 9, 11, 89, 93, 52, 31, 53, 91, 63, 5, 86, 67, 39, 81, 6, 23 };

	for (int i = 0; i < length; i++) {
		arr[i] = temp[i];
	}

	makeHeap(arr, length);
	arr = insert(arr, length, 1);
	length++;

	for (int i = 0, min = -1; i < length; i++) {
		min = extractMin(arr, length - i);

		printf("%d ", min);
	}

	//1 5 6 9 10 11 20 23 31 35 38 39 52 53 63 67 81 86 89 91 93

	return 0;
}

int extractMin(int* arr, int length) {
	int min = arr[0];

	arr[0] = arr[length - 1];
	arr[length - 1] = -1;

	siftDown(arr, length - 1, 0);

	return min;
}

int* insert(int* arr, int length, int val) {
	arr = extendArray(arr, length, 1);
	arr[length] = val;
	siftUp(arr, length + 1, length);
	return arr;
}

//TODO: it is not good idea to extend array by one element,
//it is better to extend by set of elements, by something
//dependend on N
int* extendArray(int* arr, int length, int add) {
	int* temp = new int[length + add];

	for (int i = 0; i < length; i++) {
		temp[i] = arr[i];
	}

	delete [] arr;
	arr = temp;

	return arr;
}

void makeHeap(int* arr, int length) {
	for (int i = length / 2 - 1; i >= 0; i--) {
		siftDown(arr, length, i);
	}
}

void siftUp(int* arr, int length, int id) {
	int parentId = getParentId(id);

	if (id == 0) {
		return;
	}

	if (arr[parentId] > arr[id]) {
		int temp = arr[id];
		arr[id] = arr[parentId];
		arr[parentId] = temp;
		siftUp(arr, length, parentId);
	}
}

void siftDown(int *arr, int length, int id) {
	int leftChildId = getLeftChildId(id);
	int rightChildId = getRightChildId(id);

	if (rightChildId == length) {
		rightChildId = leftChildId;
	}

	if (rightChildId > length) {
		return;
	}
	
	if (arr[id] > arr[leftChildId] || arr[id] > arr[rightChildId]) {
		int minChildId = arr[leftChildId] > arr[rightChildId] ? rightChildId : leftChildId;
		int temp = arr[minChildId];
		arr[minChildId] = arr[id];
		arr[id] = temp;
		siftDown(arr, length, minChildId);
	}
}

int getParentId(int id) {
	return (id - 1) / 2;
}

int getLeftChildId(int id) {
	return id * 2 + 1;
}

int getRightChildId(int id) {
	return id * 2 + 2;
}
