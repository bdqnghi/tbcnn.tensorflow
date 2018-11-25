


#include <iostream>
#include <array>

using namespace std;


void doSort(int nums[], int size);


void print(int nums[], int size);


int main() {
	int nums[] = {12, 11, 14, 6, 2};

	
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
	
	for(int i = 0; i < size; i++) {
		cout << nums[i] << " ";
	}
	cout << endl;
}