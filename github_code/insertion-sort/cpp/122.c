#pragma once

#include <vector>
#include <iterator>

#include "AbstractSort.h"

template <typename T>
class InsertionSort : public AbstractSort<T>
{
public:
    InsertionSort();
    virtual ~InsertionSort();

    T *Sort(T *arr, size_t size) override;

};

template<typename T>
InsertionSort<T>::InsertionSort()
{

}

template<typename T>
InsertionSort<T>::~InsertionSort()
{

}

template<typename T>
T *InsertionSort<T>::Sort(T *arr, size_t size)
{
    T *copy = new T[size];
    std::copy(arr, arr + size, copy);

    for (int i = 1; i < size; i++)
    {
        T key = copy[i];
        int j = i - 1;
        while (j >= 0 && copy[j] > key) // < to desc
        {
            copy[j + 1] = copy[j];
            copy[j] = key;
            j = j - 1;
            this->AddMove();
            this->AddComparison();
        }
    }

    this->moves.push_back(this->move);
    this->comparisons.push_back(this->comparison);

    return copy;
}
