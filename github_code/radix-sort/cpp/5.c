//
//  RadixSortableArray.cpp
//  AoAHW3
//
//  Created by Buğra Ekuklu on 24.11.2016.
//  Copyright © 2016 The Digital Warehouse. All rights reserved.
//

#include "RadixSortStrategy.hpp"

#include "AlgorithmicSortStrategy.cpp"

template <typename T>
RadixSortStrategy<T>::RadixSortStrategy(const Container::Array<T> &array)
: AlgorithmicSortStrategy<T>(array)
{
    //  Empty implementation
}

template <typename T>
void
RadixSortStrategy<T>::sort() noexcept
{
    T maximumValue = AlgorithmicSortStrategy<T>::array[0];
    
    for (UInt64 i = 0; i < AlgorithmicSortStrategy<T>::array.getLength(); ++i) {
        if (static_cast<UInt64>(AlgorithmicSortStrategy<T>::array[i]) > static_cast<UInt64>(maximumValue)) {
            maximumValue = AlgorithmicSortStrategy<T>::array[i];
        }
    }

    for (UInt64 exponent = 1; maximumValue / exponent > 0; exponent *= 10) {
        countSort(exponent);
    }
}

template <typename T>
void
RadixSortStrategy<T>::countSort(UInt64 exponent)
{
    Container::Array<T> temporaryArray;
    temporaryArray.setLength(AlgorithmicSortStrategy<T>::array.getLength());
    
    UInt64 bucket[10] = {0};
    
    for (UInt64 i = 0; i < AlgorithmicSortStrategy<T>::array.getLength(); ++i) {
        bucket[(AlgorithmicSortStrategy<T>::array[i] / exponent) % 10] += 1;
    }
    
    for (UInt64 i = 1; i < 10; ++i) {
        bucket[i] += bucket[i - 1];
    }
    
    for (UInt64 i = AlgorithmicSortStrategy<T>::array.getLength() - 1; i > 0; --i) {
        temporaryArray[bucket[(static_cast<UInt64>(AlgorithmicSortStrategy<T>::array[i]) / exponent) % 10] - 1] = AlgorithmicSortStrategy<T>::array[i];
        bucket[(AlgorithmicSortStrategy<T>::array[i] / exponent) % 10] -= 1;
    }
    
    temporaryArray[bucket[(static_cast<UInt64>(AlgorithmicSortStrategy<T>::array[0]) / exponent) % 10] - 1] = AlgorithmicSortStrategy<T>::array[0];
    bucket[(AlgorithmicSortStrategy<T>::array[0] / exponent) % 10] -= 1;
    
    AlgorithmicSortStrategy<T>::array = temporaryArray;
}















