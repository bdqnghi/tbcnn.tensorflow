//Justin Seda
//CPSC 250 10am
//jseda1@live.esu.edu
//19 March 2017
//This program will demonstrate insertion sort, merge sort, quick sort and a quick sort where the pivot is the first item in the array. It will then count the number of comparisons made in each sort and the running time 
//of each sort.
#include <iostream>    
#include <time.h>
#include<math.h>
using namespace std;

void insertSort(int[], int); //puts array in order by insertion sort
void mergeSort(int[], int, int); //puts array in order by merge sort 
void merge(int[], int, int, int); //second part of the merge sort 
void display(int[], int); //displays the array 
int partition(int[], int, int); //a part of the quick sort 
void sortFCE(int[], int, int, int);// a part of the quick sort. First, Middle, last 
void quickSort(int[], int, int); //puts array in order by quick sort
void QSInsertSort(int[], int, int); //a part of the quick sort
void RQuickSort(int[], int, int);//Revises the quickSort function, now the first item in the array is the pivot
int Rpartition(int[], int, int);

//the counters for each sort 
double count1 = 0;//insertSort
double count2 = 0;//MergeSort
double count3 = 0;//quickSort
double count4 = 0;//RQuickSort

const int SIZE = 8; //the size of the array 
const int MIN = 3;

int main()
{
	clock_t start, stop;
	srand(time(NULL));

	//differecne array for each sort 
	int * ar = new int[SIZE];//insertSort
	int * ar2= new int[SIZE];//MergeSort
	int * ar3 = new int[SIZE];//quickSort
	int * ar4 = new int[SIZE];//RQuickSort

	for (int i = 0; i < SIZE; i++) //outputs the array with random numbers 
	{
		ar[i] = 1 + rand() % 100;
		ar2[i] = 1 + rand() % 100;
		ar3[i] = 1 + rand() % 100;
		ar4[i] = 1 + rand() % 100;
	}

	//InsertSort
	cout << "InsertionSort" << endl; 
	cout << "The array: " << endl; //displays a array 
	display(ar, SIZE);

	//used to find the running time of the method
	start = clock();
	insertSort(ar, SIZE);
	stop = clock();

	cout <<endl<< endl << "The result of the insertionSort is: " << endl;
	display(ar, SIZE); //displays the insertSort array 
	 cout << endl << "Running time for insertionSort is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl; //outputs running time
	 cout << "The count result is " << count1 << endl << endl; //outputs counter

	//MergeSort
	int first = 0;
	int end = SIZE - 1;

	cout << endl << "MergeSort" << endl;
	cout  << "The array: " << endl; //displays a array 
	display(ar2, SIZE);

	start = clock();
	mergeSort(ar2, first, end);
	stop = clock();

	cout << endl << endl << "The result of the MergeSort is: " << endl;
	display(ar2, SIZE);//displays the MergeSort array 
	cout << endl << "Running time for MergeSort is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl;//outputs running time
	cout << "The count result is " << count2 << endl << endl;//outputs counter
	
	//Original QuickSort
	cout << endl << "Original QuickSort" << endl;
	cout << "The array: " << endl;//displays a array 
	display(ar3, SIZE);

	start = clock();
	quickSort(ar3, first, end);
	stop = clock();

	cout << endl << endl << "The result of the Original QuickSort is: " << endl;
	display(ar3, SIZE);//displays the QuickSort array 
	cout << endl << "Running time for Original QuickSort is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl;//outputs running time
	cout << "The count result is " << count3 << endl << endl;//outputs counter

	//Revises QuickSort
	cout << endl << "Revises QuickSort" << endl;
	cout << "The array: " << endl;//displays a array 
	display(ar4, SIZE);

	start = clock();
	RQuickSort(ar4, first, end);
	stop = clock();

	cout << endl << endl << "The result of the Revises QuickSort is: " << endl;
	display(ar4, SIZE);//displays the RQuickSort array 
	cout << endl << "Running time for Revises QuickSort is " << static_cast<double>(stop - start) / (CLOCKS_PER_SEC) << endl;//outputs running time
	cout << "The count result is " << count4 << endl << endl;//outputs counter

	system("pause");
	return 0;
}


//Displays the array
void display(int arr[], int n)
{
	for (int j = 0; j < n; j++)
	{
		cout << arr[j] << ", ";
	}
}


//Insertion Sort - puts array in order by insertion sort
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


//Merge Sort - puts array in order by merge sort 
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

//merge - second part of the merge sort 
void merge(int arr[], int first, int center, int end)
{
	int tempA[SIZE];

	//the array is split
	int f1 = first; //1st subarray's beginning 
	int l1 = center; //1st subarray's end

	int f2 = center + 1; //2nd subarray's beginning 
	int l2 = end;//2nd subarray's end

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


//QuickSort - puts array in order by quick sort
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

//QSInsertSort a part of the quick sort
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


//partition - a part of thr quick sort
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

//sortFCE- a part of the quick sort. First, Middle, last 
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


//Revises QuickSort - revises the quickSort function, now the first item in the array is the pivot
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

//Rpartition - a part of RQuickSort
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

