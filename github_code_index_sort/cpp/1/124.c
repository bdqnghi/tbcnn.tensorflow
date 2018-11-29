/* 2.3-4
 *
 * insertion-sort(A, n)
 *   if n > 1
 *     insertion-sort(A, n - 1)
 *   key = A[n]
 *   i = n - 1
 *   while i > 0 and A[i] > key
 *     A[i + 1] = A[i]
 *     i = i - 1
 *   A[i + 1] = key
 *
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

constexpr int ratio = 5;

void insertionSort(int *A, int n);

int main()
{
    int n;
    std::cout << "enter the size of the array: ";
    std::cin >> n;

    int *arr = new int[n];

    time_t aTime;
    srand(static_cast<unsigned>(time(&aTime)));

    std::cout << "before insertion sort:\n";
    for(int i = 0; i < n; i++) {
	arr[i] = rand() % (n * ratio);
	std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    insertionSort(arr, n);
    
    std::cout << "after insertion sort:\n";
    for(int i = 0; i < n; i++)
	std::cout << arr[i] << " ";
    std::cout << std::endl;
    
    delete [] arr;
    
    return 0;
}

void insertionSort(int *A, int n)
{
    if(n > 1)
	insertionSort(A, n - 1);
    int key = A[n - 1];
    int i = n - 2;
    while(i >= 0 && A[i] > key) {
	A[i + 1] = A[i];
	i--;
    }
    A[i + 1] = key;
}
