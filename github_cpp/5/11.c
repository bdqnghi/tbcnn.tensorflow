







#ifndef cpp_practice_insertion_sort_hpp
#define cpp_practice_insertion_sort_hpp

namespace dennycd {

    
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
