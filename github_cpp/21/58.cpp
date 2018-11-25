#ifndef selection_SORT
#define selection_SORT

#include <array>

#include "minimumSearch.cpp"
#include "arrayutils.cpp"

namespace ownsort {

    template<typename T, size_t SIZE>
    void selectionSort(std::array<T, SIZE> &a, size_t start, size_t end) {
        for (size_t i = start; i < end; i++) {
            std::swap(a[i], a[minimumSearch::minimum(a, i, end)]);
        }
    }

    template<typename T, size_t SIZE>
    void selectionSort(std::array<T, SIZE> &a) {
        selectionSort(a, 0, SIZE);
    }

    template<typename T, size_t SIZE>
    void selectionSortOpt(std::array<T, SIZE> &a, size_t start, size_t end) {
        for (size_t i = start; i < end; i++) {
            std::swap(a[i], a[minimumSearch::minimumOpt(a, i, end)]);
        }
    }

    template<typename T, size_t SIZE>
    void selectionSortOpt(std::array<T, SIZE> &a) {
        selectionSortOpt(a, 0, SIZE);
    }

}

#endif 
