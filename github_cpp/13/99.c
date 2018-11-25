#include <iostream>
#include <cmath>

using namespace std;

void printArray(int* arr, int length) {
	for (int i = 0; i < length; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

void bubbleSort(int* bubbleSortArray, int length) {
	int reverses = 1;
	int sorted = 0; 
	while (reverses) {
		reverses = 0;
		for (int i = 0; i < length - sorted - 1; ++i) {
			if (bubbleSortArray[i] > bubbleSortArray[i + 1]) {
				const int swapper = bubbleSortArray[i + 1];
				bubbleSortArray[i + 1] = bubbleSortArray[i];
				bubbleSortArray[i] = swapper;
				++reverses;
			}
		}
		++sorted;
	}
	cout << "Result of bubble sort: ";
	printArray(bubbleSortArray, length);
}

void printCountedSortArray(int* arr, int countLength, int shift) {
	for (int i = 0; i < countLength; ++i) {
			for (int j = arr[i]; j > 0; --j) {
				cout << i - shift << " ";
			}
		}
	cout << endl;
}

void countingSort(int* countingSortArray, int length) {
	int minimum = countingSortArray[0];
	int maximum = countingSortArray[0];
	for (int i = 1; i < length; ++i) {
		if (countingSortArray[i] > maximum) {
			maximum = countingSortArray[i];
		}
		if (countingSortArray[i] < minimum) {
			minimum = countingSortArray[i];
		}
	}
	int *forCountingSort = new int[maximum - minimum + 1]{};
	const int countLength = maximum - minimum + 1; 
	const int shift = -minimum;
	
	
	for (int i = 0; i < length; ++i) {
		++forCountingSort[countingSortArray[i] + shift];
	}
	cout << "Result of counting sort: ";
	printCountedSortArray(forCountingSort, countLength, shift);
	delete[] forCountingSort;
}
 
int main()
{
	cout << "Enter length of array" << endl;
	unsigned int length = 0;
	cin >> length;
	int *bubbleSortArray = new int[length] {};
	int *countingSortArray = new int[length] {};
	cout << "Enter elements of array" << endl;
	for (unsigned int i = 0; i < length; ++i) {
		cin >> bubbleSortArray[i];
		countingSortArray[i] = bubbleSortArray[i];
	}
	bubbleSort(bubbleSortArray, length);
	countingSort(countingSortArray, length);
	int forPause = 0;
	cin >> forPause;
	delete[] bubbleSortArray;
	delete[] countingSortArray;
	return 0;
}