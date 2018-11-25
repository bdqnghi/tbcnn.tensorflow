
















#ifndef LLAMA_CPP_SRC_SORT_INSERTIONSORT_H_
#define LLAMA_CPP_SRC_SORT_INSERTIONSORT_H_

#include <vector>

#include "Sort.h"

namespace llama {
template<class T>
class InsertionSort : public Sort<T> {
 public:
    InsertionSort() {}
    explicit InsertionSort(std::vector<T> *inputArray) { this->performSort(inputArray); }

    void doSort(std::vector<SortObject<T>> *reformedArray) override {
        for (int i = 1; i < reformedArray->size(); i++) {
            
            SortObject<T> key = reformedArray->at(i);
            
            int index = i;
            
            
            
            while (index > 0 && reformedArray->at(index-1) > key) {
                reformedArray->at(index) = reformedArray->at(index-1);
                
                index--;
            }
            reformedArray->at(index) = key;
        }
    }
};
}  

#endif  
