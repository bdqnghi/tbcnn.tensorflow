#include<iostream>
using namespace std;

#define SIZE 7

void print(int *list, int n)
{
	cout << "list : ";
	for (int i = 0; i < n; i++)
		cout << list[i] << " ";
	cout << endl;
}

void swap(int *list, int i, int j)
{
	int temp = list[i];
	list[i] = list[j];
	list[j] = temp;
}

void bubbleSort(int *list, int n)
{
	int i = 0;
	bool swapFlag=false;
	// exit this loop if the list is sorted
	// meaning do a pass which does not require any swap
	while (!swapFlag)
	{
		// set swapFlag true in the begining of a new pass
		swapFlag = true;
		for (i = 0; i < n - 1; i++)
		{
			if (list[i] > list[i + 1])
			{
				swap(list, i, i + 1);
				swapFlag = false;
			}
		}
	}
}

int main()
{
	int list[] = { 38, 27, 43, 3, 9, 82, 10 };

	print(list, SIZE);
	bubbleSort(list, SIZE);
	print(list, SIZE);

	getchar();
	return 1;
}