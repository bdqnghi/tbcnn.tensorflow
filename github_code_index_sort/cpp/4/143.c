#ifndef _HEAP_H
#define _HEAP_H

/* heap.h - heapsort sorting algorithm
This header and its associated .hpp file provide an implementation of the
  heap-sort sorting algorithm.

TODO: roll my own recursive heapify function
  TODO: track accesses and comparisons
  TODO: in-place heapify
*/

#include <vector>
#include <utility>    // swap, pair
#include <algorithm>  // STL heap operations

// helper function
template<typename T, typename compare>
std::pair<int, int> Heapify(std::vector<T> &array,
                            const compare& comp
                           );

// default of operator<
template<typename T>
std::pair<int, int> HeapSort(std::vector<T> &array);

// custom comparator
template<typename T, typename compare>
std::pair<int, int> HeapSort(std::vector<T> &array,
                             const compare& comp
                            );

// implementation
#include "heap.hpp"


#endif
