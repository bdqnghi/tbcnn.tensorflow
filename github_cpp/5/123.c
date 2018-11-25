#ifndef _INSERTION_SORT_CPP_
#define _INSERTION_SORT_CPP_
#include <iostream>       
#include <iomanip>        
#include <algorithm>      
#include <vector>         

namespace sort
{


template<typename T=int>
static inline void insertion_sort(typename std::vector<T>::iterator begin,
                                  typename std::vector<T>::iterator end) {
   auto&& size = std::distance(begin, end);
   if(size < 2) return;    
   
   for (auto&& it = std::next(begin); it != end; ++it) {
      auto big_it = std::upper_bound(begin, it, *it); 
      
      std::rotate(big_it, it, std::next(it)); 
   }
}

#if 0
   for(int i = 0; i < n; i++) {
      for(int j = i; j > 0; j--)  
         if(cmp(&objs[j], &objs[j - 1]))
            SWAP(objs[j], objs[j - 1]);
         else break;
   }
#endif

}  
   
#endif 
