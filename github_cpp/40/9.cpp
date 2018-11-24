#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

template<typename Iterator>
Iterator choosePivot(Iterator begin, Iterator end)
{
    return begin+(end-begin)/2;
}

template<typename Iterator>
void quickSort(Iterator begin, Iterator end)
{
    Iterator pivot=choosePivot(begin, end);
    if (end-begin<2) {
        return;
    }
    Iterator left=begin;
    Iterator right=end-1;
    while (left<right) {
        while (*left<*pivot) {
            ++left;
        }
        while (*right>*pivot) {
            --right;
        }
        std::swap(*left, *right);
        if (left==pivot) {
            pivot=right;
            ++left;
        } else if (right==pivot) {
            pivot=left;
            --right;
        }
    }
    quickSort(begin, pivot);
    quickSort(pivot+1, end);
}

int main()
{
    std::default_random_engine random_engine;
    for (unsigned int i=0; i!=1000; ++i) {
        typedef std::vector<int> Data;
        //Data origin={-10, 5, -10, 0, 16, 34 , 164, 115, 345, -12, 0, 134};
        Data origin;
        for (unsigned int i=0; i!=1000; ++i) {
            origin.push_back(random_engine());
        }
        Data stdSort=origin;
        std::sort(stdSort.begin(), stdSort.end());
        Data mySort=origin;
        quickSort(mySort.begin(), mySort.end());
        if (mySort!=stdSort) {
            for (const int& e: origin) {
                std::cout << e << " ";
            }
            std::cout << std::endl;
        }
    }
}
