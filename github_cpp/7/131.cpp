

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
