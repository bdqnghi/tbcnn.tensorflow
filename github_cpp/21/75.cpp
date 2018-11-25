
#include "../include/preliminary.h"


class Solution{

public:
    
    void bubbleSort(int *A, int n){
        for(int i = 0; i < n-1; i++){ 
            for(int j = n-1; j > i; j--){ 
                if(A[j-1] > A[j]){  
                    swapInt(A[j-1], A[j]); 
                }
            }
        }
        return;
    }

    
    void selectionSort(int *A, int n){
        for (int i = 0; i < n-1; i++){ 
            int sel = i;
            for(int j = i+1; j < n; j++){
                if(A[j] < A[sel])    sel = j; 
            }

            if(sel != i)    swapInt(A[i], A[sel]); 
        }
        return;
    }

    
    void insertionSort(int *A, int n){
        for(int i = 1; i < n; i++){ 
            int tmp = A[i];
            int j = i-1;
            for(; j >= 0 && A[j] > tmp; j--){ 
                A[j+1] = A[j];  
            }
            A[j+1] = tmp; 
        }
        return;
    }

    
    void mergeSort(int *A, int n){
        mergesort(A, 0, n-1);
    }

private:
    
    void mergesort(int *A, int l, int r){  
        if(l >= r)    return;

        int q = (l + r) / 2;
        mergesort(A, l, q);
        mergesort(A, q + 1, r);

        merge(A, l, q, r);
    }

    
    void merge(int *A, int l, int q, int r){ 
        int n1 = q - l + 1, n2 = r - q; 

        int AL[n1 + 1]; 
        memset(AL, 0, sizeof(AL));
        int AR[n2 + 1];
        memset(AR, 0, sizeof(AR));

        static const int MAXIM = 0xffff; 

        for(int i = 0; i < n1; i++){ 
            AL[i] = A[i + l];
        }
        AL[n1] = MAXIM;

        for(int i = 0; i < n2; i++){ 
            AR[i] = A[i + q + 1];
        }
        AR[n2] = MAXIM; 

        int i = 0, j = 0, k = l;
        while(k <= r){ 
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
