//
//  insertion_sort.hpp
//  cpp-practice
//
//  Created by Denny C. Dai on 2013-06-12.
//  Copyright (c) 2013 Denny C. Dai. All rights reserved.
//

#ifndef cpp_practice_insertion_sort_hpp
#define cpp_practice_insertion_sort_hpp

namespace dennycd {

    /**
      Insertion sort in place
     
      grow a sorted region of the array by iterative move a element from unsorted region to it 
     
     
     O(n^2) time 
         - O(n) iteration
         -  O(n) for each insertion
     
     O(n) - space 
     **/
    template<typename D, typename E>
    void insertion_sort(D& data){
        
        int n = (int)data.size();
        for(int sorted = 1; sorted < n; sorted++){
            
            for(int cur = sorted; cur > 0; cur--)
            {
                if(data[cur] < data[cur-1]){
                    E tmp = data[cur-1];
                    data[cur-1] = data[cur];
                    data[cur] = tmp;
                }
            }
        }
    }
}

#endif
