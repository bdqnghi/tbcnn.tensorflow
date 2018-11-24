//quick sort

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;

void writeArr(int *arr, int len);
void printArr(int *arr, int len, ofstream &fout, char sep = ' ');

void quickSort(int *arr, int l, int r);
void quickSort(int *arr, int n);

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	srand(time(0));

	int len;
	fin >> len;

	int *arr = new int[len];

	writeArr(arr, len);
	//printArr(arr, len, fout, '\n');

	quickSort(arr, len);
	
	printArr(arr, len, fout, '\n');

	fin.close();
	fout.close();

	delete[] arr;
	return 0;
}

void quickSort(int *arr, int l, int r) {
	int i = l, j = r, middle = arr[(i + j) / 2];

	do {
		while (middle > arr[i]) i++;
		while (middle < arr[j]) j--;

		if (i <= j) {
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;

			i++; j--;
		}

	} while (i < j);

	if (i < r) quickSort(arr, i, r);
	if (j > l) quickSort(arr, l, j);
}

void quickSort(int *arr, int n) {
	quickSort(arr, 0, n - 1);
}

void writeArr(int *arr, int len) {
	for (int i = 0; i < len; i++) {
		arr[i] = rand() % 10000;
	}
}

void printArr(int *arr, int len, ofstream &fout, char sep) {
	for (int i = 0; i < len; i++) {
		fout << arr[i] << sep;
	}
}
