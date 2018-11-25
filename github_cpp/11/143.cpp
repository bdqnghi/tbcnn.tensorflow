#ifndef _HEAP_H
#define _HEAP_H



#include <vector>
#include <utility>    
#include <algorithm>  


template<typename T, typename compare>
std::pair<int, int> Heapify(std::vector<T> &array,
                            const compare& comp
                           );


template<typename T>
std::pair<int, int> HeapSort(std::vector<T> &array);


template<typename T, typename compare>
std::pair<int, int> HeapSort(std::vector<T> &array,
                             const compare& comp
                            );


#include "heap.hpp"


#endif
