












#ifndef OR_TOOLS_UTIL_SORT_H_
#define OR_TOOLS_UTIL_SORT_H_

#include <algorithm>
#include <functional>
#include <iterator>

namespace operations_research {

template <class Iterator>
using value_type_t = typename std::iterator_traits<Iterator>::value_type;




















template <class Iterator, class Compare = std::less<value_type_t<Iterator>>>
void IncrementalSort(int max_comparisons, Iterator begin, Iterator end,
                     Compare comp = Compare{}, bool is_stable = false) {
  
  if (std::distance(begin, end) <= 1) return;

  
  
  Iterator last_sorted = std::prev(end);
  for (auto it = last_sorted; it != begin; --it) {
    if (comp(*it, *std::prev(it))) {
      std::iter_swap(it, std::prev(it));
      last_sorted = it;
    }
  }

  
  
  Iterator it = std::next(last_sorted);
  for (; it != end && max_comparisons > 0; ++it) {
    const auto inserted = *it;
    Iterator j = it;
    max_comparisons--;
    while (comp(inserted, *std::prev(j))) {
      max_comparisons--;
      *j = *std::prev(j);
      j--;
    }
    *j = inserted;
  }

  
  if (it == end) return;

  if (is_stable) {
    std::stable_sort(last_sorted, end, comp);
  } else {
    std::sort(last_sorted, end, comp);
  }
}









template <class Iterator, class Compare = std::less<value_type_t<Iterator>>>
void InsertionSort(Iterator begin, Iterator end, Compare comp = Compare{}) {
  
  if (std::distance(begin, end) <= 1) return;

  
  
  Iterator last_sorted = std::prev(end);
  for (auto it = last_sorted; it != begin; --it) {
    if (comp(*it, *std::prev(it))) {
      std::iter_swap(it, std::prev(it));
      last_sorted = it;
    }
  }

  
  
  for (Iterator it = std::next(last_sorted); it != end; ++it) {
    const auto inserted = *it;
    Iterator j = it;
    while (comp(inserted, *std::prev(j))) {
      *j = *std::prev(j);
      j--;
    }
    *j = inserted;
  }
}







template <class Iterator, class Compare = std::less<value_type_t<Iterator>>>
void IncrementalSort(Iterator begin, Iterator end, Compare comp = Compare{},
                     bool is_stable = false) {
  const int size = std::distance(begin, end);
  if (size <= 32) {
    InsertionSort(begin, end, comp);
  } else {
    IncrementalSort(size * 8, begin, end, comp, is_stable);
  }
}

}  

#endif  
