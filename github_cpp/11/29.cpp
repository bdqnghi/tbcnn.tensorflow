

#include <stdio.h>
#include "profiler.h"
#define MAX_SIZE 10000

Profiler profiler("Tema 3");

int heap_c = 0, heap_a = 0, heap_c_a = 0;
int quick_c = 0, quick_a = 0, quick_c_a = 0;

void swap(int *a, int *b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}

void afiseaza(int *a, int n) {
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int left(int i)
{
	return (2 * i + 1);
}

int right(int i)
{
	return (2 * (i + 1));
}

void reconstituieHeap(int a[], int n, int i)
{
	int maxim;
	int stanga, dreapta;
	stanga = left(i);
	dreapta = right(i);
	maxim = i;
	
	heap_c++;
	heap_c_a++;
	if (stanga < n && a[stanga] > a[i])
	{
		maxim = stanga;
	}
	else
	{
		maxim = i;
	}

	heap_c++;
	heap_c_a++;
	if (dreapta < n && a[dreapta] > a[maxim]) {
		maxim = dreapta;
	}
	if (i != maxim)
	{
		heap_a += 3;
		heap_c_a += 3;
		swap(&a[i], &a[maxim]);
		reconstituieHeap(a, n, maxim);
	}
}

void heapSort(int *a, int n)
{
	int i;
	for (i = n / 2 - 1; i >= 0; i--)
		reconstituieHeap(a, n, i);
	for (i = n - 1; i >= 0; i--)
	{

		heap_a += 3;
		heap_c_a +=3;
		swap(&a[0], &a[i]);
		reconstituieHeap(a, i, 0);
	}
}

int partition (int *a, int p, int r, int n)
{
	int i, j, x;
	x = a[r];
	
	
	quick_a++;
	quick_c_a++;
	i = p - 1;
		for (j = p; j <= r - 1; j++)
		{
			
			
			quick_c++;
			quick_c_a++;
			if (a[j] <= x)
			{
				i++;
				swap(&a[i], &a[j]);
				
				
				quick_a += 3;
				quick_c_a += 3;
			}
		}
		swap(&a[i + 1], &a[r]);
		
		
		quick_a += 3;
		quick_c_a += 3;
		return (i + 1);
}

void quickSort(int *a, int p, int r, int n)
{
	int q;
	if (p < r)
	{
		q = partition(a, p, r, n);
		quickSort(a, p, q - 1, n);
		quickSort(a, q + 1, r, n);
	}
}

int randomizedPartition(int *a, int p, int r, int n)
{
	int i;
	i = rand() % r + p;
	swap(&a[r], &a[i]);
	return partition(a, p, r, n);
}

int randomizedSelect(int *a, int p, int r, int i)
{
	int k, q;
	int n;
	n = sizeof(a) / sizeof(int);
	if (p == r)
	{
		return a[p];
	}
	q = randomizedPartition(a, p, r, n);
	k = q - p + 1;
	if (i == k)
		{
			return a[q];
		}
	else if(i < k)
		{	
		return randomizedSelect(a, p, q - 1, i);
		}
	else
	{
		return randomizedSelect(a, q + 1, r, i - k);
	}
}

void verificareAlgoritm(int n) {
	int v[10] = {1, 7, 2, 8, 3, 9, 1, 10, 8, 29};
	printf("%d\n", randomizedSelect(v, 0, 9, 7));
	quickSort(v, 0, 9, 10);
	printf("%d\n", randomizedSelect(v, 0, 9, 7));
	afiseaza(v, n);
}

void divide(int a, int b, int c, int d)
{
	a /= 5;
	b /= 5;
	c /= 5;
	d /= 5;
}
int main() {
	int i, j;
	int v[MAX_SIZE], v1[MAX_SIZE];
	
	
	for (i = 100; i < 10000; i += 100) {
		FillRandomArray(v, i, 1, 100000, false, 0);
		for (j = 0; j < i; j++)
		{
			v1[j] = v[j];
		}
		quickSort(v, 0, i - 1, i);
		heapSort(v1, i);
		
		profiler.countOperation("HeapSort: Numar de asignari", i, heap_a);
		profiler.countOperation("HeapSort: Numar de comparatii", i, heap_c);
		profiler.countOperation("HeapSort: Numar de asignari si comparatii", i, heap_a + heap_c);
		profiler.countOperation("QuickSort: Numar de asignari", i, quick_a);
		profiler.countOperation("QuickSort: Numar de comparatii", i, quick_c);
		profiler.countOperation("QuickSort: Numar de asignari si comparatii", i, quick_a + quick_c);
	}

	profiler.createGroup("Asignari AVG", "QuickSort: Numar de asignari", "HeapSort: Numar de asignari");
	profiler.createGroup("Comparatii AVG", "QuickSort: Numar de comparatii", "HeapSort: Numar de comparatii");
	profiler.createGroup("Asignari si comparatii AVG", "QuickSort: Numar de asignari si comparatii", "HeapSort: Numar de asignari si comparatii");
	profiler.reset();
	
	heap_a = 0;
	heap_c = 0;
	quick_a = 0;
	quick_c = 0;
	for (i = 100; i < 10000; i += 100) {
		FillRandomArray(v, i, 1, 100000, false, 1);
		for (j = 0; j < i; j++)
		{
			v1[j] = v[j];
		}
		quickSort(v, 0, i - 1, i);
		heapSort(v1, i);
		
		profiler.countOperation("HeapSort: Numar de asignari", i, heap_a);
		profiler.countOperation("HeapSort: Numar de comparatii", i, heap_c);
		profiler.countOperation("HeapSort: Numar de asignari si comparatii", i, heap_a + heap_c);
		profiler.countOperation("QuickSort: Numar de asignari", i, quick_a);
		profiler.countOperation("QuickSort: Numar de comparatii", i, quick_c);
		profiler.countOperation("QuickSort: Numar de asignari si comparatii", i, quick_a + quick_c);
	}

	profiler.createGroup("Asignari BEST", "QuickSort: Numar de asignari", "HeapSort: Numar de asignari");
	profiler.createGroup("Comparatii BEST", "QuickSort: Numar de comparatii", "HeapSort: Numar de comparatii");
	profiler.createGroup("Asignari si comparatii BEST", "QuickSort: Numar de asignari si comparatii", "HeapSort: Numar de asignari si comparatii");
	profiler.reset();

	heap_a = 0;
	heap_c = 0;
	quick_a = 0;
	quick_c = 0;
	for (i = 100; i < 10000; i += 100) {
		FillRandomArray(v, i, 1, 100000, false, 2);
		for (j = 0; j < i; j++)
		{
			v1[j] = v[j];
		}
		quickSort(v, 0, i - 1, i);
		heapSort(v1, i);
		
		profiler.countOperation("HeapSort: Numar de asignari", i, heap_a);
		profiler.countOperation("HeapSort: Numar de comparatii", i, heap_c);
		profiler.countOperation("HeapSort: Numar de asignari si comparatii", i, heap_a + heap_c);
		profiler.countOperation("QuickSort: Numar de asignari", i, quick_a);
		profiler.countOperation("QuickSort: Numar de comparatii", i, quick_c);
		profiler.countOperation("QuickSort: Numar de asignari si comparatii", i, quick_a + quick_c);
	}
	profiler.createGroup("Asignari WORST", "QuickSort: Numar de asignari", "HeapSort: Numar de asignari");
	profiler.createGroup("Comparatii WORST", "QuickSort: Numar de comparatii", "HeapSort: Numar de comparatii");
	profiler.createGroup("Asignari si comparatii WORST", "QuickSort: Numar de asignari si comparatii", "HeapSort: Numar de asignari si comparatii");
	profiler.showReport();


	return 0;


}