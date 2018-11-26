//
//  bubble_sort.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-12.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_bubble_sort_hpp
#define cpp_practice_bubble_sort_hpp

#include "alg_share.h"

namespace dennycd {

    /**
      Bubble Sort 
     
      locally sort two consecutive items and move the larger one towards the end
     
     
     O(n^2)  runtime 
     O(n) space 
     
     O(n^2) comparison 
     O(n^2) value copy
     
     however it has a chance of earlier termination if no exchange occurs in a swap pass
     
      - if already sortred, O(n)
     
     **/
    template<typename D, typename E>
    void bubble_sort(D& data){
        
        int n = (int)data.size();
        
        for(int sorted = n; sorted > 1; sorted--){
            bool swapped = false;
            for(int pos = 0; pos < sorted-1; pos++){
                if(data[pos] > data[pos+1]){
                    E tmp = data[pos+1];
                    data[pos+1] = data[pos];
                    data[pos] = tmp;
                    swapped = true;
                }
            }
            
            if(!swapped){
                //std::cout << "break at " << sorted << std::endl;
                break;
            }
            //when done, largest element now in sorted-1
        }
        
    }
}

#endif
