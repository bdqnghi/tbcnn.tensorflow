#ifndef _MERGE_SORT_CPP_
#define _MERGE_SORT_CPP_
#include <iostream>       /* std::cout               */
#include <iomanip>        /* std::setw               */
#include <algorithm>      /* std::vector             */
#include <vector>         /* std:vector              */

namespace sort
{

template<typename T=int>
static inline void merge(typename std::vector<T>::iterator begin,
           typename std::vector<T>::iterator mid,
           typename std::vector<T>::iterator end) {
   while (begin != mid && mid != end) {
      auto it = mid;
      /* Skip over elements in 1st partition which are less  *
       * than mid (1st elem in 2nd partition)                */
      begin = std::upper_bound(begin, mid, *mid);
      /* Skip over elements in 2nd partition which are greater*
       * than begin (1st elem in 1st partition)              */
      mid   = std::upper_bound(mid,   end, *begin);
      std::rotate(begin, it, mid);
   }
}
   
/* Recursive Merge sort                                      *
 * Impl inspired by http://hgad.net/posts/stl-algorithms-in-action/  */
template<typename T=int>
static inline void merge_sort(typename std::vector<T>::iterator begin,
                              typename std::vector<T>::iterator end) {
   auto&& size = std::distance(begin, end);
   if(size < 2) return;    /* If 0 or 1 elems, don't sort    */
   auto&& mid = begin + size / 2 + size % 2;

   merge_sort(begin, mid);
   merge_sort(mid,   end);
   merge(begin, mid, end);
}

   
}  //end namespace

#endif //_MERGE_SORT_CPP_
