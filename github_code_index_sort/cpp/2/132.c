
//
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

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
            // Left hand side.
            mergesort(arr, low, mid);
            // Right hand side.
            mergesort(arr, mid + 1, high);
            Merge(arr, low, mid, high);
        }
    }

    void doSort(std::vector<SortObject<T>> *reformedArray) override {
        mergesort(reformedArray, 0, reformedArray->size() - 1);
    }
};
}   // namespace llama

#endif   // LLAMA_CPP_SRC_SORT_MERGESORT_H_
