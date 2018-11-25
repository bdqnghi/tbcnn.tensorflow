#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <iterator>

#include "Sort.hpp"

namespace algorithms {


class Selection : public Sort {
public:
    template <typename ForwardIt>
    static void sort(ForwardIt first, ForwardIt last)
    {
        sort(first, last, std::less<typename std::iterator_traits<ForwardIt>::value_type>{});
    }

    template <typename ForwardIt, typename Less>
    static void sort(ForwardIt first, ForwardIt last, Less less)
    {
        for (; first != last; ++first) {
            ForwardIt min = first;
            for (auto it = std::next(first); it != last; ++it) {
                if (less(*it, *min)) {
                    min = it;
                }
            }
            exchange(min, first);
        }
    }
};

} 

#endif 
