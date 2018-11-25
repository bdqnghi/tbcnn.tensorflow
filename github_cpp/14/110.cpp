

#pragma once

namespace thrust
{
namespace detail
{
namespace backend
{
namespace cpp
{
namespace detail
{

template<typename RandomAccessIterator>
void stable_radix_sort(RandomAccessIterator begin,
                       RandomAccessIterator end);

template<typename RandomAccessIterator1,
         typename RandomAccessIterator2>
void stable_radix_sort_by_key(RandomAccessIterator1 keys_begin,
                              RandomAccessIterator1 keys_end,
                              RandomAccessIterator2 values_begin);

} 
} 
} 
} 
} 

#include <thrust/detail/backend/cpp/detail/stable_radix_sort.inl>

