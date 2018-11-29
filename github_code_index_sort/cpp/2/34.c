#ifndef GUARD_MERGE_SORT_CPP
#define GUARD_MERGE_SORT_CPP

#include <vector>
#include <iterator>

using namespace std;

// w is the iterator pointing to the working space 
// the vector w has to be lage enough to hold both a1 and a2
template<class I>
void mergeInternal(I a1, I a1_end, I a2,I a2_end, I w)  {
	while (a1 != a1_end && a2 != a2_end)
		*(w++) = (*a1 < *a2 ? *(a1++) : *(a2++));
	while (a1 != a1_end)
		*(w++) = *(a1++);
	while (a2 != a2_end)
		*(w++) = *(a2++);
}

template<class I>
void mergeSortInternal(I a, I a_end) {
	typedef typename iterator_traits<I>::value_type vecTy;
	vector<vecTy>::size_type size = a_end - a;

	if (size < 2)
		return;
	
	mergeSortInternal(a, a + (size - size / 2));
	mergeSortInternal(a + (size - size / 2), a_end);

	vector<vecTy> tmp(a, a_end);
	mergeInternal(tmp.begin(), tmp.begin() + (size - size / 2), tmp.begin() + (size - size / 2), tmp.end(), a);
}
	
template<class T>
void mergeSort(vector<T>& a) {
	mergeSortInternal(a.begin(), a.end());
}
 #endif // !GUARD_MERGE_SORT_CPP