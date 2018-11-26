// 2.3.1 merge.h
#include <stdint.h>
// MERGE(A, p, q, r)
// n1 = q - p + 1
// n2 = r - q
// let L[1..n1 + 1] and R[1..n2 + 1] be new arrays
// for i = 1 to n1
//     L[i] = A[p + i - 1]
// for j = 1 to n2
//     R[j] = A[q + j]
// L[n1 + 1] = INT64_MAX
// R[n2 + 1] = INT64_MAX
// i = 1
// j = 1
// for k = p to r
//     if L[i] <= R[j]
//         A[k] = L[i]
//         i = i + 1
//     else A[k] = R[j]
//         j = j + 1

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

// MERGE-SORT(A, p, r)
// if p < r
//     q = |_(p + r) / 2_|
//     MERGE-SORT(A, p, q)
//     MERGE-SORT(A, q + 1, r)
//     MERGE(A, p, q, r)

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