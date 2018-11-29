#include "dslib.h"

bool lin_search(int arr[], int value, int num_elems, int* idx) 
{  
    for(int i=0; i<num_elems; i++) {
        if (arr[i] == value) {
           *idx = i;
           return true; 
        }
            
    }

    return false;
}

void swap(int& a, int& b) 
{
    int temp;
    
    temp = a;
    a = b;
    b = temp;
    return;
}



void selection_sort(int test_array[], int num_elems)
{
    int i,j = 0;
    
    for (i = 0; i < num_elems; i++ ) {
        for (j = i; j < num_elems ; j++) {
            if (test_array[j]  <= test_array[i]) {
                swap(test_array[i], test_array[j]);
            }
        }
    }
}


void bubble_sort(int test_array[], int num_elems)
{
    int i,j = 0;
    
    for (i = 0; i < num_elems - 1; i++ ) {
        for (j = 0; j < num_elems-i -1  ; j++) {
            if (test_array[j]  >= test_array[j+1]) {
                swap(test_array[j], test_array[j+1]);
               
            }
      
       }
    }
}


void insertion_sort(int test_array[], int num_elems)
{
    
    int i,j = 0;
    
    for (i = 0; i < num_elems; i++ ) {
        for (j = i; j < num_elems ; j++) {
            if (test_array[j]  <= test_array[i]) {
                swap(test_array[i], test_array[j]);
            }
        }
    }
    
}


static void merge(int a[], int low, int mid, int high)
{
    int b[10000];
    int i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high) {
        if (a[i] <= a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    }
    while (i <= mid)
        b[k++] = a[i++];

    while (j <= high)
        b[k++] = a[j++];

    k--;
    while (k >= 0) {
        a[low + k] = b[k];
        k--;
    }
}

static void partition(int a[], int pivot, int left, int right)
{
    int i = left;
    int j = right;

    while(i<=j) {
        while (a[i] < a[pivot]) {
            i++;
        }
        while (a[j] > a[pivot]) {
            j--;
        }
        if (i <= j) {
            swap(a[i] , a[j]);
            i++;
            j--;
        }
    }
}

void quick_sort(int a[], int left, int right)
{
    int pivot = (right + left)/2;
    if (left < right) {
        partition(a,pivot,left, right);
        quick_sort(a, left, pivot );
        quick_sort(a,pivot+1, right);
    }
}



void merge_sort(int a[], int low, int high)
{
    if (low < high) {
        int mid = (high + low)/2;
        merge_sort(a, low, mid);
        merge_sort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}




bool bin_search(int arr[], int value, int num_elems, int* idx)
{
 
    int mid = 0;
    int lo  = 0;
    int hi = num_elems - 1;
    
    quick_sort(arr, 0, hi);
    
    while (lo <= hi) {
        mid =(lo + hi)/2 ;
        cout << "lo :" <<lo<<"  Mid  " <<mid <<"  hi  :"<<hi<<endl;   
        if (arr[mid] == value) {
                *idx = mid;
                return true;
            } else if (arr[mid] > value) {
                hi = mid -1;
            } else if (arr[mid] < value) {
               lo = mid +1;         
        }     
    }    
      
   return false;    
}


/* Recursion call stack

[************************]merge_sort
[************]merge_sort(lo,mid)
[******]merge_sort(lo,mid)
[***]merge_sort(lo,mid)
[**]merge_sort(lo,mid)
 [**]merge_sort(mid+1,hi)
[***]merge
   [***]merge_sort(mid+1,hi)
   [**]merge_sort(lo,mid)
    [**]merge_sort(mid+1,hi)
   [***]merge
[******]merge
      [******]merge_sort(mid+1,hi)
      [***]merge_sort(lo,mid)
      [**]merge_sort(lo,mid)
       [**]merge_sort(mid+1,hi)
      [***]merge
         [***]merge_sort(mid+1,hi)
         [**]merge_sort(lo,mid)
           [**]merge_sort(mid+1,hi)
         [***]merge
      [******]merge
[************]merge
            [************]merge_sort(mid+1,hi)
            [******]merge_sort(lo,mid)
            [***]merge_sort(lo,mid)
            [**]merge_sort(lo,mid)
             [**]merge_sort(mid+1,hi)
            [***]merge
               [***]merge_sort(mid+1,hi)
               [**]merge_sort(lo,mid)
                 [**]merge_sort(mid+1,hi)
               [***]merge
            [******]merge
                  [******]merge_sort(mid+1,hi)
                  [***]merge_sort(lo,mid)
                  [**]merge_sort(lo,mid)
                    [**]merge_sort(mid+1,hi)
                  [***]merge
                     [***]merge_sort(mid+1,hi)
                     [**]merge_sort(lo,mid)
                      [**]merge_sort(mid+1,hi)
                     [***]merge
                  [******]merge
            [************]merge
[************************]merge

*/
