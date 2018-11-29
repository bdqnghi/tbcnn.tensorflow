//
// Created by dyq94 on 2018/11/11.
//

#ifndef SHELLSORT_SHELLSORT_H
#define SHELLSORT_SHELLSORT_H

#include "InsertSortMethod.h"

namespace ShellSort {
    int step = 3;

    template<typename T>
    void shellSort(T *arr, int n) {
        //选取步长
        for (int h = n / step; h > 0; h = h / step) {
            //选择头指针
            for (int i = 0; i < h; ++i) {
                //插入排序
                for (int j = i; j < n; j = j + h) {
                    //选择初始元素arr[i],arr[i+h],arr[i+2h]
                    T t = arr[j];
                    int insertIndex = j;
                    //与数组中之前的元素进行匹配：
                    // 当比前元素要大的时：
                    //  前一个数组完后移动。
                    // 当相等或小于的时候，在前一个位置进行插入
                    for (int k = j; k - h >= 0 && t > arr[k - h]; k = k - h) {
                        arr[k] = arr[k - h];
                        insertIndex = k - h;
                    }
                    arr[insertIndex] = t;
                }
            }
        }
    }
}

#endif //SHELLSORT_SHELLSORT_H
