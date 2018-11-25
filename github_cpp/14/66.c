







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
	
	int m = abs(getMaxValue (A, size));
	
 	
	
	for (int exp = 1; m/exp > 0; exp *= 10) {
		sortMinToMax(A, size, exp*10);
	}
	
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
	
	for (int i = size - 2; i >= 0; i--) {
		temp = A[i];
		
		temp = (temp % mod) / (mod/10);
		
		
		
		
		
		
		if (temp > max) {
			max = temp;
			maxIndex = i;
		}
		
	}
	
	
	
	
	
	return maxIndex;
}

void sortMinToMax(int A[], int size, int mod) {
	for (int i = 0; i < size; i++) {
		int indexOfMax = getMaxIndex(A, size-i, mod);
		
		
		int max = A[indexOfMax];
		
		for (int j = indexOfMax; j < size-i-1; j++) {
			
			A[j] = A[j+1];
		}
		
		
		
		A[size-1-i] = max;
		
	}
	
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
