#include <iostream>
#include <cstdio>
using namespace std;

void radixSort(int* arr, int n);
void countingSort(int* arr, int n, int exp);
int maxValueInArray(int* arr, int n);
void printArr(int* arr, int size);

void radixSort(int* arr, int n) {
	int max = maxValueInArray(arr, n);
	for (int exp = 1; max/exp > 0; exp *= 10)
		countingSort(arr, n, exp);
	cout<<endl<<"radix sort: ";
	printArr(arr, n);
}

void countingSort(int* arr, int n, int exp) {
	int output[n], i;
	int count[10] = {0};
	for (i = 0; i < n; i++)
		++count[(arr[i]/exp) % 10];
	for (i = 1; i < 10; i++)
		count[i] = count[i] + count[i-1];
	for (i = n-1; i >= 0; i--) {
		output[count[(arr[i]/exp) % 10]-1] = arr[i];
		--count[(arr[i]/exp) % 10];
	}
	
	// copy contents of output to arr so that they reflect in calling method
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

int maxValueInArray(int* arr, int n) {
	int max = arr[0];
	for (int i = 0; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

void printArr(int* arr, int size) {
	for (int i = 0; i < size; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}

int main()
{
    freopen("input.txt","r",stdin);

	int n;					// n is no of elements in input array
	cin>>n;
	int arr[n];
	for (int i = 0; i < n; i++)
		cin>>arr[i];
	cout<<"original array: ";
	printArr(arr, n);
	radixSort(arr, n);
	cout<<endl;
	return 0;
}