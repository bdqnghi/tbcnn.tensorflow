//
// Created by Sherif on 3/27/2017.
//

#ifndef QUICKSORT_QUICKSORT_H
#define QUICKSORT_QUICKSORT_H
#include <cstdlib>
#include <vector>

using namespace std;

void quickSort(vector<int> &arr, int left, int right);          //Quick-Sort from Left~Right. <- Best Performance
void quickSortNoSkip(vector<int> &arr, int left, int right);    //Quick-Sort from Left~Right without skipping.
void quickSortNaive(vector<int> &arr, int left, int right);     //Quick-Sort using Naive Partitioning.

int  partition(vector<int> &arr, int left, int right) ;         //Random Pivot avg of n*log(n).
int  partitionNoSkip(vector<int> &arr, int left, int right) ;   //Random Pivot avg of n*log(n) without skipping.
int  partitionNaive(vector<int> &arr, int left, int right);     //O[n^2] when list is sorted descendingly.


void quickSort(vector<int> &arr, int left, int right)
{
    if (left < right)//if range is > 2
    {
        int pivot = partition(arr, left, right);      //Partition around a Pivot, Returns Pivot's position.
        if(left < pivot -1)
            quickSort(arr, left, pivot - 1);          //Quick-Sort the left-Part  around the pivot.
        if(right > pivot+1 )
            quickSort(arr, pivot + 1, right);         //Quick-Sort the right-Part around the pivot.
    }
    return;
}

int partition(vector<int> &arr, int left, int right)//Random Pivot avg of n*log(n);
{
    int pivotIdx = rand() % (right - left) + left; //pick a random pivot of range(left ~ right-1).
    int pivot = arr[pivotIdx];                     // pivot value;
    int i = left;                                  // Index of smaller elements
    int j = right-1;
    swap(arr[pivotIdx], arr[right]);               //put the pivot at the end.
    while (i <= j){
        while(arr[i] <= pivot && i <= j)
            ++i;
        while(arr[j] >  pivot && i <= j)
            --j;
        if(i < j)
            swap(arr[i],arr[j]);
    }
    swap(arr[i], arr[right]);                      //put pivot element int its position
    return i;                                      //Return pivot position
}

void quickSortNoSkip(vector<int> &arr, int left, int right)
{
    if (left < right)//if range is > 2
    {
        int pivot = partitionNoSkip(arr, left, right);   //Partition around a Pivot, Returns Pivot's position.
        quickSortNoSkip(arr, left, pivot - 1);           //Quick-Sort the left-Part  around the pivot.
        quickSortNoSkip(arr, pivot + 1, right);          //Quick-Sort the right-Part around the pivot.
    }
    return;
}

int partitionNoSkip(vector<int> &arr, int left, int right) //Random Pivot avg of n*log(n);
{
    int pivotIdx = rand()%(right-left) + left; //pick a random pivot of range(left ~ right-1).
    int pivot = arr[pivotIdx];      // pivot value;
    int i = left-1;                 // Index of smaller elements
    swap(arr[pivotIdx],arr[right]); //put the pivot at the end.

    for (int j = left; j < right; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            if(i!=j)
                swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[right]); //put pivot element int its position
    return i+1; //Return pivot position
}




void quickSortNaive(vector<int> &arr, int left, int right)
{
    if (left < right)//if range is > 2
    {
        int pivot = partitionNaive(arr, left, right); //Partition around the rightmost element.
        quickSortNaive(arr, left, pivot - 1);             //Quick-Sort the left-Part  around the pivot.
        quickSortNaive(arr, pivot + 1, right);        //Quick-Sort the right-Part around the pivot.
    }
    return;
}

int partitionNaive(vector<int> &arr, int left, int right) //O[n^2] when list is sorted descendingly.
{
    int pivot = arr[right];    // Pick the right element as the pivot.
    int i = left-1;            // Index of smaller element

    for (int j = left; j < right; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]); //put pivot element int its position
    return i + 1;                     //Return pivot position
}


#endif //QUICKSORT_QUICKSORT_H
