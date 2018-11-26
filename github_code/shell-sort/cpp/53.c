/// \file
/// \brief Shell sort realization.

#include "shell_sort.h"
#include "../../Utils/Maths.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "avx512debug.h"

#ifdef INTEL
#include <immintrin.h>
#endif

/// \brief Two numbers minimum.
///
/// \param X - the first number
/// \param Y - the second number
///
/// \return
/// Minimum of <c>X</c> and <c>Y</c>.
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#ifdef INTEL
__m512i ind_straight;
__m512i ind_k;
#endif

/// \brief Max ks array size.
#define MAX_KS_SIZE 100

/// \brief Test sequence.
int ks_test[] =
{
    0, 1
};

/// \brief Gaps sequence constructed by dividing on 2.
int ks_half[MAX_KS_SIZE];

/// \brief Hibbard's gaps sequence.
int ks_hibbard[] =
{
    0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767,
    65535, 131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607
};

/// \brief Sedgewick's gaps sequence.
int ks_sedgewick[] =
{
    0, 1, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289,
    64769, 146305, 260609, 587521, 1045505, 2354689, 4188161
};

/// \brief Pratt's gaps sequence.
int ks_pratt[] =
{
    0, 1, 2, 3, 4, 6, 8, 9, 12, 16, 18, 24, 27, 32, 36, 48, 54, 64, 72, 81, 96,
    108, 128, 144, 162, 192, 216, 243, 256, 288, 324, 384, 432, 486, 512, 576,
    648, 729, 768, 864, 972, 1024, 1152, 1296, 1458, 1536, 1728, 1944, 2048,
    2187, 2304, 2592, 2916, 3072, 3454, 3888, 4096, 4374, 4608, 5184, 5832,
    6144, 6561, 6912, 7776, 8192, 8748, 9216, 10368, 11664, 12288, 13122, 13824,
    15552, 16384, 17496, 18432, 19683, 20736, 23328, 24576, 26244, 27648, 31104,
    32768, 34992, 36864, 39366, 41472, 46656, 49152, 52488, 55296, 59049, 62208,
    65536, 69984, 73728, 78732, 82944, 93312, 98304, 104976, 110592, 118098,
    124416, 131072, 139968, 147456, 157464, 165888, 177147, 186624, 196608, 209952,
    221184, 236196, 248832, 262144, 279936, 294912, 314928, 331776, 354294, 373248,
    393216, 419904, 442368, 472392, 497664, 524288, 531441, 559872, 589824, 629856,
    663552, 708588, 746496, 786432, 839808, 884736, 944784, 995328, 1048576,
    1062882, 1119744
};

/// \brief Fibbonacci's gaps sequence.
int ks_fib[] =
{
    0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181,
    6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229,
    832040, 1346269, 2178309, 3524578
};

/// \brief Get ks_test index.
///
/// \param n - array length
///
/// \return
/// Array index to begin.
int ks_test_i(int n)
{
    return 1;
}

/// \brief Get ks_half index.
///
/// \param n - array length
///
/// \return
/// Array index to begin.
int ks_half_i(int n)
{
    int i = MAX_KS_SIZE - 1;
    int k = n / 2;

    do
    {
        ks_half[i] = k;
        k /= 2;
        i--;
    }
    while (k > 0);

    // Write 0.
    ks_half[i] = k;

    return MAX_KS_SIZE - 1;
}

/// \brief Get ks_half index.
///
/// \param n - array length
///
/// \return
/// Array index to begin.
int ks_hibbard_i(int n)
{
    int i = 0;

    while (ks_hibbard[i + 1] <= n)
    {
        i++;
    }

    return i;
}

/// \brief Get ks_half index.
///
/// \param n - array length
///
/// \return
/// Array index to begin.
int ks_sedgewick_i(int n)
{
    int i = 0;

    while (3 * ks_sedgewick[i + 1] <= n)
    {
        i++;
    }

    return i;
}

