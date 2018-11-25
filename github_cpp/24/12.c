

#include <iostream>
#include <conio.h>
#include <ctime>


int binarysearch(int *A,int l, int r, int data){
    if(data<A[l] || data > A[r]){
        return -1;
    }else{
        int mid = (r+l)/2;
        int key = A[mid];
        if(data == key) return mid;
        if(data < key) return binarysearch(A,l,mid,data);
        if(data > key) return binarysearch(A,mid,r,data);
    }
}



void insertionSort(int *A,int l, int r){
    int i,j,key;
    for(i = l;i<=r;i++){
        for(j = l;j<=i;j++){
            if(A[j] > A[i]){
                key = A[i];
                for(int k = i;k>j;k--){
                    A[k] = A[k-1];
                }
                A[j] = key; 
            }
        }
    }
}

int main(){
    int A[100];
    srand(time(NULL));
    for (int i = 0 ; i<10; i++){
        A[i] = rand()%99+1;
    }
    insertionSort(A,0,9);
    for(int i =0; i<10;i++){
        std::cout << A[i] << " ";
    }
    std::cout  << '\n' << "Nhap so can tim : ";
    int n;
    std::cin >> n;
    int m;
    m = binarysearch(A,0,9,n) ;
    if(m != -1){
        std::cout << "ket qua : tim thay " << '\n';
        std::cout << "Index :" << m;
    }
    return 0;
}