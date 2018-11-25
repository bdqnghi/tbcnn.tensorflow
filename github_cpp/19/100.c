



#ifndef QUICKSORT_QUICKSORT_H
#define QUICKSORT_QUICKSORT_H
#include <cstdlib>
#include <vector>

using namespace std;

void quickSort(vector<int> &arr, int left, int right);          
void quickSortNoSkip(vector<int> &arr, int left, int right);    
void quickSortNaive(vector<int> &arr, int left, int right);     

int  partition(vector<int> &arr, int left, int right) ;         
int  partitionNoSkip(vector<int> &arr, int left, int right) ;   
int  partitionNaive(vector<int> &arr, int left, int right);     


void quickSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int pivot = partition(arr, left, right);      
        if(left < pivot -1)
            quickSort(arr, left, pivot - 1);          
        if(right > pivot+1 )
            quickSort(arr, pivot + 1, right);         
    }
    return;
}

int partition(vector<int> &arr, int left, int right)
{
    int pivotIdx = rand() % (right - left) + left; 
    int pivot = arr[pivotIdx];                     
    int i = left;                                  
    int j = right-1;
    swap(arr[pivotIdx], arr[right]);               
    while (i <= j){
        while(arr[i] <= pivot && i <= j)
            ++i;
        while(arr[j] >  pivot && i <= j)
            --j;
        if(i < j)
            swap(arr[i],arr[j]);
    }
    swap(arr[i], arr[right]);                      
    return i;                                      
}

void quickSortNoSkip(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int pivot = partitionNoSkip(arr, left, right);   
        quickSortNoSkip(arr, left, pivot - 1);           
        quickSortNoSkip(arr, pivot + 1, right);          
    }
    return;
}

int partitionNoSkip(vector<int> &arr, int left, int right) 
{
    int pivotIdx = rand()%(right-left) + left; 
    int pivot = arr[pivotIdx];      
    int i = left-1;                 
    swap(arr[pivotIdx],arr[right]); 

    for (int j = left; j < right; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            if(i!=j)
                swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[right]); 
    return i+1; 
}




void quickSortNaive(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int pivot = partitionNaive(arr, left, right); 
        quickSortNaive(arr, left, pivot - 1);             
        quickSortNaive(arr, pivot + 1, right);        
    }
    return;
}

int partitionNaive(vector<int> &arr, int left, int right) 
{
    int pivot = arr[right];    
    int i = left-1;            

    for (int j = left; j < right; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]); 
    return i + 1;                     
}


#endif 
