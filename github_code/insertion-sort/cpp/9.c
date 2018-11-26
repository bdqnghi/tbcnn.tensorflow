#ifndef INSERTION_HPP
#define INSERTION_HPP

#include <iterator>

#include "Sort.hpp"

namespace algorithms {

/**
 * Insertion sort method implementation class.
 *
 * [insertion-sort](https://www.toptal.com/developers/sorting-algorithms/insertion-sort)
 */
class Insertion : public Sort {
public:
    template <typename BidirectionalIt>
    static void sort(BidirectionalIt first, BidirectionalIt last)
    {
        sort(first, last, std::less<typename std::iterator_traits<BidirectionalIt>::value_type>{});
    }

    template <typename BidirectionalIt, typename Less>
    static void sort(BidirectionalIt first, BidirectionalIt last, Less less)
    {
        for (auto it1 = first; it1 != last; ++it1) {
            for (auto it2 = it1; it2 != first;) {
                BidirectionalIt left = std::prev(it2);
                if (less(*it2, *left)) {
                    exchange(it2, left);
                    it2 = left;
                }
                else {
                    break;
                }
            }
        }
    }
};

} // namespace algorithms

#endif // INSERTION_HPP
