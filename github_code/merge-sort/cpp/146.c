#include "calc_function.h"

long *quicksortStack;

double* sortKey_ASM;

double* mergeSort_Larray_ASM;
double* mergeSort_Rarray_ASM;
gene* *mergeSort_LorderedList_ASM;
gene* *mergeSort_RorderedList_ASM;



/************************************************************************/
/* Jensen-Shannon Divergence                                            */
/************************************************************************/

// KL divergence method for two numbers
double KL_divergence(double x1, double x2)
{
	double temp;
	if (x1 == 0 || x2 == 0)
		temp = 0.0;
	else
		temp = x1 * log(x1/x2) / log(2.0);

	return temp;
}

// array_P: probability distribution for P, sum should equal to 1
// array_Q:probability distribution for Q, sum should equal to 1
// length is the array length for both array_P and array_Q
double calculate_JSD(double *array_P, double *array_Q, long length)
{
	double temp, M, temp_P, temp_Q, propSUM1 = 0.0, propSUM2 = 0.0;
	long i_Loop;

	//normalization
	for (i_Loop = 1; i_Loop <= length; i_Loop++)
	{
		propSUM1 += array_P[i_Loop];
		propSUM2 += array_Q[i_Loop];
	}
	if (propSUM1 == 0)
		propSUM1 = 1.;
	if (propSUM2 == 0)
		propSUM2 = 1.;
	for (i_Loop = 1; i_Loop <= length; i_Loop++)
	{
		array_P[i_Loop] = array_P[i_Loop] / propSUM1;
		array_Q[i_Loop] = array_Q[i_Loop] / propSUM2;
	}

	temp = 0.0;
	for (i_Loop = 1; i_Loop <= length; i_Loop++)
	{
		M = (array_P[i_Loop]+array_Q[i_Loop])/2;
		temp_P = KL_divergence(array_P[i_Loop], M);
		temp_Q = KL_divergence(array_Q[i_Loop], M);
		temp += (temp_P + temp_Q)/2.;
	}

	if (temp < 1e-16)
	{
		temp = 0.0;
	}

	return temp; 
}

/************************************************************************/
/* Quick sort, index from 1                                             */
/************************************************************************/

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


void quicksort(double *sortArray, long length)
{
	long top = 0, p, r, q;

	quicksortStack = new long [10+length*2];

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

	delete [] quicksortStack;

	return;
}


/************************************************************************/
/* Basic calculations of a data array, index from 1                     */
/************************************************************************/

double calculate_mean(double *dataarray, long length)
{
	if (length < 1)
	{
		cout << "array length < 1 in calculate_mean";
		return 0.0;
	}

	double sum = 0.0;
	for (long tmpCnt = 1; tmpCnt <= length; ++tmpCnt)
	{
		sum += dataarray[tmpCnt];
	}
	return sum / length;
}

void calculate_meanDistribution(double** distributions, double* meanDist, int distNum, int dimension)
{
	int pathLoopCnt, sampleLoopCnt;
	double sum;

	for (pathLoopCnt = 1; pathLoopCnt <= dimension; ++pathLoopCnt)
	{
		sum = 0.0;
		for (sampleLoopCnt = 1; sampleLoopCnt <= distNum; ++sampleLoopCnt)
		{
			sum += distributions[sampleLoopCnt][pathLoopCnt];
		}
		meanDist[pathLoopCnt] = sum / distNum;
	}

	//normalize the proportions 
	sum = 0.0;
	for (pathLoopCnt = 1; pathLoopCnt <= dimension; ++pathLoopCnt)
	{
		sum += meanDist[pathLoopCnt];
	}		
	if (sum == 0.0)
	{
		sum = 1.0;
	}
	for (pathLoopCnt = 1; pathLoopCnt <= dimension; ++pathLoopCnt)
	{
		meanDist[pathLoopCnt] = meanDist[pathLoopCnt] / sum;
	}	

	return;
}

