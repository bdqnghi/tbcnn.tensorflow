



#ifndef CADA_CPP_IMPLEMENTATIONS_BINARYSEARCH_HPP
#define CADA_CPP_IMPLEMENTATIONS_BINARYSEARCH_HPP

#include "CommonInclude.hpp"



template<typename IteratorType, typename ValueType,typename Less, typename Equal>
inline IteratorType BinarySearch(IteratorType left, IteratorType right, const ValueType &target, Less less, Equal equal) {
    auto end = right--;
    while (left <= right) {
        auto dist = std::distance(left,right);
        auto middle = left + (dist / 2);
        if (equal(target,*middle))return middle;
        if (less(target,*middle))right = middle - 1;
        else left = middle + 1;
    }
    return end;
}

template<typename IteratorType, typename ValueType>
inline IteratorType BinarySearch(IteratorType left, IteratorType right, const ValueType &target) {
    return BinarySearch(left,right,target,std::less<ValueType>{},std::equal_to<ValueType>{});
}


#endif 
