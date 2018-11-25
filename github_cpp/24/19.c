




#pragma once

#include <thrust/system/cpp/detail/execution_policy.h>
#include <thrust/system/detail/internal/scalar/binary_search.h>

namespace thrust
{
namespace system
{
namespace cpp
{
namespace detail
{

template <typename ForwardIterator,
          typename T,
          typename StrictWeakOrdering>
ForwardIterator lower_bound(tag,
                            ForwardIterator first,
                            ForwardIterator last,
                            const T& val,
                            StrictWeakOrdering comp)
{
  return thrust::system::detail::internal::scalar::lower_bound(first, last, val, comp);
}


template <typename ForwardIterator,
          typename T,
          typename StrictWeakOrdering>
ForwardIterator upper_bound(tag,
                            ForwardIterator first,
                            ForwardIterator last,
                            const T& val, 
                            StrictWeakOrdering comp)
{
  return thrust::system::detail::internal::scalar::upper_bound(first, last, val, comp);
}

template <typename ForwardIterator,
          typename T,
          typename StrictWeakOrdering>
bool binary_search(tag,
                   ForwardIterator first,
                   ForwardIterator last,
                   const T& val, 
                   StrictWeakOrdering comp)
{
  return thrust::system::detail::internal::scalar::binary_search(first, last, val, comp);
}

} 
} 
} 
} 

