// -*- C++ -*-

/*! 
  \file insertion_sort.h
  \brief Contains the insertion_sort() functions.
*/

#if !defined(__ads_insertion_sort_h__)
#define __ads_insertion_sort_h__

#include "../defs.h"

#include <iterator>

BEGIN_NAMESPACE_ADS

//-----------------------------------------------------------------------------
/*! \defgroup algorithm_insertion_sort Algorithm: Insertion Sort */
// @{

//! Insertion sort.
template<typename RandomAccessIterator>
void
insertion_sort(RandomAccessIterator first, RandomAccessIterator last);

//! Insertion sort with a comparison function.
template<typename RandomAccessIterator, typename Compare>
void
insertion_sort(RandomAccessIterator first, RandomAccessIterator last,
	       Compare comp);

// @}

END_NAMESPACE_ADS

#define __ads_insertion_sort_ipp__
#include "insertion_sort.ipp"
#undef __ads_insertion_sort_ipp__

#endif
