

#pragma once

#include <thrust/detail/config.h>
#include <thrust/system/omp/detail/tag.h>
#include <thrust/system/detail/generic/binary_search.h>

namespace thrust
{
namespace system
{
namespace omp
{
namespace detail
{


template <typename ForwardIterator, typename T, typename StrictWeakOrdering>
ForwardIterator lower_bound(tag,
                            ForwardIterator begin,
                            ForwardIterator end,
                            const T& value, 
                            StrictWeakOrdering comp)
{
    
    return thrust::system::detail::generic::lower_bound(tag(), begin, end, value, comp);
}


template <typename ForwardIterator, typename T, typename StrictWeakOrdering, typename Backend>
ForwardIterator upper_bound(tag,
                            ForwardIterator begin,
                            ForwardIterator end,
                            const T& value, 
                            StrictWeakOrdering comp)
{
    
    return thrust::system::detail::generic::upper_bound(tag(), begin, end, value, comp);
}


template <typename ForwardIterator, typename T, typename StrictWeakOrdering>
bool binary_search(tag,
                   ForwardIterator begin,
                   ForwardIterator end,
                   const T& value, 
                   StrictWeakOrdering comp)
{
    
    return thrust::system::detail::generic::binary_search(tag(), begin, end, value, comp);
}


} 
} 
} 
} 

