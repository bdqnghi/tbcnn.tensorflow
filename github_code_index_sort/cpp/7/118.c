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

#ifdef INTEL
__m512i ind_i;
__m512i ind_straight;
__m512i ind_k;
#endif

/// \brief Shell sort.
///
/// \param m - array
/// \param n - array element count
void shell_sort_orig(double *m, int n)
{
    int i, j, k;

    for (k = n / 2; k > 0; k /= 2)
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

#ifdef INTEL

/// \brief Insert from i position for step k in shell sorting.
///
/// \param m - array
/// \param n - array size
/// \param k - step size
/// \param i - insert position
void shell_sort_step_i(double *m, int n, int k, int i)
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
void shell_sort_step_i_mod(double *m, int n, int k, int i)
{
    int j = i;
    double t = m[j];

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

/// \brief Insert from i position for step k in shell sorting (16 repeats).
///
/// \param m - array
/// \param n - array size
/// \param k - step size
/// \param i - insert position
void shell_sort_step_big_i8(double *m, int n, int k, int i)
{
    __m512i ind_j = _mm512_add_epi64(ind_i, ind_straight);
    __m512d t = _mm512_i64gather_pd(ind_j, m, _MM_SCALE_8);
    __mmask8 mask = 0xFF;
    __m512i ind_jk;
    __m512d q;

    do
    {
	mask = mask & _mm512_mask_cmp_epi64_mask(mask, ind_j, ind_k, _MM_CMPINT_GE);

///	if (mask == 0x0)
//	{
///	    break;
//	}

	ind_jk = _mm512_mask_sub_epi64(ind_j, mask, ind_j, ind_k);
	q = _mm512_mask_i64gather_pd(q, mask, ind_jk, m, _MM_SCALE_8);

	mask = mask & _mm512_mask_cmp_pd_mask(mask, t, q, _MM_CMPINT_LT);

//	if (mask == 0x0)
//	{
//	    break;
//	}

	_mm512_mask_i64scatter_pd(m, mask, ind_j, q, _MM_SCALE_8);
	ind_j = _mm512_mask_sub_epi64(ind_j, mask, ind_j, ind_k);
    }
    while (mask != 0x0);

    _mm512_i64scatter_pd(m, ind_j, t, _MM_SCALE_8);
}

/// \brief Shell sort big step.
///
/// \param m - array
/// \param n - array size
/// \param k - step size
void shell_sort_step_big(double *m, int n, int k)
{
    int i = k;

    ind_k = _mm512_set1_epi64(k);

    while (i + 7  < n)
    {
	ind_i = _mm512_set1_epi64(i);
	shell_sort_step_big_i8(m, n, k, i);
	i += 8;
    }

    while (i < n)
    {
	shell_sort_step_i(m, n, k, i);
	i++;
    }
}

/// \brief Shell sort small step.
///
/// \param m - array
/// \param n - array size
/// \param k - step size
void shell_sort_step_small(double *m, int n, int k)
{
    int i;

    for (i = k; i < n; i++)
    {
	shell_sort_step_i(m, n, k, i);
    }
}

#endif

/// \brief Prepare for optimized version of shell sort.
void shell_sort_opt_prepare()
{

#ifdef INTEL

    ind_straight = _mm512_set_epi64(7,  6,  5,  4,  3,  2, 1, 0);

#endif

}

/// \brief Shell sort.
///
/// \param m - array
/// \param n - array element count
void shell_sort_opt(double *m, int n)
{

#ifndef INTEL

    shell_sort_orig(m, n);

#else

    int k;

    for (k = n / 2; k >= 8; k /= 2)
    {
	shell_sort_step_big(m, n, k);
    }

    for(; k > 0; k /= 2)
    {
	shell_sort_step_small(m, n, k);
    }

#endif

}
