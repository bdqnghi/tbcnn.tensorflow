#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
using namespace std;
// 0.339637 seconds desordenado
// 0.392636 seconds mayor menor
// 0.393043 seconds menor mayor
int getMax(int arr[], int n){
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

void countSort(int arr[], int n, int exp){
	int* output = new int[n];
	int i, count[10] = {0};
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	for (i = n - 1; i >= 0; i--){
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
	for (i = 0; i < n; i++)
		arr[i] = output[i];
	delete[] output;
}


void radixsort(int arr[], int n){
	int m = getMax(arr, n);
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}

void runRadix(int array[], int n, const char nombre[]){
	float startTime, endTime;
	startTime = ((float)clock())/CLOCKS_PER_SEC;
	radixsort(array, n);
	endTime = ((float)clock())/CLOCKS_PER_SEC;
	float timeDiff = endTime-startTime;
	cout << "The radix-sort algorithm took approximately " << timeDiff << " seconds to execute." << endl;
	ofstream myfile2 (nombre);
	for(int i = 0; i < 1000000 ; i++){
		if (myfile2.is_open()){
   			myfile2 << array[i] << '\n';
    	}
	}
	myfile2.close();
}