void calculate_group_mean_expr_permutated(double* sample_expr, double* group_mean_expr, int* group_size, int* group_assign, int group_num)
{
	int sampleLoopCnt, groupLoopCnt;
	double sum;

	for (groupLoopCnt = 1; groupLoopCnt <= group_num; ++groupLoopCnt)
	{
		sum = 0.0;
		for (sampleLoopCnt = 1; sampleLoopCnt <= group_size[groupLoopCnt]; ++sampleLoopCnt)
		{
			sum += sample_expr[group_assign[sampleLoopCnt]];
		}
		group_mean_expr[groupLoopCnt] = sum / group_size[groupLoopCnt];
	}

	return;
}

double calculate_percentile(double *dataarray, long length, double percentile_0to1)
{
	double percentileRank, rangeStart, rangeEnd, percentileValue = 0.0;

	if (percentile_0to1 < 0 || percentile_0to1 > 1)
	{
		cout << "ERROR: percentile should be 0 to 1 in calculate_percentile" << endl;
		exit(1);
	}

	percentileRank = percentile_0to1 * (length - 1) + 1;

	rangeStart = dataarray[long(floor(percentileRank))];
	rangeEnd   = dataarray[long(ceil(percentileRank))];

	percentileValue = rangeStart + (percentileRank - floor(percentileRank)) * (rangeEnd - rangeStart);

	return percentileValue;
}

double calculate_SSE(double *dataarray, long length)
{
	double SSE = 0.0, groupmean = calculate_mean(dataarray, length);
	for (long tmpCnt = 1; tmpCnt <= length; ++tmpCnt)
	{
		SSE += pow(dataarray[tmpCnt] - groupmean, 2);
	}
	return SSE;
}

long calculate_factorial(long n)
{
	if (n == 0)
		return 1;
	else
		return n * calculate_factorial(n-1);
}

long choose(long n, long k)
{
	return calculate_factorial(n) / calculate_factorial(k) / calculate_factorial(n-k);
}

long choose_non_recursive(long n, long k)
{
	if (k > n || k < 0)
		return 0;
	if (k > n - k)
		k = n - k;

	double comb = 1;
	for (long tmpLoop = 1; tmpLoop <= k; ++tmpLoop)
	{
		comb *= (n - (k - tmpLoop));
		comb = comb / tmpLoop;
	}

	return long(floor(comb + 0.5));
}

//calculate the median absolute deviation from the median
double calculate_mad(double *dataArray, long arrayLength)
{
	double median = 0.0, *abs_deviation, mad_value;
	abs_deviation = new double [arrayLength+1];

	quicksort(dataArray, arrayLength);
	//median = dataArray[long(ceil(arrayLength/2.))];
	median = calculate_percentile(dataArray, arrayLength, 0.5);

	for (long loopCnt = 1; loopCnt <= arrayLength; ++loopCnt)
	{
		abs_deviation[loopCnt] = fabs(dataArray[loopCnt] - median);
	}

	quicksort(abs_deviation, arrayLength);
	//mad_value = abs_deviation[long(ceil(arrayLength/2.))];
	mad_value = calculate_percentile(abs_deviation, arrayLength, 0.5);

	delete [] abs_deviation;
	return mad_value;
}

//calculate the coefficient variation;
double calculate_coefficient_variation(double *dataArray, long arrayLength)
{
	return sqrt(calculate_SSE(dataArray, arrayLength)/(arrayLength-1)) / fabs(calculate_mean(dataArray, arrayLength));
}


/************************************************************************/
/* Merge sort of the ASM list, index from 1                             */
/************************************************************************/

