#include<iostream>
#include<stdlib.h>
using namespace std;




void initialiseArray(int arr[], int length)
{
    for(int i=1; i<length; i++)
        arr[i] = rand()%100;
}




void printArray(int arr[], int arrLength)
{
    for(int i=1; i<arrLength; i++)
        cout << arr[i] << " ";
    cout << endl;
}




int leftChildOf(int i)
{
    return 2*i;
}




int rightChildOf(int i)
{
    return 2*i+1;
}


void maxHeapify(int elementAt[], int i, int heapSize)
{
    int largestInd = i;
    int leftInd = leftChildOf(i);
    int rightInd = rightChildOf(i);

    if(leftInd <= heapSize && elementAt[leftInd] > elementAt[largestInd])
        largestInd = leftInd;
    if(rightInd <= heapSize && elementAt[rightInd] > elementAt[largestInd])
        largestInd = rightInd;

    if(largestInd != i)
    {
        swap(elementAt[i], elementAt[largestInd]);
        maxHeapify(elementAt, largestInd, heapSize);
    }
}


void buildMaxHeap(int arr[], int length)
{
    for(int i=length/2; i>0; i--)
    {
        maxHeapify(arr, i, length-1);
    }
}


void heapSort(int arr[], int lengthOfArray)
{
    int heapSize = lengthOfArray-1;

    buildMaxHeap(arr, lengthOfArray);

    for(int i=1; i<lengthOfArray; i++)
    {
        swap(arr[1], arr[heapSize]);
        --heapSize;
        maxHeapify(arr, 1, heapSize);
    }
}


int main()
{
    int N;
    cout << "Enter size of the array: ";
    cin >> N;

    int A[N+1];
    

    initialiseArray(A, N+1);

    cout << "Array before sorting: ";
    printArray(A, N+1);

    heapSort(A, N+1);

    cout << "Array after sorting:  ";
    printArray(A, N+1);

    return 0;
}
