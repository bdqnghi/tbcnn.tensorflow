
#include <stdint.h>



















void merge(int64_t* A, uint64_t p, uint64_t q, uint64_t r)
{
    uint64_t n1 = q - p + 1;
    uint64_t n2 = r - q;
    int64_t* L = new int64_t[n1 * sizeof(int64_t)];
    int64_t* R = new int64_t[n2 * sizeof(int64_t)];
    for (uint64_t i = 0; i < n1; i++)
    {
        L[i] = A[p + i];
    }
    for (uint64_t j = 0; j < n2; j++)
    {
        R[j] = A[q + j + 1];
    }
    L[n1] = INT64_MAX;
    R[n2] = INT64_MAX;
    uint64_t i = 0;
    uint64_t j = 0;
    for (uint64_t k = p; k < r + 1; k++)
    {
        if (L[i] <= R[j])
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








void merge_sort(int64_t* A, uint64_t p, uint64_t r)
{
    if (p < r)
    {
        uint64_t q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}