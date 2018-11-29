/* merge(A, p, q, r)
 *   n1 = q - p + 1
 *   n2 = r - q
 *   let L[1 .. n1 + 1] and R[1 .. n2 + 1] be new arrays
 *   for i = 1 to n1
 *     L[i] = A[p + i - 1]
 *   for j = 1 to n2
 *     R[j] = A[q + i]
 *   L[n1 + 1] = inf
 *   R[n2 + 1] = inf
 *   i = 1
 *   j = 1
 *   for k = p to r
 *     if L[i] <= R[j]
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
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

constexpr int MAX_INT = ~(1 << 31); // 4 bytes integer

void mergeSort(int *A, int p, int r);

void merge(int *A, int p, int q, int r);

int main()
{
    int n;
    std::cout << "enter the size of the array A: ";
    std::cin >> n;

    int *arr = new int[n];

    time_t aTime;
    srand(static_cast<unsigned>(time(&aTime)));
    
    std::cout << "before merge sort:\n";
    constexpr int ratio = 5;
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
    int *L = new int[n1 + 1];
    int *R = new int[n2 + 1];
    int i, j, k;
    for(i = 0; i < n1; i++)
	L[i] = A[p + i];
    for(j = 0; j < n2; j++)
	R[j] = A[q + j + 1];
    L[n1] = R[n2] = MAX_INT;
    i = j = 0;
    for(k = p; k <= r; k++)
	if(L[i] <= R[j])
	    A[k] = L[i++];
	else
	    A[k] = R[j++];
    delete [] L;
    delete [] R;
}
