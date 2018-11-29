#ifndef GUARD_QUICKSORT_CPP
#define GUARD_QUICKSORT_CPP

#include <vector>
#include <random>
#include <iterator>
#include <thread>

#include "insert_sort.h"
#include "stack.h"

using namespace std;

template<class T>
void quicksort(std::vector<T>& a) {
	AuxQuicksort(a.begin(), a.end());
}

//for whatever reason the recurrsive version is faster
//than the explicit stack version.
template<class I>
void nonrecurrsive_AuxQuicksort(I begin, I end) {
	struct vec_s {
		I begin, end;
	};
	Stack<vec_s> stack;

	stack.push({begin, end});

	while (!stack.isEmpty()) {
		vec_s cur = stack.pop();//cur for current
		if ((cur.end - cur.begin) <= 100) {
			insertSort(cur.begin, cur.end);
			continue;
		}
		I pivot = cur.begin + (rand() % (cur.end - cur.begin));

		partition(cur.begin, cur.end, pivot);

		stack.push({cur.begin, pivot});
		stack.push({pivot, cur.end});
	}
}

/*template<class I>
void multithreaded_AuxQuicksort(I begin, I end) {
	if ((end - begin) <= 1) {
		//insertSort(begin, end);
		return;
	}

	I pivot = begin + (rand() % (end - begin));

	partition(begin, end, pivot);
	std::thread t[1];
	t[0] = std::thread(multithreaded_AuxQuicksort, begin, pivot);

	AuxQuicksort(pivot, end);
	t[0].join();
}*/

template<class I>
void AuxQuicksort(I begin, I end) {
	while (true) {
		if ((end - begin) <= 60) {//determined to be opimal on my machine
			insertSort(begin, end);
			return;
		}

		I pivot = begin + (rand() % (end - begin));

		partition(begin, end, pivot);
		
		AuxQuicksort(begin, pivot);//not sure of iterator value will be modified
		begin = pivot;
		end = end;
	}
}

template<class I>
void partition(I begin, I end, I& pivot) {
	typedef typename std::iterator_traits<I>::value_type vecTy;

	vecTy tmp = *(end - 1);
	*(end - 1) = *pivot;
	*pivot = tmp;
	pivot = end - 1;

	I i = begin;
	for (I j = i; j != pivot; ++j) {
		if (*j < *pivot) {
			tmp = *j;
			*j = *i;
			*i = tmp;
			++i;
		}
	}

	tmp = *i;
	*i = *pivot;
	*pivot = tmp;
	pivot = i;
}

#endif