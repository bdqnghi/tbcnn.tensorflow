#include "heapsort.h"

//Este código se le han hecho modificaciones, pero fue extraído de: https://www.geeksforgeeks.org/heap-sort/
//Prototipos

template <class T>
HeapSort<T>::HeapSort(){
    x = 1;
}

template <class T>
void HeapSort<T>::heapsort(T *arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // Si el hijo izquierdo es más grande que la raíz
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Si el hijo derecho es más grande que largest
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // Si largest no es una raíz
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapsort(arr, n, largest);
    }
}


template <class T>
HeapSort<T>::~HeapSort()
{

}
