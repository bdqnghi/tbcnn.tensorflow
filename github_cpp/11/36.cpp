



#ifndef ALGORITHM_HEAPSORT_H
#define ALGORITHM_HEAPSORT_H

#include <vector>

using namespace std;

class HeapSort {
public:
    HeapSort() = delete;

    explicit HeapSort(const vector<int>& v) {
        num = v;
    }

    ~HeapSort() {
        num.clear();
    }

    HeapSort(const HeapSort&) = default;

    HeapSort(HeapSort&&) noexcept = default;

    HeapSort& operator=(const HeapSort&) = default;

    HeapSort& operator=(HeapSort&&) = default;

    void sort();

    void print();

private:
    vector<int> num;
};


#endif 
