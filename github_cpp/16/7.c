#ifndef SHELL_HPP
#define SHELL_HPP

#include <iterator>

#include "Sort.hpp"

namespace algorithms {


class Shell : public Sort {
public:
    template <typename RandomAccessIt>
    static void sort(RandomAccessIt first, RandomAccessIt last)
    {
        sort(first, last, std::less<typename std::iterator_traits<RandomAccessIt>::value_type>{});
    }

    template <typename RandomAccessIt, typename Less>
    static void sort(RandomAccessIt first, RandomAccessIt last, Less less)
    {
        
        
        std::size_t l = std::distance(first, last);

        
        
        std::size_t h = 1;
        while (h < l / 3) {
            h = 3 * h + 1;
        }

        
        
        
        while (h >= 1) {
            
            
            for (std::size_t i = h; i < l; ++i) {
                
                
                for (std::size_t j = i; j >= h; j -= h) {
                    if (less(first[j], first[j - h])) {
                        exchange(first + j, first + j - h);
                    }
                    else {
                        break;
                    }
                }
            }
            h /= 3;
        }
    }
};

} 

#endif 
