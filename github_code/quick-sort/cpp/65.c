/**
 * Copyright (c) 2012, OpenGeoSys Community (http://www.opengeosys.com)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.com/LICENSE.txt
 *
 *
 * \file quicksort.h
 *
 * Created on 2010-05-26 by Thomas Fischer
 */

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

// STL
#include <cstddef>
#include <vector>
#include <algorithm>


namespace BaseLib
{
/**
 * version of partition_ that additional updates the permutation vector
 * */
template <class T>
size_t partition_(T* array, size_t beg, size_t end, size_t *perm)
{
    size_t i = beg + 1;
    size_t j = end - 1;
    T m = array[beg];

    for (;;) {
        while ((i < end) && (array[i] <= m))
            i++;
        while ((j > beg) && !(array[j] <= m))
            j--;

        if (i >= j)
            break;
        std::swap(array[i], array[j]);
        std::swap(perm[i], perm[j]);
    }

    std::swap(array[beg], array[j]);
    std::swap(perm[beg], perm[j]);
    return j;
}

/**
 * version of quickSort that stores the permutation
 * */
template <class T>
void quicksort(T* array, size_t beg, size_t end, size_t* perm)
{
    if (beg < end) {
        size_t p = partition_(array, beg, end, perm);
        quicksort(array, beg, p, perm);
        quicksort(array, p+1, end, perm);
    }
}

template <typename T>
class Quicksort {
public:
    Quicksort (std::vector<T>& array, size_t beg, size_t end, std::vector<size_t>& perm)
    {
        quicksort (array, beg, end, perm);
    }
private:
    size_t partition_(std::vector<T>& array, size_t beg, size_t end, std::vector<size_t>& perm)
    {
        size_t i = beg + 1;
        size_t j = end - 1;
        T m = array[beg];

        for (;;) {
            while ((i < end) && (array[i] <= m))
                i++;
            while ((j > beg) && !(array[j] <= m))
                j--;

            if (i >= j)
                break;
            std::swap(array[i], array[j]);
            std::swap(perm[i], perm[j]);
        }

        std::swap(array[beg], array[j]);
        std::swap(perm[beg], perm[j]);
        return j;
    }

    void quicksort(std::vector<T>& array, size_t beg, size_t end, std::vector<size_t>& perm)
    {
        if (beg < end) {
            size_t p = partition_(array, beg, end, perm);
            quicksort(array, beg, p, perm);
            quicksort(array, p+1, end, perm);
        }
    }
};

// specialization for pointer types
template <typename T>
class Quicksort <T *> {
public:
    Quicksort (std::vector<T*>& array, size_t beg, size_t end, std::vector<size_t>& perm)
    {
        quicksort (array, beg, end, perm);
    }

    Quicksort (std::vector<size_t>& perm, size_t beg, size_t end, std::vector<T*>& array)
    {
        quicksort (perm, beg, end, array);
    }

private:
    size_t partition_(std::vector<T*>& array, size_t beg, size_t end, std::vector<size_t>& perm)
    {
        size_t i = beg + 1;
        size_t j = end - 1;
        T* m = array[beg];

        for (;;) {
            while ((i < end) && (*array[i] <= *m))
                i++;
            while ((j > beg) && !(*array[j] <= *m))
                j--;

            if (i >= j)
                break;
            std::swap(array[i], array[j]);
            std::swap(perm[i], perm[j]);
        }

        std::swap(array[beg], array[j]);
        std::swap(perm[beg], perm[j]);
        return j;
    }

    void quicksort(std::vector<T*>& array, size_t beg, size_t end, std::vector<size_t>& perm)
    {
        if (beg < end) {
            size_t p = partition_(array, beg, end, perm);
            quicksort(array, beg, p, perm);
            quicksort(array, p+1, end, perm);
        }
    }

    size_t partition_(std::vector<size_t> &perm, size_t beg, size_t end, std::vector<T*>& array)
    {
        size_t i = beg + 1;
        size_t j = end - 1;
        size_t m = perm[beg];

        for (;;) {
            while ((i < end) && (perm[i] <= m))
                i++;
            while ((j > beg) && !(perm[j] <= m))
                j--;

            if (i >= j)
                break;
            std::swap(perm[i], perm[j]);
            std::swap(array[i], array[j]);
        }

        std::swap(perm[beg], perm[j]);
        std::swap(array[beg], array[j]);
        return j;
    }

    void quicksort(std::vector<size_t>& perm, size_t beg, size_t end, std::vector<T*>& array)
    {
        if (beg < end) {
            size_t p = partition_(perm, beg, end, array);
            quicksort(perm, beg, p, array);
            quicksort(perm, p+1, end, array);
        }
    }
};

} // end namespace BaseLib

#endif /* QUICKSORT_H_ */
