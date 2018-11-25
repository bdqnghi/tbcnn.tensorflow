
















#ifndef LLAMA_CPP_SRC_SORT_SELECTIONSORT_H_
#define LLAMA_CPP_SRC_SORT_SELECTIONSORT_H_

#include <algorithm>
#include <vector>
#include <utility>

#include "Sort.h"

namespace llama {
template<class T>
class SelectionSort : public Sort<T> {
 public:
    SelectionSort() {}
    explicit SelectionSort(std::vector<T> *inputArray) { this->performSort(inputArray); }

    void doSort(std::vector<SortObject<T>> *reformedArray) override {
        int n = reformedArray->size();
        int min;
        for (int i = 0; i < n - 1; i++) {
            min = i;
            
            for (int j = i + 1; j < n; j++) {
                if (reformedArray->at(min) > reformedArray->at(j)) {
                    min = j;
                }
            }
            
            if (min != i) {
                std::swap(reformedArray->at(i), reformedArray->at(min));
            }
        }
    }
};
}  

#endif  
