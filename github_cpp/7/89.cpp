






































#include <iostream>
#include <stdlib.h>

using namespace std;

#define int_max ~(1<<(sizeof(int)*8 - 1)) 


template<size_t SIZE>
void gen_rand_n(int (&A)[SIZE])
{
    srand(5);
    for (int i = 0; i < SIZE; ++i)
    {
        A[i] = rand();
    }
}


template<size_t SIZE>
void merge(int(&A)[SIZE], const int p, const int q, const int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[SIZE] = {0};
    int R[SIZE] = {0};

    for (int i = 0; i < n1; ++i)
    {
        L[i] = A[p+i];
    }
    for (int i = 0; i < n2; ++i)
    {
        R[i] = A[q+1+i];
    }

    L[n1] = int_max;
    R[n2] = int_max;   

    int i = 0;
    int j = 0;

    for (int k = p; k <= r; ++k)
    {
        if (L[i] < R[j])
        {
            A[k] = L[i];
            i++;  
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }
}


template<size_t SIZE>
void merge_sort(int (&A)[SIZE],const int p, const int r)
{
    int q = 0;
    if (p < r)
    {
        q = (p+r)/2;
        merge_sort(A, p, q);
        merge_sort(A, q+1, r);
        merge(A, p, q, r);
    }
}
int main()
{
    const int N(20); 

    int A[N] = {0}; 

    gen_rand_n(A); 

    merge_sort(A, 0, N-1); 

    for (int i = 0; i < N; ++i)
    {
        cout << A[i] << endl;
    }
    return 0;
}