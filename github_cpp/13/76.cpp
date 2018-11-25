
















#ifndef LLAMA_CPP_SRC_SORT_BUBBLESORT_H_
#define LLAMA_CPP_SRC_SORT_BUBBLESORT_H_

#include <algorithm>
#include <vector>
#include <utility>

#include "Sort.h"

namespace llama {
template<class T>
class BubbleSort : public Sort<T> {
 public:
    BubbleSort() {}
    explicit BubbleSort(std::vector<T> *inputArray) { this->performSort(inputArray); }

    void doSort(std::vector<SortObject<T>> *reformedArray) override {
        SortObject<T> temp;
        int n = reformedArray->size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (reformedArray->at(j) > reformedArray->at(j+1)) {
                std::swap(reformedArray->at(j), reformedArray->at(j+1));
            }
            }
        }
    }
};
}  
#endif  
