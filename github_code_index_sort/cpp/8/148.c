//
//  quick_sort.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-13.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_quick_sort_hpp
#define cpp_practice_quick_sort_hpp


#include "alg_share.h"

namespace dennycd{
    
    /**
       1 - pick a pivot and place it at the beginning of array
       2 - incrementall move items into [p][...<p...][...>=p...][unknown]
       3 - move pivot to mid of the two segment
     
        O(M)  where M = (end-begin+1)
     **/
    template<typename D, typename E>
    int _partition(int begin, int end, D& data){
        std::cout << "partition " << begin << "-" << end << std::endl;
        
        //randomly pick a pivot
        int pivot = begin + (int)((end-begin) * ((float)rand()/RAND_MAX));
        
        //excahnge with begin
        swap(data[begin], data[pivot]);
        pivot = begin;
        
        
        int lastP1 = pivot;        
        for(int beginU = pivot+1; beginU <= end; beginU++){
            if(data[beginU] < data[pivot]){
                //insert item after lastP1 by simply swaping with it
                lastP1++;
                swap(data[beginU], data[lastP1]); 
            }
            else{
                //beginU++; //advance even further
            }
        }
        
        //place pivot mid by swaping with lastP1
        swap(data[pivot], data[lastP1]);
        pivot = lastP1;
        
        return pivot;
    }

    /**
       O(N) for each level's partition cost
     
       on average, there are O(log N ) recursive levels 
       however, worst case (data is already sortd), the tree is degraded to a linear chain , O(N) levels 
     
       Worst Case :  O(N^2) 
       Average Case : O(N logN)
     
     **/
    template<typename D, typename E>
    void _recursive_sort(int begin, int end, D& data){
        if(begin < end){
            int pivot = _partition<D, E>(begin, end, data);
            std::cout << "pivot = " << pivot << " with data " << data << std::endl;
            _recursive_sort<D, E>(begin, pivot-1, data);
            _recursive_sort<D, E>(pivot+1, end, data);
        }
    }
    

    /**
      use a pivot item to partition array into two parts 
        - left part all smaller than pivot value 
        - right part all equal or larger than pivot value
     
      - then resurivly sort each part 
     
     **/
    template<typename D, typename E>
    void quick_sort(D& data){
        _recursive_sort<D, E>(0, (int)data.size()-1, data);
    }
}

#endif
