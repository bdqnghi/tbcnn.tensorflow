//day 1 �鲢���� 
/*�㷨����2.3 α���� 
MERGE(A, p, q, r)
n1 = q - p + 1
n2 = r - q
let L[1 .. n1+1] and R[1 .. n2+1] be new arrays
for i = 1 to n1
	L[i] = A[p +i-1]
for j = 1 to n2
	R[j] = A[q + j]
L[n1+1] = ��
R[n2+1] = ��
i = 1
j = 1
for k = p to r
	if L[i] <= R[j]
		A[k] = L[i]
		i = i +��
	 else A[k] = R[j]
	 	j = j + 1

MERGE-SORT(A, p, r)
if p < r
	q = [(p+r)/2]
	MERGE-SORT(A, p, q)
	MERGE-SORT(A, q+1, r)
	MERGE(A, p, q, r)	  
*/
#include <iostream>
#include <cstdio>
using namespace std;

void print_arr(int *a, int len)
{
	for(int i = 0; i < len; i++)
	    printf("%d ", a[i]);
	printf("\n");
}

void merge(int *a, int start, int mid, int end)
{
	int i, j, k;
	int n1 = mid - start + 1;
	int n2 = end - mid;
	int *l = new int[n1];
	int *r = new int[n2];
	
	for(i = 0; i < n1; i++)
		l[i] = a[start+i];
	for(i = 0; i < n2; i++)
		r[i] = a[mid+i+1];
	
	i = j = k = 0;
	while(i < n1 && j < n2)
	{
		if(l[i] <= r[j])
			a[start+k] = l[i++];
		else
			a[start+k] = r[j++];
		k++;
	}
	//��ʣ��Ĳ��� 
	if(i == n1)
	{
		for(; j < n2; j++)
		{
			a[start+k] = r[j];
			k++;
		}
	}
	else
	{
		for(; i < n1; i++)
		{
			a[start+k] = l[i];
			k++;
		}
	}
	
	delete []l;
	delete []r;
}

void merge_sort(int *a, int start, int end)
{
	if(start < end)
	{
		int mid = (start + end) / 2;
		merge_sort(a, start, mid);
		merge_sort(a, mid+1, end);
		merge(a, start, mid, end);
	}
}

void merge_sort(int *a, int len)
{
	if(len > 1)
		merge_sort(a, 0, len-1);
}

int main()
{
	int test1[] = {3, 4, 1, 8, 0, -199, 23, 289, 2, 4};
	merge_sort(test1, 10);
	print_arr(test1, 10);
	
	int test2[] = {2, 93, 14, 85, 15, 29, 10, -3, 1, 5, 58, 26, 79};
	merge_sort(test2, 13);
	print_arr(test2, 13);
	 
	return 0;
}

