#include "InsertionSort.h"
#include "iostream"
using namespace std;


InsertionSort::InsertionSort()
{
	count = 0;
}


InsertionSort::~InsertionSort()
{
}

void InsertionSort::sortAlgoInfo() {
	cout << "\n In Insertion Sort:";
	InsertionSort::enterCountAndNumbersInArray(inputArr);
}

void InsertionSort::enterCountAndNumbersInArray(int inputArr[]) {
	cout << "\n enter the count of #s to sort : " << "\t";
	cin >> count;
	cout << "\n enter number in the array:" << "\t";
	for (int j = 0;j < count;j++) {
		cin >> inputArr[j];
	}

	InsertionSort::printOriginalArr(inputArr, count);
}

void InsertionSort::printOriginalArr(int inputArr[], int) {
	cout << "\n Numbers in the original array:";
	for (int i = 0;i < count;i++) {
		cout << inputArr[i];
		cout << "\t";
	}
	cout << endl;
	InsertionSort::sortInsertion(inputArr, count);
}

void InsertionSort::sortInsertion(int arrToSort[], int count) {
	int tempValue = 0;
	int start = 0;
	int next = 0;
	int prev = 0;
	int ptr = 0;
	int countInLoop = 0;

	ptr = start;
	next = start + 1;
	prev = start;

	for (;ptr < count;) {
		for (;prev >= 0;) {
			if (arrToSort[next] < arrToSort[prev]) {
				tempValue = arrToSort[prev];
				arrToSort[prev] = arrToSort[next];
				arrToSort[next] = tempValue;
				countInLoop++;
			}	//	if loop for swapping ends here

			/* check if the prev value is equal to the start value
			*/
			if (prev == start) {
				/*	This loop would be executed just once. May be during the starting */
				if (countInLoop == 1) {
					ptr = next + 1;
					prev = next;
					next = ptr;
				}
				else {
					ptr = ptr + 1;
					next = next + 1;
					prev = prev + 1;
					next = ptr;
					prev = next;
				}
				countInLoop = 0;
				break;
			}// if loop for checking if its equal to start ends here
			else {
				next = prev;
				prev = prev - 1;
			}
		}	//	for loop ends for prev >=0
	}	//	for loop for ptr ends here
	InsertionSort::printSortedArr(arrToSort, count);
}	//	sortInsertion method ends here

void InsertionSort::printSortedArr(int sortedArr[], int max) {
	cout << "Sorted Array:" << endl;
	for (int l = 0;l < max;l++) {
		cout << sortedArr[l] << "\t";
	}
	cout << endl;
}	//	method printSortedArr ends here