void merge_ASM_sort(long p, long q, long r)
{
	long n1, n2, i, j, k;

	n1 = q - p + 1;
	n2 = r - q;

	for (i = 1; i <= n1; i++)
	{
		mergeSort_Larray_ASM[i] = sortKey_ASM[p + i - 1];
		mergeSort_LorderedList_ASM[i] = sortList_ASM[p + i - 1];
	}
	for (j = 1; j <= n2; j++)
	{
		mergeSort_Rarray_ASM[j] = sortKey_ASM[q + j];
		mergeSort_RorderedList_ASM[j] = sortList_ASM[q + j];
	}

	mergeSort_Larray_ASM[n1 + 1] = MAX_NUMBER;
	mergeSort_Rarray_ASM[n2 + 1] = MAX_NUMBER;

	i = 1;
	j = 1;

	for (k = p; k <= r; k++)
	{
		if (mergeSort_Larray_ASM[i] <= mergeSort_Rarray_ASM[j])
		{
			sortKey_ASM[k] = mergeSort_Larray_ASM[i];
			sortList_ASM[k] = mergeSort_LorderedList_ASM[i];

			i++;
		} 
		else
		{
			sortKey_ASM[k] = mergeSort_Rarray_ASM[j];
			sortList_ASM[k] = mergeSort_RorderedList_ASM[j];

			j++;
		}
	}

	return;
}


void mergeSort_ASM_sort(long sortList_size)
{
	//non-recursive merge sort for sorting junctions
	long m, n, i, r;
	m = 1;
	n = sortList_size;

	while (m <= n)
	{
		i = 1;
		while (i <= n - m)
		{
			r = (i + 2 * m - 1) < n ? (i + 2 * m - 1) : n;
			merge_ASM_sort(i, i + m - 1, r);
			i = i + 2 * m;
		}

		m = m * 2;
	}

	return;
}

void mergeSort_initialization(long sortList_ASM_Num)
{
	sortKey_ASM = new double [sortList_ASM_Num+1];
	mergeSort_Larray_ASM = new double [sortList_ASM_Num+1];
	mergeSort_Rarray_ASM = new double [sortList_ASM_Num+1];
	mergeSort_LorderedList_ASM = new gene* [sortList_ASM_Num+1];
	mergeSort_RorderedList_ASM = new gene* [sortList_ASM_Num+1];

	return;
}

void mergeSort_cleanup()
{
	delete [] sortKey_ASM;
	delete [] mergeSort_Larray_ASM;
	delete [] mergeSort_Rarray_ASM;
	delete [] mergeSort_LorderedList_ASM;
	delete [] mergeSort_RorderedList_ASM;
	
	return;
}


/************************************************************************/
/* Randomly shuffle an index array, index from 1                        */
/************************************************************************/

class shuffle_card
{
public:
	int entry_index;
	shuffle_card *next;

	shuffle_card(int entry) {entry_index = entry;};
};

void shuffle_index_array(int *index_array, int array_length)
{
	shuffle_card *new_card, *all_cards = NULL, *all_cards_tail = NULL;
	int index_loop, tmp_cnt;

	//create a list (with circle) that contains all the cards
	for (index_loop = 1; index_loop <= array_length; ++index_loop)
	{
		new_card = new shuffle_card(index_array[index_loop]);
		if (!all_cards_tail)
		{
			all_cards = new_card;
			all_cards_tail = new_card;
		} 
		else
		{
			all_cards_tail->next = new_card;
			all_cards_tail = new_card;
		}
	}
	all_cards_tail->next = all_cards;

	//shuffle and save new order
	shuffle_card *cur_card = all_cards, *prev_card = all_cards_tail;

	for (index_loop = 1; index_loop <= array_length; ++index_loop)
	{
		//randomly pick next entry
		tmp_cnt = rand() % (array_length - index_loop + 1);
		while (tmp_cnt > 0)
		{
			cur_card = cur_card->next;
			prev_card = prev_card->next;
			--tmp_cnt;
		}

		//fill in the entry index
		index_array[index_loop] = cur_card->entry_index;

		//remove this card
		if (index_loop < array_length)
		{
			assert(prev_card != cur_card);
			prev_card->next = cur_card->next;
			delete cur_card;
			cur_card = prev_card->next;
		}
		else
		{
			delete cur_card;
		}
	}

	return;
}










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

	mergeSort_Larray[n1 + 1] = MAX_NUMBER;
	mergeSort_Rarray[n2 + 1] = MAX_NUMBER;

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
