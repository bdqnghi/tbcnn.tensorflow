



#include "stdafx.h"

#include<iostream>
using namespace std;

#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



void print2(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << "\n";
}



int rxsort(int *data, int size, int p, int k) {

	int                *counts,
		*temp;

	int                index,
		pval,
		i,
		j,
		n;

	

	if ((counts = (int *)malloc(k * sizeof(int))) == NULL)
		return -1;

	

	if ((temp = (int *)malloc(size * sizeof(int))) == NULL)
		return -1;

	

	for (n = 0; n < p; n++) {

		cout << "n: " << n << endl;

		

		for (i = 0; i < k; i++)
			counts[i] = 0;

		

		pval = (int)pow((double)k, (double)n);
		cout << "pval: " << pval << endl;

		

		for (j = 0; j < size; j++) {

			index = (int)(data[j] / pval) % k;
			counts[index] = counts[index] + 1;

		}

		cout << "counts" << endl;
		print2(counts, 10);

		

		for (i = 1; i < k; i++)
			counts[i] = counts[i] + counts[i - 1];

		cout << "adjusted counts" << endl;
		print2(counts, 10);
		

		for (j = size - 1; j >= 0; j--) {

			index = (int)(data[j] / pval) % k;
			temp[counts[index] - 1] = data[j];
			counts[index] = counts[index] - 1;

		}

		cout << "temp" << endl;
		print2(temp, size);
		cout << endl;

		

		memcpy(data, temp, size * sizeof(int));

	}

	

	free(counts);
	free(temp);

	return 0;

}


void PressEnterToContinue()
{
	std::cout << "\n Press ENTER to continue... " << flush;
	std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}

int main()
{
	int data[] = { 170, 45, 75, 290, 802, 24, 2, 66, 237, 856 };
	int size   = 10;
	int p      = 3;
	int k      = 10;
	int error  = 0;

	cout << "original data: ";
	print2(data, size);

	error = rxsort(data, size, p, k);

	cout << "sorted   data: ";
	print2(data, size);
    
	PressEnterToContinue();
}

