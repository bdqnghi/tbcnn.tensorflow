#include "heapsort.h"




template <class T>
HeapSort<T>::HeapSort(){
    x = 1;
}

template <class T>
void HeapSort<T>::heapsort(T *arr, int n, int i)
{
    int largest = i; 
    int l = 2*i + 1; 
    int r = 2*i + 2; 

    
    if (l < n && arr[l] > arr[largest])
        largest = l;

    
    if (r < n && arr[r] > arr[largest])
        largest = r;

    
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        
        heapsort(arr, n, largest);
    }
}


template <class T>
HeapSort<T>::~HeapSort()
{

}
