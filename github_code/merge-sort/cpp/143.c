
#include "common_function.h"



//convert a long integer to string
string itostr(long t)
{
	ostringstream oss;
	oss << t;
	return oss.str();
}




//sort fragment
void merge(void** sortlist, double* sortkey, long p, long q, long r, double* mergeSort_Larray, double* mergeSort_Rarray, void** mergeSort_LorderedList, void** mergeSort_RorderedList)
{
	long n1, n2, i, j, k;

	n1 = q - p + 1;
	n2 = r - q;

	for (i = 1; i <= n1; i++)
	{
		mergeSort_Larray[i] = sortkey[p + i - 1];
		mergeSort_LorderedList[i] = sortlist[p + i - 1];
	}
	for (j = 1; j <= n2; j++)
	{
		mergeSort_Rarray[j] = sortkey[q + j];
		mergeSort_RorderedList[j] = sortlist[q + j];
	}

	mergeSort_Larray[n1 + 1] = MAX_CHR_LENGTH;
	mergeSort_Rarray[n2 + 1] = MAX_CHR_LENGTH;

	i = 1;
	j = 1;

	for (k = p; k <= r; k++)
	{
		if (mergeSort_Larray[i] <= mergeSort_Rarray[j])
		{
			sortkey[k] = mergeSort_Larray[i];
			sortlist[k] = mergeSort_LorderedList[i];

			i++;
		} 
		else
		{
			sortkey[k] = mergeSort_Rarray[j];
			sortlist[k] = mergeSort_RorderedList[j];

			j++;
		}
	}

	return;
}


void mergeSort(void** sortlist, double* sortkey, long sortList_size)
{
	if (sortList_size <= 0)
		return;

	//non-recursive merge sort for sorting junctions
	long m, n, i, r;
	m = 1;
	n = sortList_size;

	double* mergeSort_Larray = new double [sortList_size + 2];
	double* mergeSort_Rarray = new double [sortList_size + 2];
	void** mergeSort_LorderedList = new void* [sortList_size + 2];
	void** mergeSort_RorderedList = new void* [sortList_size + 2];

	while (m <= n)
	{
		i = 1;
		while (i <= n - m)
		{
			r = (i + 2 * m - 1) < n ? (i + 2 * m - 1) : n;
			merge(sortlist, sortkey, i, i + m - 1, r, mergeSort_Larray, mergeSort_Rarray, mergeSort_LorderedList, mergeSort_RorderedList);
			i = i + 2 * m;
		}

		m = m * 2;
	}

	delete [] mergeSort_Larray;
	delete [] mergeSort_Rarray;
	delete [] mergeSort_LorderedList;
	delete [] mergeSort_RorderedList;

	return;
}



long partition(long p,long r, double *sortArray)
{
	long i, j;
	double x, tmp;

	//randomized partition
	i = long(p + (double)rand()/ (RAND_MAX) * (r - p));

	if (sortArray[r] != sortArray[i])
	{
		tmp = sortArray[r];
		sortArray[r] = sortArray[i];
		sortArray[i] = tmp;
	}

	x = sortArray[r];
	i = p - 1;

	for(j = p; j < r; j++)
	{
		if (sortArray[j] <= x)
		{
			i++;

			if (sortArray[i] != sortArray[j])
			{
				tmp = sortArray[j];
				sortArray[j] = sortArray[i];
				sortArray[i] = tmp;
			}
		}
	}

	if (sortArray[r] != sortArray[i+1])
	{
		tmp = sortArray[r];
		sortArray[r] = sortArray[i+1];
		sortArray[i+1]=tmp;
	}

	return i+1;
}


void quicksort(double *sortArray, long length, long *quicksortStack)
{
	long top = 0, p, r, q;

	quicksortStack[top++] = 1;
	quicksortStack[top++] = length;

	while (top != 0)
	{
		r = quicksortStack[--top];
		p = quicksortStack[--top];

		if(p>=r)
			continue;

		q = partition(p, r, sortArray);

		quicksortStack[top++] = p;
		quicksortStack[top++] = q - 1;

		quicksortStack[top++] = q + 1;
		quicksortStack[top++] = r;
	}

	return;
}

//calculate the mean of the data array, index starts from 0
double calculate_mean(double *dataarray, long length)
{
	if (length < 1)
	{
		cout << "array length < 1 in calculate_mean";
		return 0.0;
	}

	double sum = 0.0;
	for (long tmpCnt = 0; tmpCnt < length; ++tmpCnt)
	{
		sum += dataarray[tmpCnt];
	}
	return sum / length;
}
