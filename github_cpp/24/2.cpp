



#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <algorithm>

using namespace std;


int main()
{
	srand(time(NULL));

	int arr1[1000];
	int arr2[10000];
	int arr3[100000];
	int	arr4[1000000];
	int results;
	int results2;
	int numb;

	cout << "got here 1" << endl;

	for (int i = 0; i < 1000; i++) {
		int x = rand() % 1000000;
		arr1[i] = x;
	}
	for (int i = 0; i < 10000; i++) {
		int x = rand() % 1000000;
		arr2[i] = x;
	}
	for (int i = 0; i < 100000; i++) {
		int x = rand() % 1000000;
		arr3[i] = x;
	}
	for (int i = 0; i < 1000000; i++) {
		int x = rand() % 1000000;
		arr4[i] = x;
	}

	searchList();

	std::sort(arr1, arr1 + 1000);
	for (int i = 0; i < 1000; i++) {
		std::cout << arr1[i] << ' ';
	}
	std::sort(arr2, arr2 + 10000);
	for (int i = 0; i < 10000; i++) {
		std::cout << arr2[i] << ' ';
	}
	std::sort(arr3, arr3 + 100000);
	for (int i = 0; i < 100000; i++) {
		std::cout << arr3[i] << ' ';
	}
	std::sort(arr4, arr4 + 1000000);
	for (int i = 0; i < 1000000; i++) {
		std::cout << arr4[i] << ' ';
	}

	binarysearch();

	cout << "memes";
}

int searchList(const int[], int, int) {
	const int size = int.size();
	results = searchList(arr1, 1000, 100);

	if (results == -1) {
		cout << "The matching number was not found";
	}
	else {
		cout << "Found it" << endl;
		cout << (results + 1) << endl;
	}

	std::cout << "got here" << std::endl;
	return 0;
}

int binarysearch(const int[], int size, int value) {
	
	cout << "enter a number to search for: ";
	cin >> numb;

	results2 = binarysearch(arr1, 1000, numb);
	if (results2 == -1) {
		cout << "That number does not exist in the array";
	}
	else {
		cout << "That ID is found in the array";
		cout << " in the array";
	}
	return 0;
}


