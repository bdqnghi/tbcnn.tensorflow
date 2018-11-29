#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <iostream>
#include <vector>

namespace aed2
{

///////////////////////////////////////////////////////////////////////////////
/// Shellsort class.
///
/// In-place shellsort algorithm.
/// The increments follow Ciura's heuristics presented in
/// Ciura, Martin. Best increments for the average case of shellsort.
/// In 13th International Symposium on Fundamentals of Computation Theory
/// Pages 22--24, Riga, Latvia, August 2001.
///////////////////////////////////////////////////////////////////////////////
template <class T>
class ShellSort
{
public:
    ShellSort(std::vector<T>& v);

protected:
    std::vector<T>& _v; ///< Reference to the vector to be sorted.
};

///////////////////////////////////////////////////////////////////////////////
/// Constructor.
///
/// \param _v Vector of elements to be sorted in place.
///////////////////////////////////////////////////////////////////////////////
template <class T>
ShellSort<T>::ShellSort(std::vector<T>& v) : _v(v)
{
    int size = (int) v.size();
    int h = (int) (size / 2);
    while (h > 0)
    {
        for (int i = h; i < size; ++i)
        {
            T key = v.at(i);
            int j = i;
            while (j >= h && v.at(j - h) > key)
            {
                v.at(j) = v.at(j - h);
                j = j - h;
            }
            v.at(j) = key;
        }
        h = (int) (h / 2.25);
    }
}

}

#endif // SHELLSORT_H
