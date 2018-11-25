#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <iostream>
#include <vector>

namespace aed2
{










template <class T>
class ShellSort
{
public:
    ShellSort(std::vector<T>& v);

protected:
    std::vector<T>& _v; 
};






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

#endif 
