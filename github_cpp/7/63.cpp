#ifndef _MERGE_SORT_CPP_
#define _MERGE_SORT_CPP_
#include <iostream>       
#include <iomanip>        
#include <algorithm>      
#include <vector>         

namespace sort
{

template<typename T=int>
static inline void merge(typename std::vector<T>::iterator begin,
           typename std::vector<T>::iterator mid,
           typename std::vector<T>::iterator end) {
   while (begin != mid && mid != end) {
      auto it = mid;
      
      begin = std::upper_bound(begin, mid, *mid);
      
      mid   = std::upper_bound(mid,   end, *begin);
      std::rotate(begin, it, mid);
   }
}
   

template<typename T=int>
static inline void merge_sort(typename std::vector<T>::iterator begin,
                              typename std::vector<T>::iterator end) {
   auto&& size = std::distance(begin, end);
   if(size < 2) return;    
   auto&& mid = begin + size / 2 + size % 2;

   merge_sort(begin, mid);
   merge_sort(mid,   end);
   merge(begin, mid, end);
}

   
}  

#endif 
