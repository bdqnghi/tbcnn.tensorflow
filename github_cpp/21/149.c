#include <iostream>
using namespace std;

template <typename T>
void printArray(T value[], int count);

template <typename T>
void selectionSort(T value[], int count) {
	int i = 0, j = 0;
	int min = 0, temp = 0;

	
	
	for (i = 0; i < count - 1; i++) {
		
		min = i;
		for (j = i + 1; j < count; j++) {
			
			if (value[j] < value[min]) {
				min = j;
			}
		}
		temp = value[i];
		value[i] = value[min];
		value[min] = temp;

		printf("Step-%d, ", i + 1);
		printArray(value, count);
	}
}

int main() {
	int values[] = { 80, 50, 70, 10, 60, 20, 40, 30 };

	printf("Before Sort\n");
	printArray(values, 8);

	selectionSort(values, 8);

	printf("\nAfter Sort\n");
	printArray(values, 8);

	return 0;
}

template <typename T>
void printArray(T value[], int count) {
	int i = 0;
	for (i = 0; i < count; i++) {
		cout << value[i] << " ";
	}
	printf("\n");
}