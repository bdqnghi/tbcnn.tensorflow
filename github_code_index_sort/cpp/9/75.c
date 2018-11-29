/*
 * bubble sort:
 * time O(n^2), in place. excessive swap in every time internal iteration
 *
 * selection sort:
 * time O(n^2), in place
 * improvement on bubble sort by reducing swap to once in each internal iteration.
 * its average efficiency is a little worse than insertionsort
 *
 * insertion sort:
 * in internal iteration, stops till finding its correct postion.
 * improvement on selection sort with copy instead of swap.
 * for linked list sort, it is very efficient.
 *
 * merge sort:
 * divide-and-conquer, and it is not in-place sort, some extra memory is in need
 *
 * */
#include "../include/preliminary.h"


class Solution{

public:
    /*
     * standard implementation of bubble sort
     * */
    void bubbleSort(int *A, int n){
        for(int i = 0; i < n-1; i++){ // range [0, i) is sorted alreadt. move minimum in [i, n) bottom-up to A[i]
            for(int j = n-1; j > i; j--){ // bottom up
                if(A[j-1] > A[j]){  // compare [j] and [j-1], which covers [i]
                    swapInt(A[j-1], A[j]); // move minimum in range [i,n) to [i] one by one like bubble
                }
            }
        }
        return;
    }

    /*
     * standard implementation of selection sort
     * optimize based on bubble sort
     * */
    void selectionSort(int *A, int n){
        for (int i = 0; i < n-1; i++){ // range [0, i) is sorted already, select minimum in [i, n) to set it to A[i]
            int sel = i;
            for(int j = i+1; j < n; j++){
                if(A[j] < A[sel])    sel = j; // compare every elemennt in range (i, n) to A[i] to find minimum in [i,n)
            }

            if(sel != i)    swapInt(A[i], A[sel]); // only swap once mostly for inner interation
        }
        return;
    }

    /*
     * standard implementation of insertion sort
     * */
    void insertionSort(int *A, int n){
        for(int i = 1; i < n; i++){ // range [0, i-1] is sorted already
            int tmp = A[i];
            int j = i-1;
            for(; j >= 0 && A[j] > tmp; j--){ // scan [0, i-1] reversely, compare every element with initial A[i]
                A[j+1] = A[j];  // move A[j] to tail
            }
            A[j+1] = tmp; // above loop breaks if j == -1 or A[j] <= tmp, so [j+1] is the right place to insert tmp
        }
        return;
    }

    /*
     * standard merge sort is in mergesort()
     * */
    void mergeSort(int *A, int n){
        mergesort(A, 0, n-1);
    }

private:
    /*
     * divide-and-conquer
     * */
    void mergesort(int *A, int l, int r){  // range[l, r]
        if(l >= r)    return;

        int q = (l + r) / 2;
        mergesort(A, l, q);
        mergesort(A, q + 1, r);

        merge(A, l, q, r);
    }

    /*
     * range[l..q] and [q+1..r] are sorted already both, merge them to whole sorted
     * */
    void merge(int *A, int l, int q, int r){ // for whole rage [l, r], q split it to [l, q] and [q+1, r]
        int n1 = q - l + 1, n2 = r - q; // valid size of two sub arrays

        int AL[n1 + 1]; // tip: use one more cell allocated in array as sentinel to simplify compare and tail check
        memset(AL, 0, sizeof(AL));
        int AR[n2 + 1];
        memset(AR, 0, sizeof(AR));

        static const int MAXIM = 0xffff; // considered as theory upper bound of any integer to sort

        for(int i = 0; i < n1; i++){ // move A[l..q] which size is n1 to AL[]
            AL[i] = A[i + l];
        }
        AL[n1] = MAXIM;

        for(int i = 0; i < n2; i++){ // move A[q+1..r] which size is n2 to AR[]
            AR[i] = A[i + q + 1];
        }
        AR[n2] = MAXIM; // after the copy, current A[l..r] does not need reset as it will be set in following block

        int i = 0, j = 0, k = l;
        while(k <= r){ // merge two sub arrays and assign back to A[l..r]
            if(AL[i] <= AR[j]){
                A[k++] = AL[i++];
            }else{
                A[k++] = AR[j++];
            }
        }
    }

    void swapInt(int& a, int& b){
        int tmp = a;
        a = b;
        b = tmp;
    }
};
