//
//  ShellSort.cpp
//  Sort
//
//  Created by limaoqi on 14/08/2017.
//  Copyright © 2017 limaoqi. All rights reserved.
//

#include "ShellSort.hpp"

vector<int> ShellSort::sort() {
    _sort();
    return _arr;
}

void ShellSort::_sort() {
    int n = (int)_arr.size();
    for (int k = n / 2; k > 0; k /= 2) {
        for (int i = 0; i < k; ++i) {
            for (int j = i + k; j < n; j += k) {
                for (int m = j - k; m >= 0; m -= k) {
                    if (_arr[m] > _arr[m + k]) {
                        swap(_arr[m], _arr[m + k]);
                    } else {
                        break;
                    }
                }
            }
        }
    }
}