/// \brief Get ks_half index.
///
/// \param n - array length
///
/// \return
/// Array index to begin.
int ks_pratt_i(int n)
{
    int i = 0;

    while (ks_pratt[i + 1] <= n / 2)
    {
        i++;
    }

    return i;
}

/// \brief Get ks_half index.
///
/// \param n - array length
///
/// \return
/// Array index to begin.
int ks_fib_i(int n)
{
    int i = 0;

    while (ks_fib[i + 1] <= n)
    {
        i++;
    }

    return i;
}

/// \brief Shell sort.
///
/// \param m - array
/// \param n - array element count
/// \param ks - gaps array
/// \param k_ind - index for first gap
void shell_sort_orig(float *m, int n, int *ks, int k_ind)
{
    int i, j, k;

    for (k = ks[k_ind]; k > 0; k = ks[--k_ind])
    {
        for (i = k; i < n; i++)
        {
            float t = m[i];

            for (j = i; j >= k; j -= k)
            {
                if (t < m[j - k])
                {
                    m[j] = m[j - k];
                }
                else
                {
                    break;
                }
            }

            m[j] = t;
        }
    }
}

/// \brief Shell sort with test sequence.
///
/// \param m - array
/// \param n - array size
void shell_sort_test_orig(float *m, int n)
{
    shell_sort_orig(m, n, ks_test, ks_test_i(n));
}

/// \brief Shell sort with ks generates by half division.
///
/// \param m - array
/// \param n - array size
void shell_sort_half_orig(float *m, int n)
{
    shell_sort_orig(m, n, ks_half, ks_half_i(n));
}

/// \brief Shell sort with Hibbard's sequence.
///
/// \param m - array
/// \param n - array size
void shell_sort_hibbard_orig(float *m, int n)
{
    shell_sort_orig(m, n, ks_hibbard, ks_hibbard_i(n));
}

/// \brief Shell sort with Sedgewick's sequence.
///
/// \param m - array
/// \param n - array size
void shell_sort_sedgewick_orig(float *m, int n)
{
    shell_sort_orig(m, n, ks_sedgewick, ks_sedgewick_i(n));
}

/// \brief Shell sort with Pratt's sequence.
///
/// \param m - array
/// \param n - array size
void shell_sort_pratt_orig(float *m, int n)
{
    shell_sort_orig(m, n, ks_pratt, ks_pratt_i(n));
}

/// \brief Shell sort with Fibonacci's sequence.
///
/// \param m - array
/// \param n - array size
void shell_sort_fib_orig(float *m, int n)
{
    shell_sort_orig(m, n, ks_fib, ks_fib_i(n));
}

#ifdef INTEL

/// \brief Insert from i position for step k in shell sorting.
///
/// \param m - array
/// \param n - array size
/// \param k - step size
/// \param i - insert position
void shell_sort_k_i(float *m, int n, int k, int i)
{
    int j;
    float t = m[i];

    for (j = i; j >= k; j -= k)
    {
        if (t < m[j - k])
        {
             m[j] = m[j - k];
        }
        else
        {
            break;
        }
    }

    m[j] = t;
}

/// \brief Insert from i position for step k in shell sorting.
///
/// Version, modified for vectorization.
///
/// \param m - array
/// \param n - array size
/// \param k - step size
/// \param i - insert position
void shell_sort_k_i_mod(float *m, int n, int k, int i)
{
    int j = i;
    float t = m[j];

    do
    {
        bool p1 = (j >= k);

        if (!p1)
        {
            break;
        }

        float q = m[j - k];

        bool p2 = (t < q);

        if (!p2)
        {
            break;
        }

        m[j] = q;
        j -= k;
    }
    while (true);

    m[j] = t;
}

