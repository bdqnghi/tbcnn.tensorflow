/* 2.3-2
 *
 * merge(A, p, q, r)
 *   n1 = q - p + 1
 *   n2 = r - q
 *   let L[1 .. n1] and R[1 .. n2] be new arrays
 *   for i = 1 to n1
 *     L[i] = A[p + i - 1]
 *   for j = 1 to n2
 *     R[j] = A[q + j]
 *   i = 1
 *   j = 1
 *   for k = p to r
 *     if i > n1
 *       A[k] = R[j]
 *       j = j + 1
 *     else-if j > n2
 *       A[k] = L[i]
 *       i = i + 1
 *     else-if L[i] <= R[j]
 *       A[k] = L[i]
 *       i = i + 1
 *     else
 *       A[k] = R[j]
 *       j = j + 1
 *
 * merge-sort(A, p, r)
 *   if p < r
 *     q = floor((p + r) / 2)
 *     merge-sort(A, p, q)
 *     merge-sort(A, q + 1, r)
 *     merge(A, p, q, r)
 *
 * loop invariant: 
 *   at the start of each for loop in line 13-25,
 *   the subarray A[p .. k - 1] have the k - p smallest
 *   elements in L[1 .. n1] and R[1 .. n2], in sorted 
 *   order; L[i] and R[j] are the smallest elements of 
 *   their array that have not been copied back to A
 *
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

constexpr int ratio = 5;

void mergeSort(int *A, int p, int r);
void merge(int *A, int p, int q, int r);

int main()
{
    int n;
    std::cout << "enter the size of the array: ";
    std::cin >> n;

    int *arr = new int[n];

    time_t aTime;
    srand(static_cast<unsigned>(time(&aTime)));
    
    std::cout << "before merge sort:\n";
    for(int i = 0; i < n; i++) {
	arr[i] = rand() % (n * ratio);
	std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    mergeSort(arr, 0, n - 1);
    
    std::cout << "after merge sort:\n";
    for(int i = 0; i < n; i++)
	std::cout << arr[i] << " ";
    std::cout << std::endl;
    
    delete [] arr;
    
    return 0;
}

void mergeSort(int *A, int p, int r)
{
    if(p < r) {
	int q = (p + r) / 2;
	mergeSort(A, p, q);
	mergeSort(A, q + 1, r);
	merge(A, p, q, r);
    }
}

void merge(int *A, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int *L = new int[n1];
    int *R = new int[n2];
    int i, j, k;
    for(i = 0; i < n1; i++)
	L[i] = A[p + i];
    for(j = 0; j < n2; j++)
	R[j] = A[q + j + 1];
    i = j = 0;
    for(k = p; k <= r; k++) {
	if(j >= n2)
	    A[k] = L[i++];
	else if(i >= n1)
	    A[k] = R[j++];
	else if(L[i] <= R[j])
	    A[k] = L[i++];
	else
	    A[k] = R[j++];
    }
    delete [] L;
    delete [] R;
}
