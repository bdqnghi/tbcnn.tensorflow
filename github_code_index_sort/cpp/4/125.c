#include <iostream>
#include <stdlib.h>
using namespace std;

#define N 6

int A[N] = {12, 11, 13, 5, 6, 7};


void MAX_HEAPIFY(int A[], int n, int i){
    int esq = 2 * i;
    int dir = 2 * i + 1;
    int maior = i;

    if ( esq <= n && A[esq] > A[maior]) {
        maior = esq;
    }

    if ( dir <= n  &&  A[dir] > A[maior] ) {
        maior = dir;
    }

    if ( maior != i ) {
        swap(A[i], A[maior]);
        MAX_HEAPIFY(A, n, maior);
    }
}

void MAKE_MAX_HEAP(int A[], int n){
    for (int i = (n/2) ; i > 0; i--) {
        MAX_HEAPIFY(A, n, i);
    }
}

void HEAPSORT(int A[], int n){
    MAKE_MAX_HEAP(A, n);

    for ( int tam_heap = n; tam_heap > 1; tam_heap--) {
        swap(A[1], A[tam_heap]);
        MAX_HEAPIFY(A, tam_heap - 1, 1);
    }
}
 
void printVetor(int A[], int n){
     cout << "saida    -> ";
    for (int i=0; i<n; i++)
        cout << A[i] << " ";
    cout << "\n";
    cout << "esperado -> 5 6 7 11 12 13  \n";
}

int main(){
 
    HEAPSORT(A, N);
    printVetor(A, N);
}