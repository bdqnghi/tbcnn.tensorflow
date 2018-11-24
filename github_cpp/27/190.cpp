//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>

using namespace std;

void print(int A[], int size);
void altPrint(int A[], int size);
int getMaxIndex(int A[], int size, int mod);
void sortMinToMax(int A[], int size, int mod);
int getMaxValue (int A[], int size);

void RadixSort::sort(int A[], int size)
{
	// Finds the largest number
	int m = abs(getMaxValue (A, size));
	//cout << "MAX = " << m << endl;
 	
	// Sorts through every digit
	for (int exp = 1; m/exp > 0; exp *= 10) {
		sortMinToMax(A, size, exp*10);
	}
	//print (A, size);
}

void print (int A[], int size) {
	for (int i = 0; i < size; i++) {
		cout << A[i] << endl;
	}
}

void altPrint(int A[], int size) {
	for (int i = 0; i < size; i++) {
		cout << "[" << A[i] << "] ";
	}
	cout << endl;
}

int getMaxIndex(int A[], int size, int mod)
{
	int max = (A[size-1] % mod) / (mod/10);
	int maxIndex = size-1;
	int temp = 0;
	//altPrint(A, size);
	for (int i = size - 2; i >= 0; i--) {
		temp = A[i];
		//cout << "MOD = " << mod << endl;
		temp = (temp % mod) / (mod/10);
		//cout << "NUMBER: " << A[i] << "\tValue: " << temp << endl;
		//cout << temp << " & " << max << endl;
		//cout << "MAX: " << A[maxIndex] << endl;
		//cout << "temp = " << temp << endl;
		//cout << temp << " > " << max << endl;
		/*if (A[i] < 0 && max >= 0) {
			//do nothing to keep max the max
		} else*/
		if (temp > max) {
			max = temp;
			maxIndex = i;
		}
		//cout << "MAX VALUE = " << max << endl;
	}
	//cout << RED << "MAX NUMBER = " << A[maxIndex] << RESET << endl;
	//cout << "temp = " << temp << endl;
	//cout << "MAX VALUE = " << max << endl << endl;
	//cout << MAGENTA << "MAX INDEX = " << maxIndex << RESET << endl;
	//cout << endl;
	return maxIndex;
}

void sortMinToMax(int A[], int size, int mod) {
	for (int i = 0; i < size; i++) {
		int indexOfMax = getMaxIndex(A, size-i, mod);
		//cout << "INDEX OF MAX = " << indexOfMax << endl;
		//cout << "INDEX OF MAX FOUND" << endl;
		int max = A[indexOfMax];
		//cout << CYAN << "MAX NUMBER = " << max << RESET << endl << endl;
		for (int j = indexOfMax; j < size-i-1; j++) {
			//cout << A[j] << " becomes " << A[j+1] << endl;
			A[j] = A[j+1];
		}
		//cout << endl;
		//int temp = A[size-1-i];
		//cout << "temp = " << temp << endl << endl;
		A[size-1-i] = max;
		//A[indexOfMax] = temp;
	}
	//altPrint(A, 6);
}

int getMaxValue (int A[], int size) {
	int maxValue = A[0];
	
	for (int i = 0; i < size; i++) {
		if (A[i] > maxValue) {
			maxValue = A[i];
		}
	}

	return maxValue;
}
