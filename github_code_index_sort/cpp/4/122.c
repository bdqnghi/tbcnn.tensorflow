//
//  HeapSortStrategy.cpp
//  AoAHW3
//
//  Created by Buğra Ekuklu on 26.11.2016.
//  Copyright © 2016 The Digital Warehouse. All rights reserved.
//

#include "HeapSortStrategy.hpp"

#include <algorithm>

#include "AlgorithmicSortStrategy.cpp"

template <typename T>
HeapSortStrategy<T>::HeapSortStrategy(const Container::Array<T> &array)
: AlgorithmicSortStrategy<T>(array)
{
    //  Blank implementation
}

template <typename T>
void
HeapSortStrategy<T>::sort() noexcept
{
    buildHeap();
    
    for (UInt64 i = AlgorithmicSortStrategy<T>::array.getLength() - 1; i > 0; --i) {
        std::swap(AlgorithmicSortStrategy<T>::array[0], AlgorithmicSortStrategy<T>::array[i]);
        
        minimumHeapify(0, i);
    }
    
    minimumHeapify(0, 0);
}

template <typename T>
void
HeapSortStrategy<T>::buildHeap() noexcept
{
    for (UInt64 i = (AlgorithmicSortStrategy<T>::array.getLength() / 2) - 1; i > 0; --i) {
        minimumHeapify(i, AlgorithmicSortStrategy<T>::array.getLength());
    }
    
    minimumHeapify(0, AlgorithmicSortStrategy<T>::array.getLength());
}

template <typename T>
void
HeapSortStrategy<T>::minimumHeapify(const UInt64 targetIndex,
                                    const UInt64 boundIndex) noexcept
{
    UInt64 biggestIndex = targetIndex;
    UInt64 left = (targetIndex * 2) + 1;
    UInt64 right = (targetIndex * 2) + 2;
    
    if (left < boundIndex && AlgorithmicSortStrategy<T>::array[left] < AlgorithmicSortStrategy<T>::array[targetIndex]) {
        biggestIndex = left;
    } else {
        biggestIndex = targetIndex;
    }
    
    if (right < boundIndex && AlgorithmicSortStrategy<T>::array[right] < AlgorithmicSortStrategy<T>::array[biggestIndex]) {
        biggestIndex = right;
    }
    
    if (biggestIndex != targetIndex) {
        std::swap(AlgorithmicSortStrategy<T>::array[biggestIndex], AlgorithmicSortStrategy<T>::array[targetIndex]);
        
        minimumHeapify(biggestIndex, boundIndex);
    }
}


















