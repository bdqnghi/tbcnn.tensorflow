





#include <iostream>    
#include <time.h>
#include<math.h>
using namespace std;

void insertSort(int[], int); 
void mergeSort(int[], int, int); 
void merge(int[], int, int, int); 
void display(int[], int); 
int partition(int[], int, int); 
void sortFCE(int[], int, int, int);
void quickSort(int[], int, int); 
void QSInsertSort(int[], int, int); 
void RQuickSort(int[], int, int);
int Rpartition(int[], int, int);


double count1 = 0;
double count2 = 0;
double count3 = 0;
double count4 = 0;

const int SIZE = 8; 
const int MIN = 3;

int main()
{
	clock_t start, stop;
	srand(time(NULL));

	
	int * ar = new int[SIZE];
	int * ar2= new int[SIZE];
	int * ar3 = new int[SIZE];
	int * ar4 = new int[SIZE];

	for (int i = 0; i < SIZE; i++) 
	{
		ar[i] = 1 + rand() % 100;
		ar2[i] = 1 + rand() % 100;
		ar3[i] = 1 + rand() % 100;
		ar4[i] = 1 + rand() % 100;
	}

	
	cout << "InsertionSort" << endl; 
	cout << "The array: " << endl; 
	display(ar, SIZE);

	
	start = clock();
	insertSort(ar, SIZE);
	stop = clock();

	cout <<endl<< endl << "The result of the insertionSort is: " << endl;
	display(ar, SIZE); 
	 cout << endl << "Running time for insertionSort is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl; 
	 cout << "The count result is " << count1 << endl << endl; 

	
	int first = 0;
	int end = SIZE - 1;

	cout << endl << "MergeSort" << endl;
	cout  << "The array: " << endl; 
	display(ar2, SIZE);

	start = clock();
	mergeSort(ar2, first, end);
	stop = clock();

	cout << endl << endl << "The result of the MergeSort is: " << endl;
	display(ar2, SIZE);
	cout << endl << "Running time for MergeSort is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl;
	cout << "The count result is " << count2 << endl << endl;
	
	
	cout << endl << "Original QuickSort" << endl;
	cout << "The array: " << endl;
	display(ar3, SIZE);

	start = clock();
	quickSort(ar3, first, end);
	stop = clock();

	cout << endl << endl << "The result of the Original QuickSort is: " << endl;
	display(ar3, SIZE);
	cout << endl << "Running time for Original QuickSort is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl;
	cout << "The count result is " << count3 << endl << endl;

	
	cout << endl << "Revises QuickSort" << endl;
	cout << "The array: " << endl;
	display(ar4, SIZE);

	start = clock();
	RQuickSort(ar4, first, end);
	stop = clock();

	cout << endl << endl << "The result of the Revises QuickSort is: " << endl;
	display(ar4, SIZE);
	cout << endl << "Running time for Revises QuickSort is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl;
	cout << "The count result is " << count4 << endl << endl;

	system("pause");
	return 0;
}



void display(int arr[], int n)
{
	for (int j = 0; j < n; j++)
	{
		cout << arr[j] << ", ";
	}
}



void insertSort(int arr[], int n) 
{
	for (int i = 1; i < n; i++)
	{
		int next = arr[i];
		int location = i;

		while ((location > 0) && (arr[location - 1] > next))
		{
			arr[location] = arr[location - 1];
			location--;
		}
		count1++;
		arr[location] = next;
	}
	return;
}



void mergeSort(int arr[], int first, int end)
{
	if (first < end)
	{
		int center = first + (end - first) / 2;
		mergeSort(arr, first, center);
		mergeSort(arr, center + 1, end);
		merge(arr, first, center, end);
	}
			
}


void merge(int arr[], int first, int center, int end)
{
	int tempA[SIZE];

	
	int f1 = first; 
	int l1 = center; 

	int f2 = center + 1; 
	int l2 = end;

	int i = f1;

	while ((f1 <= l1) && (f2 <= l2))
	{
		if (arr[f1] <= arr[f2])
		{
			tempA[i] = arr[f1];
			f1++;
		}
		else
		{
			tempA[i] = arr[f2];
			f2++;
		}
		i++;
	}
	while (f1 <= l1)
	{
		tempA[i] = arr[f1];
		f1++;
		i++;
	}

	while (f2 <= l2)
	{
		tempA[i] = arr[f2];
		f2++;
		i++;
	}
	count2++;
	for (i = first; i <= end; i++)
	{
		arr[i] = tempA[i];
	}
}