/// \brief Insert from i position for step k in shell sorting (start with given mask).
///
/// \param m - array
/// \param n - array size
/// \param k - step size
/// \param i - insert position
/// \param w - wide
void shell_sort_k_i_w(float *m, int n, int k, int i, int w)
{
    int j = i;
    __mmask16 ini_mask = ((unsigned int)0xFFFF) >> (16 - w);
    __mmask16 mask = ini_mask;
    __m512i ind_j = _mm512_add_epi32(_mm512_set1_epi32(i), ind_straight);
    __m512 t, q;

    t = _mm512_mask_load_ps(t, mask, &m[j]);

    do
    {
        mask = mask & _mm512_mask_cmp_epi32_mask(mask, ind_j, ind_k, _MM_CMPINT_GE);
        q = _mm512_mask_load_ps(q, mask, &m[j - k]);
        mask = mask & _mm512_mask_cmp_ps_mask(mask, t, q, _MM_CMPINT_LT);
        _mm512_mask_store_ps(&m[j], mask, q);
        ind_j = _mm512_mask_sub_epi32(ind_j, mask, ind_j, ind_k);
        j -= k;
    }
    while (mask != 0x0);

    _mm512_mask_i32scatter_ps(m, ini_mask, ind_j, t, _MM_SCALE_4);
}

/// \brief Shell sort step.
///
/// \param m - array
/// \param n - array size
/// \param k - step size
/// \param w - wide
void shell_sort_k(float *m, int n, int k, int w)
{
    int i = k;

    ind_k = _mm512_set1_epi32(k);

    while (i + (w - 1) < n)
    {
        shell_sort_k_i_w(m, n, k, i, w);
        i += w;
    }

    if (i + 1 < n)
    {
        shell_sort_k_i_w(m, n, k, i, n - i);
    }
    else if (i < n)
    {
        shell_sort_k_i(m, n, k, i);
    }
}

/// \brief Shell sort small step.
///
/// \param m - array
/// \param n - array size
void shell_sort_1(float *m, int n)
{
    for (int i = 1; i < n; i++)
    {
        shell_sort_k_i(m, n, 1, i);
    }
}

#endif

/// \brief Prepare for optimized version of shell sort.
void shell_sort_opt_prepare()
{

#ifdef INTEL

    ind_straight = _mm512_set_epi32(15, 14, 13, 12, 11, 10, 9, 8,
                                     7,  6,  5,  4,  3,  2, 1, 0);

#endif

}

/// \brief Shell sort.
///
/// \param m - array
/// \param n - array element count
/// \param ks - gaps array
/// \param k_ind - index for first gap
void shell_sort_opt(float *m, int n, int *ks, int k_ind)
{

#ifndef INTEL

    shell_sort_orig(m, n, ks, k_ind);

#else

    int k;

    for (k = ks[k_ind]; k > 1; k = ks[--k_ind])
    {
        shell_sort_k(m, n, k, MIN(16, k));
    }

    shell_sort_1(m, n);

#endif

}

/// \brief Shell sort with test sequence.
///
/// \param m - array
/// \param n - array size
void shell_sort_test_opt(float *m, int n)
{
    shell_sort_opt(m, n, ks_test, ks_test_i(n));
}

/// \brief Shell sort with ks sequence generated with half division.
///
/// \param m - array
/// \param n - array size
void shell_sort_half_opt(float *m, int n)
{
    shell_sort_opt(m, n, ks_half, ks_half_i(n));
}

/// \brief Shell sort with Hibbard's sequence.
///
/// \param m - array
/// \param n - array size
void shell_sort_hibbard_opt(float *m, int n)
{
    shell_sort_opt(m, n, ks_hibbard, ks_hibbard_i(n));
}

/// \brief Shell sort with Sedgewick's sequence.
///
/// \param m - array
/// \param n - array size
void shell_sort_sedgewick_opt(float *m, int n)
{
    shell_sort_opt(m, n, ks_sedgewick, ks_sedgewick_i(n));
}

/// \brief Shell sort with Pratt's sequence.
///
/// \param m - array
/// \param n - array size
void shell_sort_pratt_opt(float *m, int n)
{
    shell_sort_opt(m, n, ks_pratt, ks_pratt_i(n));
}

/// \brief Shell sort with Fibbonacci's sequence.
///
/// \param m - array
/// \param n - array size
void shell_sort_fib_opt(float *m, int n)
{
    shell_sort_opt(m, n, ks_fib, ks_fib_i(n));
}
