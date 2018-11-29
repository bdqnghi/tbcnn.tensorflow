/******************************************************************************
Description: Radix Sort Algorithm. Code adapted from book.

Author     : Arturo Alatriste Trujillo.

reference  : 
	Mastering Algorithms with C
	by Kyle Loudon
	Publisher: O'Reilly Media, Inc.
	Release Date: August 1999
	ISBN: 9781565924536

******************************************************************************/
// radixsort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/*****************************************************************************
*                                                                            *
*  ------------------------------- rxsort.c -------------------------------  *
*                                                                            *
*****************************************************************************/
#include<iostream>
using namespace std;

#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//#include "sort.h"

void print2(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << "\n";
}

/*****************************************************************************
*                                                                            *
*  -------------------------------- rxsort --------------------------------  *
*                                                                            *
*****************************************************************************/

int rxsort(int *data, int size, int p, int k) {

	int                *counts,
		*temp;

	int                index,
		pval,
		i,
		j,
		n;

	/*****************************************************************************
	*                                                                            *
	*  Allocate storage for the counts.                                          *
	*                                                                            *
	*****************************************************************************/

	if ((counts = (int *)malloc(k * sizeof(int))) == NULL)
		return -1;

	/*****************************************************************************
	*                                                                            *
	*  Allocate storage for the sorted elements.                                 *
	*                                                                            *
	*****************************************************************************/

	if ((temp = (int *)malloc(size * sizeof(int))) == NULL)
		return -1;

	/*****************************************************************************
	*                                                                            *
	*  Sort from the least significant position to the most significant.         *
	*                                                                            *
	*****************************************************************************/

	for (n = 0; n < p; n++) {

		cout << "n: " << n << endl;

		/**************************************************************************
		*                                                                         *
		*  Initialize the counts.                                                 *
		*                                                                         *
		**************************************************************************/

		for (i = 0; i < k; i++)
			counts[i] = 0;

		/**************************************************************************
		*                                                                         *
		*  Calculate the position value.                                          *
		*                                                                         *
		**************************************************************************/

		pval = (int)pow((double)k, (double)n);
		cout << "pval: " << pval << endl;

		/**************************************************************************
		*                                                                         *
		*  Count the occurrences of each digit value.                             *
		*                                                                         *
		**************************************************************************/

		for (j = 0; j < size; j++) {

			index = (int)(data[j] / pval) % k;
			counts[index] = counts[index] + 1;

		}

		cout << "counts" << endl;
		print2(counts, 10);

		/**************************************************************************
		*                                                                         *
		*  Adjust each count to reflect the counts before it.                     *
		*                                                                         *
		**************************************************************************/

		for (i = 1; i < k; i++)
			counts[i] = counts[i] + counts[i - 1];

		cout << "adjusted counts" << endl;
		print2(counts, 10);
		/**************************************************************************
		*                                                                         *
		*  Use the counts to position each element where it belongs.              *
		*                                                                         *
		**************************************************************************/

		for (j = size - 1; j >= 0; j--) {

			index = (int)(data[j] / pval) % k;
			temp[counts[index] - 1] = data[j];
			counts[index] = counts[index] - 1;

		}

		cout << "temp" << endl;
		print2(temp, size);
		cout << endl;

		/**************************************************************************
		*                                                                         *
		*  Prepare to pass back the data as sorted thus far.                      *
		*                                                                         *
		**************************************************************************/

		memcpy(data, temp, size * sizeof(int));

	}

	/*****************************************************************************
	*                                                                            *
	*  Free the storage allocated for sorting.                                   *
	*                                                                            *
	*****************************************************************************/

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

