







#ifndef cpp_practice_merge_sort_hpp
#define cpp_practice_merge_sort_hpp

#include "alg_share.h"

namespace dennycd{

    
    
    template<typename D, typename E>
    void _recursive_sort(int begin, int end, D& data, D& temp){


        
        
        if(begin==end) return;
        else{
            
            int mid = floor((begin+end)/2);
            _recursive_sort<D,E>(begin, mid, data,temp);
            _recursive_sort<D,E>(mid+1, end, data,temp);
            
            
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
         
            
            for(int i=begin;i<=end;i++)
                data[i] = temp[i];
            


        }
        
        
    }
    

    
    template<typename D, typename E>
    void merge_sort(D& data){
        D temp(data);
        _recursive_sort<D,E>(0, (int)data.size()-1, data, temp);
    }
    
    
}

#endif
