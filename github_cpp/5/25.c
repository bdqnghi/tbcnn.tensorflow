#ifndef CL_INSERTIONSORT_H_
#define CL_INSERTIONSORT_H_

#include "BaseSorting.h"

class InsertionSort : public BaseSorting
{
public:
		InsertionSort(size_t n = 0) : BaseSorting(n) {}
		InsertionSort(const vector<int> &vec) : BaseSorting(vec) {}
		InsertionSort(const int* arr, size_t n) : BaseSorting(arr, n) {}
		InsertionSort(const string& file_name) : BaseSorting(file_name) {}
		InsertionSort(const BaseSorting& obj) : BaseSorting(obj) {}
		virtual ~InsertionSort() {}
		InsertionSort& operator=(const BaseSorting& obj);
		virtual long long sort(size_t = 100);
		virtual string name() const { return string("InsertionSort"); }
};

#endif