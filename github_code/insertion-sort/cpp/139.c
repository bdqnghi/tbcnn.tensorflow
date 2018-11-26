
/**
 * Author: SAHIL SHARMA
 * Created On: March 16, 2018
 * Project: Implementation of Insertion Sort.
 */

#include <iostream>
#include <array>

using namespace std;

// Function to sort array.
void doSort(int nums[], int size);

// Function to print the array.
void print(int nums[], int size);


int main() {
	int nums[] = {12, 11, 14, 6, 2};

	// Find the size of array.
	int size = sizeof(nums) / sizeof(nums[0]);

	doSort(nums, size);
	print(nums, size);

	return 0;
}


void doSort(int nums[], int size) {
	int key;

	for(int i = 0; i < size; i++) {
		key = nums[i];
		int j = i - 1;

		while(j >= 0 && nums[j] > key) {
			nums[j+1] = nums[j];
			j = j - 1;
		}
		nums[j + 1] = key;
	}

}

void print(int nums[], int size) {
	// Loop through each element of array.
	for(int i = 0; i < size; i++) {
		cout << nums[i] << " ";
	}
	cout << endl;
}