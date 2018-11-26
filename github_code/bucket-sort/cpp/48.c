//
// Created by n5320 on 2017/5/4.
//

#include "bucketsort.h"
#include "string.h"
#include "datastruct/Link.h"

void bucketsort(int *arrayA, int arraySize, int range) {
    int *arrayC = new int[range];
    memset(arrayC, 0, sizeof(int) * (range));
    int i, j, k;
    for (i = 0; i < arraySize; i++) {//把A中的每个元素按照值放入桶中
        arrayC[arrayA[i]]++;
    }

    for (i = j = 0; i < range; i++, j = k) {//统计每个桶元素的个数，并输出到B
        for (k = j; k < j + arrayC[i]; k++) {
            arrayA[k] = i;
        }
    }
}

void bucketsortMul(int* array, int arraySize, int range){
    int bucketCount = range/ 5;
    Link links[bucketCount];

    for(int i = 0; i< arraySize; i++){

    }
}