void quickSort(int arr[], int first, int end)
{
	if ((end - first + 1) < MIN)
	{
		QSInsertSort(arr, first, end);
	}
	else
	{
		int pivotI = partition(arr, first, end);

		quickSort(arr, first, pivotI - 1);
		quickSort(arr, pivotI + 1, end);
	}
	return;
}


void QSInsertSort(int arr[], int first, int end)
{
	int n = end + 1;
	for (int i = 1; i < n; i++)
	{
		int next = arr[i];
		int loc = i;
		while ((loc > 0) && (arr[loc - 1] > next))
		{
			arr[loc] = arr[loc - 1];
			loc--;
		}
		arr[loc] = next;
	}

	return;
}



int partition(int arr[], int first, int end)
{
	int center = first + (end - first) / 2;
	sortFCE(arr, first, center, end);

	int temp = arr[center];
	arr[center] = arr[end - 1];
	arr[end - 1] = temp;

	int pI = end - 1;
	int pivot = arr[pI];

	int leftIndex = first + 1;
	int rightIndex = end - 2;

	bool done = false;
	while (!done)
	{
		while (arr[leftIndex] < pivot)
		{
			leftIndex = leftIndex + 1;
			count3++;
		}
		while (arr[rightIndex] > pivot)
		{
			rightIndex = rightIndex - 1;
			count3++;
		}
		if (leftIndex < rightIndex)
		{
			int temp2 = arr[leftIndex];
			arr[leftIndex] = arr[rightIndex];
			arr[rightIndex] = temp2;

			leftIndex = leftIndex + 1;

			rightIndex = rightIndex - 1;
		}
		else
		{
			done = true;
		}
	}

	int temp3 = arr[pI];
	arr[pI] = arr[leftIndex];
	arr[leftIndex] = temp3;

	pI = leftIndex;
	return pI;
}


void sortFCE(int arr[], int first, int center, int end)
{
	if (arr[first] > arr[center])
	{
		int temp = arr[first];
		arr[first] = arr[center];
		arr[center] = temp;
	}
	if (arr[center] > arr[end])
	{
		int temp2 = arr[center];
		arr[center] = arr[end];
		arr[end] = temp2;
	}
	if (arr[first] > arr[center])
	{
		int temp3 = arr[first];
		arr[first] = arr[center];
		arr[center] = temp3;
	}
}



void RQuickSort(int arr[], int first, int end)
{
	if ((end - first + 1) < MIN)
	{
		QSInsertSort(arr, first, end);
	}
	else
	{
		int pivotI = Rpartition(arr, first, end);
		RQuickSort(arr, first, pivotI - 1);
		RQuickSort(arr, pivotI + 1, end);
	}
	return;
}


int Rpartition(int arr[], int first, int end)
{
	int pI = first;
	int pivot = arr[pI];

	int temp = arr[pI];
	arr[first] = arr[end];
	arr[end] = temp;

	int leftIndex = first;
	int rightIndex = end - 1;

	bool done = false;
	while (!done)
	{
		while (arr[leftIndex] < pivot)
		{
			leftIndex = leftIndex + 1;
			count4++;
		}


		while (arr[rightIndex] > pivot)
		{
			rightIndex = rightIndex - 1;
			count4++;
		}

		if (leftIndex < rightIndex)
		{
			int temp2 = arr[leftIndex];
			arr[leftIndex] = arr[rightIndex];
			arr[rightIndex] = temp2;

			leftIndex = leftIndex + 1;
			rightIndex = rightIndex - 1;
		}
		else
		{
			done = true;
		}
	}

	int temp3 = arr[pI];
	arr[pI] = arr[leftIndex];
	arr[leftIndex] = temp3;

	pI = leftIndex;
	return pI;
}

