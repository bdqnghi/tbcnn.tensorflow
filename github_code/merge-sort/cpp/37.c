// 算法导论-第二章-2.3
// 合并排序排序
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 合并排序是一张分治法
// 分解：将n个元素分成各含n/2个原始的子序列
// 解决：用合并排序法对两个子序列递归的排序
// 合并：合并两个已经排好序的子序列以得到一个排好序的序列
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 假设A[p..q]和A[q+1,r]都已排好序

// MERGE（A, p, q, r）
//     n1 <- q-p+1
//     n2 <- r-q
//     create arrays L[1..n1+1] and R[1..n2+1]
//     for i <- 1 to n1
//         do L[i] <- A[p+i-1]
//     for j <- 1 to n2
//         do R[i] <- A[q+j]
//     L[n1+1] <- inf
//     R[n2+1] <- inf
//     i <- 1
//     j <- 1
//     for k <- p to r
//         do if L[i] <= R[j]
//             then A[k] <- L[i]
//                 i <- i+1
//             else A[k] <- R[j]
//                 j <- j+1

// MERGE-SORT(A, p, r)
//     if p < r
//         then q <- fix(（p+r）/2)
//           MERGE-SORT(A, p, r)
//           MERGE-SORT(A, q+1, r)
//           MERGE(A, p, q, r)
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 2014. 09. 10
// lichao

#include <iostream>
#include <stdlib.h>

using namespace std;

#define int_max ~(1<<(sizeof(int)*8 - 1)) // 一般为是 2147483647
// #include <stdlib.h>
// 产生随机数组
template<size_t SIZE>
void gen_rand_n(int (&A)[SIZE])
{
    srand(5);
    for (int i = 0; i < SIZE; ++i)
    {
        A[i] = rand();
    }
}

// 合并排序子程序
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

// 合并排序
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
    const int N(20); // 定义数组长度

    int A[N] = {0}; // 定义数组

    gen_rand_n(A); // 产生随机数组

    merge_sort(A, 0, N-1); // 合并排序

    for (int i = 0; i < N; ++i)
    {
        cout << A[i] << endl;
    }
    return 0;
}