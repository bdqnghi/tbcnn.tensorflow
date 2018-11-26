//
//  merge_sort.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-13.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_merge_sort_hpp
#define cpp_practice_merge_sort_hpp

#include "alg_share.h"

namespace dennycd{

    
    /**
      taking two array and recursively merge them into one 
      after run, data[begin..end] is sorted
     
       Time Complexity O(N logN)
       Space   O(N)
     
       tree depth  logN
       merge cost at each tree level  O(N)
     **/
    template<typename D, typename E>
    void _recursive_sort(int begin, int end, D& data, D& temp){
//        assert(begin <= end);
//        std::cout << "sort (" << begin << " - " << end << ")" << std::endl;
        
        //unit case
        if(begin==end) return;
        else{
            //split in half and sort each
            int mid = floor((begin+end)/2);
            _recursive_sort<D,E>(begin, mid, data,temp);
            _recursive_sort<D,E>(mid+1, end, data,temp);
            
            //then merge
            int left = begin, right = mid+1;
            for(int pos = begin; pos <= end; pos++){
                if(data[left] < data[right]){
                    temp[pos] = data[left++];
                    if(left > mid){
                        for(;right <= end;)
                            temp[++pos] = data[right++];
                        break;
                    }
                }
                else{
                    temp[pos] = data[right++];
                    if(right > end){
                        for(;left<=mid;)
                            temp[++pos] = data[left++];
                        break;
                    }
                }
            }
         
            //move sorted data from temp back into data
            for(int i=begin;i<=end;i++)
                data[i] = temp[i];
            
//            std::cout << "merge (" << begin << " - " << end << ")" << std::endl;
//            std::cout << data << std::endl;
        }
        
        
    }//_recursive_sort
    

    
    template<typename D, typename E>
    void merge_sort(D& data){
        D temp(data);
        _recursive_sort<D,E>(0, (int)data.size()-1, data, temp);
    }
    
    
}

#endif
