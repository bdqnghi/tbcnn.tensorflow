
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
            // Select the min value.
            for (int j = i + 1; j < n; j++) {
                if (reformedArray->at(min) > reformedArray->at(j)) {
                    min = j;
                }
            }
            // Swap between flag and the i if they are different.
            if (min != i) {
                std::swap(reformedArray->at(i), reformedArray->at(min));
            }
        }
    }
};
}  // namespace llama

#endif  // LLAMA_CPP_SRC_SORT_SELECTIONSORT_H_
