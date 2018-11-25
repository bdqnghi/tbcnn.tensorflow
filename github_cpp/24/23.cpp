

#pragma once

#include <thrust/detail/config.h>
#include <thrust/system/omp/detail/execution_policy.h>
#include <thrust/system/detail/generic/binary_search.h>

namespace thrust
{
namespace system
{
namespace omp
{
namespace detail
{


template <typename DerivedPolicy, typename ForwardIterator, typename T, typename StrictWeakOrdering>
ForwardIterator lower_bound(execution_policy<DerivedPolicy> &exec,
                            ForwardIterator begin,
                            ForwardIterator end,
                            const T& value, 
                            StrictWeakOrdering comp)
{
    
    return thrust::system::detail::generic::lower_bound(exec, begin, end, value, comp);
}


template <typename DerivedPolicy, typename ForwardIterator, typename T, typename StrictWeakOrdering, typename Backend>
ForwardIterator upper_bound(execution_policy<DerivedPolicy> &exec,
                            ForwardIterator begin,
                            ForwardIterator end,
                            const T& value, 
                            StrictWeakOrdering comp)
{
    
    return thrust::system::detail::generic::upper_bound(exec, begin, end, value, comp);
}


template <typename DerivedPolicy, typename ForwardIterator, typename T, typename StrictWeakOrdering>
bool binary_search(execution_policy<DerivedPolicy> &exec,
                   ForwardIterator begin,
                   ForwardIterator end,
                   const T& value, 
                   StrictWeakOrdering comp)
{
    
    return thrust::system::detail::generic::binary_search(exec, begin, end, value, comp);
}


} 
} 
} 
} 

