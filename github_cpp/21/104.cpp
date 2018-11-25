







#ifndef cpp_practice_selection_sort_hpp
#define cpp_practice_selection_sort_hpp

#include "alg_share.h"

namespace dennycd{
    
    
    template<typename D, typename E>
    class SelectionSort {
    public:
        
        typedef std::function<bool(E&,E&)> Comparator;

        
        
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
                
                
                E tmp = data[sorted-1];
                data[sorted-1] = largest;
                data[largestIdx] = tmp;
            }
            
        }
    
    };

}

#endif
