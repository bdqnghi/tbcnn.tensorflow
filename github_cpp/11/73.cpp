
#include "baseSort.h"
#include "heapSort.h"

#define DEBUG 1

void HeapSort::sort() {
    heapSort();
}

void HeapSort::heapSort() {
    
    buildMaxHeap();

    int i = this->len;
    int tmp;
    while( i > 0 ) {
        tmp = this->Array[0];
        this->Array[0] = this->Array[i-1];
        this->Array[i-1] = tmp;

        i--;
        maxHeapIfy(0, i);
    }
}

void HeapSort::maxHeapIfy( int i, int curlen ) {
    int left, right, largest;
    int tmp;

    left = Left(i);
    right = Right(i);

    if ( left < curlen-1
        && Array[left] > Array[i])
        largest = left;
    else
        largest = i;

    if ( right < curlen-1
        && Array[right] > Array[largest])
        largest = right;

    if ( largest != i ) {
        tmp = Array[i];
        Array[i] = Array[largest];
        Array[largest] = tmp;

        maxHeapIfy(largest, curlen);
    }
}

void HeapSort::buildMaxHeap() {
    int i;
    for ( i = (len-1)/2 ; i >= 0; i-- ) {
        maxHeapIfy(i, len);

        if (DEBUG) {
            printArray(this->Array, this->len, "midResult");
        }
    }
}

int main()
{
    int b[10] = {7,3,2,9,8,5,1,10,4,6};
    int len = 10;
    HeapSort* heapsort = new HeapSort(b, len);
    heapsort->sort();
    printArray(b, len, "HeapSort ");
}
