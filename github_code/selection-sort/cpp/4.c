#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <iterator>

#include "Sort.hpp"

namespace algorithms {

/**
 * Selection sort method implementation class.
 *
 * [selection-sort](https://www.toptal.com/developers/sorting-algorithms/selection-sort)
 */
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

} // namespace algorithms

#endif // SELECTION_HPP
