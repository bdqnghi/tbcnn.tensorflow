/* problem 2-1
 *
 * a) 
 * T(n) = (n / k) * T(k) = (n / k) * theta(k^2) = theta(n * k)
 *
 * b)
 * merge-sort(A, p, r, k)
 *   if p < r
 *     if r - p + 1 <= k
 *       A' = A[p .. r]
 *       insertion-sort(A')
 *     else
 *       q = floor((p + r) / 2)
 *       merge-sort(A, p, q, k)
 *       merge-sort(A, q + 1, r, k)
 *       merge(A, p, q, r)
 *
 * merge(A, p, q, r)
 *   n1 = q - p + 1
 *   n2 = r - q
 *   let L[1 .. n1] and R[1 .. n2] be new arrays
 *   for i = 1 to n1
 *     L[i] = A[p + i - 1]
 *   for j = 1 to n2
 *     R[j] = A[q + i]
 *   i = 1
 *   j = 1
 *   k = p
 *   while k <= r and i != n1 and j != n2
 *     if L[i] <= R[j]
 *       A[k] = L[i]
 *       i = i + 1
 *       k = k + 1
 *     else
 *       A[k] = R[j]
 *       j = j + 1
 *       k = k + 1
 *   if i == n1
 *     while k <= r
 *       A[k] = R[j]
 *       j = j + 1
 *       k = k + 1
 *   else
 *     while k <= r
 *       A[k] = L[i]
 *       i = i + 1
 *       k = k + 1
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

constexpr int ratio = 5;
void insertionSort(int *A, int n);
void mergeSort(int *A, int p, int r, int k);
void merge(int *A, int p, int q, int r);

int main()
{
    size_t n, k;
    std::cout << "enter the size of the array: ";
    std::cin >> n;
    std::cout << "enter the length k of the sublist: ";
    std::cin >> k;
    
    int *arr = new int[n];

    time_t aTime;
    srand(static_cast<unsigned>(time(&aTime)));

    std::cout << "before modified merge sort:\n";
    for(size_t i = 0; i < n; i++) {
	arr[i] = rand() % (n * ratio);
	std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    mergeSort(arr, 0, n - 1, k);

    std::cout << "after modified merge sort:\n";
    for(size_t i = 0; i < n; i++)
	std::cout << arr[i] << " ";
    std::cout << std::endl;
    
    return 0;
}

void insertionSort(int *A, int n)
{
    for(int j = 1; j < n; j++) {
	int key = A[j];
	int i = j - 1;
	while(i >= 0 && A[i] > key) {
	    A[i + 1] = A[i];
	    i--;
	}
	A[i + 1] = key;
    }
}

void mergeSort(int *A, int p, int r, int k)
{
    if(p < r) {
	int n = r - p + 1;
	if(n <= k) {
	    insertionSort(&A[p], n);
	} else {
	    int q = (p + r) / 2;
	    mergeSort(A, p, q, k);
	    mergeSort(A, q + 1, r, k);
	    merge(A, p, q, r);
	}
    }
}

void merge(int *A, int p, int q, int r)
{
    int n1 = q - p + 1, n2 = r - q;
    int *L = new int[n1], *R = new int[n2];
    int i, j, k;
    for(i = 0; i < n1; i++)
	L[i] = A[p + i];
    for(j = 0; j < n2; j++)
	R[j] = A[q + j + 1];
    i = j = 0, k = p;
    while(k <= r && i != n1 && j != n2) {
	if(L[i] <= R[j])
	    A[k++] = L[i++];
	else
	    A[k++] = R[j++];
    }
    if(i == n1)
	while(k <= r)
	    A[k++] = R[j++];
    else
	while(k <= r)
	    A[k++] = L[i++];
    delete [] L;
    delete [] R;
}
