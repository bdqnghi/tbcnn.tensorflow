

#include <iostream>
using namespace std;

void bubbleSort(int* arr, int length) {
	for(int i = 0; i < length - 1; i++) {
		bool flag = false;
		for(int j = 0; j < length - i - 1; j++) {
			if(arr[j] > arr[j + 1]) {
				int tmp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = tmp;
				flag = true;
			}
		}
		if(flag == false) {
			return;
		}
	}
}

void printArray(int* arr, int length) {
	for(int i = 0; i < length; i++) {
		cout<<arr[i]<<"\n";
	}
}

int main() {
	int a[10] = {3, 1, 2, 4, 6, 8, 9, 0, 7, 10};

	cout<<"Original array: "<<"\n";
	printArray(a, 10);

	bubbleSort(a, 10);

	cout<<"Array after sorting: "<<"\n";
	printArray(a, 10);
}