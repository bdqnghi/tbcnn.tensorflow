
















#ifndef LLAMA_CPP_SRC_SORT_MERGESORT_H_
#define LLAMA_CPP_SRC_SORT_MERGESORT_H_

#include <algorithm>
#include <utility>
#include <vector>

#include "Sort.h"

namespace llama {
template <class T> class MergeSort : public Sort<T> {
 public:
    MergeSort() {}
    explicit MergeSort(std::vector<T> *inputArray) { this->performSort(inputArray); }

    void Merge(std::vector<SortObject<T>> *arr, int low, int mid, int high) {
        int i = low;
        int j = mid + 1;
        int k = 0;
        std::vector<SortObject<T>> tmp(high - low + 1);

        while (i <= mid && j <= high) {
            if (arr->at(i) <= arr->at(j))
                std::swap(tmp.at(k++), arr->at(i++));
            else
                std::swap(tmp.at(k++), arr->at(j++));
        }
        while (i <= mid) {
            std::swap(tmp.at(k++), arr->at(i++));
        }
        while (j <= high) {
            std::swap(tmp.at(k++), arr->at(j++));
        }
        for (i = low, k = 0; i <= high; i++, k++) {
            std::swap(tmp.at(k), arr->at(i));
        }
        std::vector<SortObject<T>>().swap(tmp);
    }

    void mergesort(std::vector<SortObject<T>> *arr, int low, int high) {
        int mid;
        if (low < high) {
            mid = (low + high) / 2;
            
            mergesort(arr, low, mid);
            
            mergesort(arr, mid + 1, high);
            Merge(arr, low, mid, high);
        }
    }

    void doSort(std::vector<SortObject<T>> *reformedArray) override {
        mergesort(reformedArray, 0, reformedArray->size() - 1);
    }
};
}   

#endif   
