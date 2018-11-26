#include <iostream>
#include "pch.h"
#include "BucketSort.h"
#include <vector>


BucketSort::BucketSort()
{
}


BucketSort::~BucketSort()
{
}

std::vector<int>* BucketSort::sortVector(std::vector<int> *v) {
	// Find largest value k
	int k = NULL;
	for(auto element : *v) {
		if (k == NULL) {
			k = element;
		}
		else {
			if (k < element) {
				k = element;
			}
		}
	}

	// create a vector of size k + 1 and intiate all indexes to 0
	std::vector<int> w(k + 1, 0);

	// increase the value stored in W[i] when the same value are found in v
	for (auto i : *v) {
		w[i]++;
	}

	// I felt that I wanted to end up with a sorted list so I returned the results from the bucketsort back to the original vector
	int index = 0;
	for (int i = 0; i < w.size(); i++) {
		if (w[i] != 0) {
			for (int j = 0; j < w[i]; j++) {
				v->at(index) = i;
				index++;
			}
		}
	}

	return v;
}

void BucketSort::printVector(std::vector<int> *v) {
	std::cout << "vector : [ ";
	for (auto i : *v) {
		std::cout << i << " ";
	}
	std::cout << "]\n";
}

std::string BucketSort::getDiscription() {
	return "BucketSort";
}