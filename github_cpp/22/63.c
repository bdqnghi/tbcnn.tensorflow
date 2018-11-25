#include "BucketSort.h"

namespace rechteckpackungen {
namespace sortInt {

template<class T>
BucketSort<T>::BucketSort(bool reverse) :
		reverse(reverse) {
}

template<class T>
BucketSort<T>::~BucketSort() {
}

template<class T>
void BucketSort<T>::sort(std::vector<T>* vector, int (*getInt)(const T)) {
	auto max_element = std::max_element(vector->begin(), vector->end(), [getInt, this](const T a, const T b) {return getInt(a) < getInt(b);});
	int max = getInt(*max_element);
	auto buckets = std::vector<std::vector<T>>(max + 1);
	for (auto element : *vector) {
		buckets.at(getInt(element)).push_back(element);
	}

	if (reverse) {
		int i = vector->size() - 1;
		for (auto bucket : buckets) {
			for (auto element : bucket) {
				vector->at(i--) = element;
			}
		}
	} else {
		int i = 0;
		for (auto bucket : buckets) {
			for (auto element : bucket) {
				vector->at(i++) = element;
			}
		}
	}
}

}
}
