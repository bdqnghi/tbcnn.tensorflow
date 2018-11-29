#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int const SIZE = 10000;
int const RANGE = 10000;

int parent(int i) {
	return (i - 1) / 2;
}

int left(int i) {
	return 2 * i + 1;
}

int right(int i) {
	return 2 * i + 2;
}


void print(int array[]) {
	for(int i = 0; i < SIZE; i++) {
		cout << array[i] << ", ";
	}
	cout << endl;
}
void sift_down(int* array, int root, int end) {

	while (left(root) <= end) {
		int swap = root;
		int child = left(root);
		if (array[child] > array[swap]) {
			swap = child;
		}
		if (child + 1 <= end) {
			if (array[child + 1] > array[swap]) {
				swap = child + 1;
			}
		}
		if (swap == root) {
			break;
		}

		int temp = array[swap];
		array[swap] = array[root];
		array[root] = temp;
		root = swap;
	}



}


void heapify(int* array, int low, int high) {


	int root = parent(SIZE - 1);

	while (root >= 0) {
		sift_down(array, root, SIZE - 1);
		root -= 1;
	}
}



int main() {

	int array[SIZE];

	for (int k = 0; k < SIZE; k++) {
		array[k] = (rand() %RANGE);
	}

	clock_t start = clock();
	
	//make heap
	heapify(array, 0, SIZE - 1);


	for(int i = SIZE - 1; i > 0; i--) {
		int temp = array[i];
		array[i] = array[0];
		array[0] = temp;
		sift_down(array, 0, i - 1);
	}
	//print(array);
	clock_t end = clock();
	clock_t ticks = end - start;
	double duration = ticks / (double) CLOCKS_PER_SEC;
	cout << duration << endl;

	return 0;
}