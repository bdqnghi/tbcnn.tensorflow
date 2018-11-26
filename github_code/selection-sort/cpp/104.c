//
//  selection_sort.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-12.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_selection_sort_hpp
#define cpp_practice_selection_sort_hpp

#include "alg_share.h"

namespace dennycd{
    
    /**
      Selection Sort 
     
      D - data list type
      E - data element type
     
      O(n^2) runtime
             O(n^2) copmarison
             O(n) value copies
     O(n) space
     
     **/
    template<typename D, typename E>
    class SelectionSort {
    public:
        //comparator - default returns true if first is larger then second
        typedef std::function<bool(E&,E&)> Comparator;

        /**
          sort a given input list in ascending order (as defined in cp)
          iteratively find largest element and swap at the end of the array
         **/
        
        static void sort(D& data, Comparator cp = [](E&l,E&r)->bool{return (l > r);} ){
            int n = (int)data.size();
            
            for(int sorted=n;sorted>1;sorted--){
                E largest = data[0];
                int largestIdx = 0;
                for(int j=1;j<sorted;j++){
                    if(cp(data[j], largest)){
                        largest = data[j];
                        largestIdx = j;
                    }
                }
                
                //swap
                E tmp = data[sorted-1];
                data[sorted-1] = largest;
                data[largestIdx] = tmp;
            }
            
        }
    
    };

}

#endif
