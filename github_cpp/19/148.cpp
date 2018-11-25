







#ifndef cpp_practice_quick_sort_hpp
#define cpp_practice_quick_sort_hpp


#include "alg_share.h"

namespace dennycd{
    
    
    template<typename D, typename E>
    int _partition(int begin, int end, D& data){
        std::cout << "partition " << begin << "-" << end << std::endl;
        
        
        int pivot = begin + (int)((end-begin) * ((float)rand()/RAND_MAX));
        
        
        swap(data[begin], data[pivot]);
        pivot = begin;
        
        
        int lastP1 = pivot;        
        for(int beginU = pivot+1; beginU <= end; beginU++){
            if(data[beginU] < data[pivot]){
                
                lastP1++;
                swap(data[beginU], data[lastP1]); 
            }
            else{
                
            }
        }
        
        
        swap(data[pivot], data[lastP1]);
        pivot = lastP1;
        
        return pivot;
    }

    
    template<typename D, typename E>
    void _recursive_sort(int begin, int end, D& data){
        if(begin < end){
            int pivot = _partition<D, E>(begin, end, data);
            std::cout << "pivot = " << pivot << " with data " << data << std::endl;
            _recursive_sort<D, E>(begin, pivot-1, data);
            _recursive_sort<D, E>(pivot+1, end, data);
        }
    }
    

    
    template<typename D, typename E>
    void quick_sort(D& data){
        _recursive_sort<D, E>(0, (int)data.size()-1, data);
    }
}

#endif
